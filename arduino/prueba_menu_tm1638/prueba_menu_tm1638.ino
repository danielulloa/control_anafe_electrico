#include <TM1638plus.h>

#define STROBE_TM 4
#define CLOCK_TM 6
#define DIO_TM 7
int MainMode = 2;
unsigned long previousMillis = 0;
const long  interval  = 225; // interval at which to debounce button readback function(milliseconds)

int ref = 30;
float kp = 2;
int Ti = 50;
int Td = 30;
int temp;

TM1638plus tm(STROBE_TM, CLOCK_TM, DIO_TM);
//PreciseLM35 lm35(pinLM35, INTERNAL1V1, arefRatio); //MEGA
void setup() {
  tm.reset();
  Serial.begin(9600);
}

void loop() {

for (MainMode = 1; MainMode <= 5; MainMode++)
{
  switch (MainMode)
  {
    case 1:
    Serial.print("caso 1");
    Serial.print("\t");
    temp = analogRead(A0);
    Serial.println(temp);
    Serial.print("\t");
    char dest1[8];
    sprintf(dest1,"%04i%04i",kp,ref);
    Serial.println(dest1);
    tm.displayText(dest1);
    break;

    case 2:
//    char setpoint[1] = "set ";
//    char dest2[8];
//    sprintf(dest2,"%s%04i",setpoint,ref);
//    Serial.println(dest2);
//    tm.displayText(dest2);
//      tm.displayText("hello");
      Serial.println("case 2");
    break;

    case 3:
    Serial.println("caso 3");
//    char strkp[4] = " KP ";
//    char dest3[8];
//    sprintf(dest3,"%s%4f",strkp, kp);
//    tm.displayText(dest3);
    break;

    case 4:
     Serial.println("caso 4");
    //char strti[4] = " tI ";
    //char dest4[8];
    //sprintf(dest4,"%s%04i",strti, Ti);
    tm.displayText("hell");
    break;

    case 5:
     Serial.println("caso 5");
    char strtd[4] = " td ";
    char dest5[8];
    sprintf(dest5,"%s%04i",strtd, Td);
    tm.displayText(dest5);
    break;    
  }
  delay(1000);
}
}
