/*
  Smooth MAX6675 Thermocouple

  Reads a temperature from the MAX6675 thermocouple,
  smooth and displays it in the default Serial.

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>

#define SCK_PIN 10
#define CS_PIN 9
#define SO_PIN 8
#define SALIDA 13
#define TENSION 7
int cond;
/**
  Smoothing factor of a temperature value.
*/
#define SMOOTHING_FACTOR 5

Thermocouple* thermocouple = NULL;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  Thermocouple* originThermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
  thermocouple = new SmoothThermocouple(originThermocouple, SMOOTHING_FACTOR);
  pinMode(SALIDA, OUTPUT);
  pinMode(TENSION, OUTPUT);
  digitalWrite(TENSION,HIGH);
  /* OR
    thermocouple = new SmoothThermocouple(
      new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN),
      SMOOTHING_FACTOR
    );
  */
  const double celsius = thermocouple->readCelsius();
  Serial.println(celsius);
 if (celsius>55){
  cond=1;
 }
 else cond=0;
 delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  const double celsius = thermocouple->readCelsius();
if (cond==0){
  if (celsius<55){
    digitalWrite(SALIDA,LOW);
    Serial.print("alto");}
    else {digitalWrite(SALIDA,HIGH);
    cond=1;}}
    else{
  if (celsius>50){
    digitalWrite(SALIDA,HIGH);}
    else {digitalWrite(SALIDA,LOW);
    cond=0;}}
  
  // Output of information
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.print(" C, ");Serial.print("\t");
  Serial.print(cond);Serial.print("\t");
  Serial.println();
  

  delay(500); // optionally, only to delay the output of information in the example.
}
