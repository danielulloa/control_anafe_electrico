
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
#include <OneWire.h>
#include <DallasTemperature.h>

#define MAX6675_CS   10
#define MAX6675_SO   12
#define MAX6675_SCK  13
#define VCC_RELE      8
#define RELE          9
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// valores KP, KI, KD

double kp = 0.171760139041986;
double Ti = 0.00056124559582886;

//double kp = 1;
//double Ti=0;
double Td = 16;

double sumError;
double derError; //Es la derivada del valor a la salida de la planta
const int referencia = 80;
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
  pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
  sensors.requestTemperatures();
  anterior = sensors.getTempCByIndex(0);
}

void loop() {
  
  unsigned long now = millis();
  int dt = (now - before);
  // calculo de los errores
  sensors.requestTemperatures();
  actual = sensors.getTempCByIndex(0); //temperatura actual
  double error = referencia-actual; // entrada al bloque PID
  
  // Integral
  sumError += error*dt;
  //anti wind-up
  if (sumError > outMAX) sumError=outMAX;
  else if(sumError< outMIN) sumError=outMIN;

  //Derivada
  derError = (actual-anterior)/dt;

  //salida = kp*(error + sumError/Ti + derError*Td);
  //salida = kp*error;
  salida = kp*(error + sumError*Ti);
  adaptado = map(salida, 0, 8,0, 1023);

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
  Serial.print(salida);
  Serial.print("\t");
  Serial.print(adaptado);
  Serial.print("\t");  
  Serial.print(error);
  Serial.print("\t");
  Serial.println(readThermocouple());
  delay(100); 
  before = now;
  anterior = actual;
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
