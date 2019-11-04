/*
 * Ejemplo para mostrar en un display TM1638 
 */

#include <TM1638plus.h>
#include <PreciseLM35.h>
const int pinLM35 = A0;
const float arefRatio = 0.98819;
#define STROBE_TM 4
#define CLOCK_TM 6
#define DIO_TM 7
uint8_t MainMode = 2;
unsigned long previousMillis = 0;
const long  interval  = 180; 
int ref = 120;

TM1638plus tm(STROBE_TM, CLOCK_TM, DIO_TM);
PreciseLM35 lm35(pinLM35, INTERNAL1V1, arefRatio); //MEGA
//PreciseLM35 lm35(pinLM35, INTERNAL, arefRatio); //UNO
void setup() {
  tm.reset();
  tm.brightness(4);
  tm.displayText("CONTROL");
  delay(500);
  Serial.begin(9600);
  tm.reset();
}

void loop() {
//  int temp = lm35.readCelsius();
//  char dest[8];
//  sprintf(dest,"%04i%04i",temp,ref);
//  tm.displayText(dest);
//  Serial.println(dest);
    char setpoint[4] = "hola";
    char dest2[8];
    sprintf(dest2,"%s%03i",setpoint,ref);
    tm.displayText(dest2);
  uint8_t buttons = buttonsRead();
  switch (buttons)
  {
    case 0x80:
    ref++;
    break;
    case 0x40:
    ref--;
    break;
  }
}


uint8_t buttonsRead(void)
{
  uint8_t buttons = 0;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    buttons = tm.readButtons();
  }
  return buttons;
}
