
/*
 * Termocupla MAX6675
 * Para tener una comunicacion por hardware SPI especifico hay que usar
 * los siguientes pines
 * SCK (Source Clock) = 13
 * CS (Chip Select) = 10
 * MISO (Master IN Slave OUT) = 12
 */

 /*
  * PWM
  * Configurar el registro TCCRB1 (Timer/Counter control register B)
  * de los pines 9 y 10 para ajustar la frecuencia
  * TCCR1B = TCCR1B & B11111000 | B00000101;    
  * aplica un prescaler y se obtiene 30.64Hz
  */
  
#include <SPI.h>
#include <TimerOne.h>
#define MAX6675_CS   10
#define MAX6675_SO   12
#define MAX6675_SCK  13
#define VCC_RELE      8
#define RELE          9
// valores KP, KI, KD

double kp = 4.3;
int Ti = 230;
int Td = 16;

double sumError;
double derError; //Es la derivada del valor a la salida de la planta
const int referencia = 120;
const int outMAX = 1024;
const int outMIN = 0;
unsigned long before;
double anterior;
double actual;
double salida;
int adaptado;

void setup() {
  Timer1.initialize(4000000);  // 1Hz
  Serial.begin(250000);
  pinMode(VCC_RELE, OUTPUT);
  pinMode(RELE, OUTPUT);
  delay(1000);
  anterior = readThermocouple();
}

void loop() {
  unsigned long now = millis();
  int dt = (now - before);
  // calculo de los errores
  actual = readThermocouple(); //temperatura actual
  double error = referencia-actual; // entrada al bloque PID
  
  // Integral
  sumError += error*dt;
  //anti wind-up
  if (sumError > outMAX) sumError=outMAX;
  else if(sumError< outMIN) sumError=outMIN;

  //Derivada
  derError = (actual-anterior)/dt;

  salida = kp*(error + sumError/Ti + derError*Td);
  //salida = kp*error;
  //salida = kp*(error + sumError/Ti);
  adaptado = constrain(salida, 0, 1023);

  if (salida<1){
    digitalWrite(VCC_RELE,LOW);
  }
  else{
      digitalWrite(VCC_RELE,HIGH);
      Timer1.pwm(RELE, 1023-adaptado);
  }

 


  //DEBUG
  Serial.print(actual);
  Serial.print("\t");
  Serial.println(adaptado);
  //Serial.print("\t");  
  //Serial.print(dt);
  //Serial.print("\t");
  //Serial.println(salida); 
  before = now;
  anterior = actual;
  delay(250);
}

double readThermocouple() {

  uint16_t v;
  pinMode(MAX6675_CS, OUTPUT);
  pinMode(MAX6675_SO, INPUT);
  pinMode(MAX6675_SCK, OUTPUT);
  
  digitalWrite(MAX6675_CS, LOW);
  delay(1);

  // Read in 16 bits,
  //  15    = 0 always
  //  14..2 = 0.25 degree counts MSB First
  //  2     = 1 if thermocouple is open circuit  
  //  1..0  = uninteresting status
  
  v = shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  v <<= 8;
  v |= shiftIn(MAX6675_SO, MAX6675_SCK, MSBFIRST);
  
  digitalWrite(MAX6675_CS, HIGH);
  if (v & 0x4) 
  {    
    // Bit 2 indicates if the thermocouple is disconnected
    return NAN;     
  }

  // The lower three bits (0,1,2) are discarded status bits
  v >>= 3;

  // The remaining bits are the number of 0.25 degree (C) counts
  return v*0.25;
}
