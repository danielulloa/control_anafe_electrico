#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MAX6675_CS   10
#define MAX6675_SO   12
#define MAX6675_SCK  13
#define RELE 9
#define VCC_RELE 8
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

unsigned long time;
unsigned long before;
int dt;
float temp;
float anterior;
float delta;

void setup()
{
    pinMode(RELE, OUTPUT);
    pinMode(VCC_RELE, OUTPUT);    
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(VCC_RELE,HIGH);
    sensors.begin();
    Serial.begin(9600);
    Serial.println("---BEGIN---");
    anterior=readThermocouple();
    Serial.print("TIME");
    Serial.print("\t");
    Serial.print("INPUT");
    Serial.print("\t");
    Serial.print("OUTPUT1");
    Serial.print("\t");    
    Serial.print("OUTPUT2");
    Serial.print("\t");
    Serial.print("TS");
    Serial.print("\t");
    Serial.println("GRADIENT");
    delay(100);

}

void loop()
{
    time = millis();
    dt = time - before;
    sensors.requestTemperatures();
    if (time > 2500){      
        digitalWrite(RELE,LOW);
        temp=readThermocouple();        
        delta=(temp-anterior)/dt;
        Serial.print(time);
        Serial.print("\t");
        Serial.print("1");
        Serial.print("\t");
        Serial.print(temp);
        Serial.print("\t");
        Serial.print(sensors.getTempCByIndex(0));
        Serial.print("\t");         
        Serial.print(dt);
        Serial.print("\t");
        Serial.println(delta,5);
    }
    else
    {
        digitalWrite(RELE,HIGH);
        temp=readThermocouple();
        delta=(temp-anterior)/dt;
        Serial.print(time);
        Serial.print("\t");
        Serial.print("0");
        Serial.print("\t");
        Serial.print(temp);
        Serial.print("\t");
        Serial.print(sensors.getTempCByIndex(0));
        Serial.print("\t");        
        Serial.print(dt);
        Serial.print("\t");
        Serial.println(delta,5);
    }
    before=time;
    anterior=temp;
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
//203512
