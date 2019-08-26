/*
  Average Thermocouple

  Reads a temperature from a thermocouple based
  on the MAX6675 driver and displays it in the default Serial.

  https://github.com/YuriiSalimov/MAX6675_Thermocouple

  Created by Yurii Salimov, May, 2019.
  Released into the public domain.
*/
#include <Thermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <PreciseLM35.h>

const int pinLM35 = A0;
PreciseLM35 lm35(pinLM35, DEFAULT);

#define SCK_PIN 10
#define CS_PIN 9
#define SO_PIN 8
 int i=0;

Thermocouple* thermocouple;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  thermocouple = new MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);

}

// the loop function runs over and over again forever
void loop() {
  // Reads temperature
  const double plancha = thermocouple->readCelsius();
  Serial.print(i);
  Serial.print("\t");
  Serial.print(plancha);
  Serial.print("\t");
  Serial.println(lm35.readCelsius());
  i=i+1;
  delay(1000);  
}
