#include <TM1638plus.h>
#define STROBE_TM 4
#define CLOCK_TM 6
#define DIO_TM 7
uint8_t MainMode = 2;
unsigned long previousMillis = 0;
const long  interval  = 225; // interval at which to debounce button readback function(milliseconds)

int ref = 30;
float kp = 2;
int Ti = 50;
int Td = 30;

TM1638plus tm(STROBE_TM, CLOCK_TM, DIO_TM);
//PreciseLM35 lm35(pinLM35, INTERNAL1V1, arefRatio); //MEGA
//PreciseLM35 lm35(pinLM35, INTERNAL, arefRatio); //UNO

void setup() {
  tm.reset();
  Serial.begin(9600);
}

void loop() {
  Serial.println("Lazo principal");
MainMenu();
}

/*
 * El menu principal es el que da la funcionalidad a los botones para cambiar de hoja y mostrar
 * otras opciones, la principal es mostrar temperatura actual y setpoint, la siguiente el setpoint,
 * luego siguen los parametros kp, ti y td en pestañas distintas.
 * Al presionar el boton de configuracion se hace una llamada a una funcion que deja en un lazo al display
 * mostrando el nombre del parametro y el valor a ajustar, se habilitan los botones cancelar, aceptar, subir
 * y bajar.
 */

void MainMenu(void)
{
  uint8_t buttons = buttonsRead();

  switch (buttons)
  {
    case 0x02:
      MainMode = (MainMode-1) % 5;
      Display(MainMode);
      break;
    case 0x04:
      MainMode = 2;
      Display(MainMode);
      settingsREF();
      Serial.print(MainMode);
      Serial.print("\t");
      Serial.println("settingsREF");
      break;
    case 0x08:
      MainMode = 3;
      Display(MainMode);
      settingsKP();
      Serial.print(MainMode);
      Serial.print("\t");
      Serial.println("settingsREF");
      break;
    case 0x10:
      MainMode = 4;
      Display(MainMode);
      settingsTI();
      break;
    case 0x20:
      MainMode = 5;
      Display(MainMode);
      settingsTD();
      break;
    case 0x40:
      MainMode = (MainMode+1) % 5;
      Display(MainMode);
      break;
  }

  Display(MainMode);
  Serial.print(MainMode);
      Serial.print("\t");
      Serial.print("dibujar menu");
  }

/* 
 *  El menu para setear la referencia tiene las cuatro opciones antes mencionadas y permite ver
 *  en tiempo real el valor que tomará la referencia, solo se envia al controlador cuando
 *  se presiona OK, se realiza una llamada a la funcion setREF.
 */

void settingsREF(void)
{
  Serial.print(MainMode);
      Serial.print("\t");
  Serial.println("rutina settingsREF");
  boolean estado = 0;
  while (1)
  {
    Display(MainMode);
    Serial.print(MainMode);
      Serial.print("\t");
    Serial.println("while");
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case 0x01 : estado = 1; break;
      case 0x08 : ref--; break;
      case 0x10 : ref++; break;
      case 0x80 : setREF(ref); estado = 1; break;
    }
    if (estado == 1) break;
  }
}



void setREF(uint8_t ref)
{
  // tiene que enviar un valor entero al controlador
}

void settingsKP(void)
{
  boolean estado = 0;
  while (1)
  {
    Display(MainMode);
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case 0x01 : estado = 1; break;
      case 0x08 : kp--; break;
      case 0x10 : kp++; break;
      case 0x80 : setKP(kp); estado = 1; break;
    }
    if (estado == 1) break;
  }
}

void setKP(float kp)
{
  
}

void settingsTI(void)
{
  boolean estado = 0;
  while (1)
  {
    Display(MainMode);
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case 0x01 : estado = 1; break;
      case 0x08 : Ti--; break;
      case 0x10 : Ti++; break;
      case 0x80 : setTI(Ti); estado = 1; break;
    }
    if (estado == 1) break;
  }
}

void setTI(uint8_t Ti)
{
  
}

void settingsTD(void)
{
  boolean estado = 0;
  while (1)
  {
    Display(MainMode);
    uint8_t buttons = buttonsRead();
    switch (buttons)
    {
      case 0x01 : estado = 1; break;
      case 0x08 : Td--; break;
      case 0x10 : Td++; break;
      case 0x80 : setTD(Td); estado = 1; break;
    }
    if (estado == 1) break;
  }
}

void setTD(uint8_t Td)
{
  
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

void Display(uint8_t DisplayMode)
{
  Serial.print("MAIN MODE DISPLAY");
  Serial.print("\t");
  Serial.println(MainMode);
  switch (MainMode)
  {
    case 1 :
    Serial.println("caso 1");
    int temp = analogRead(A0);
    char dest1[8];
    sprintf(dest1,"%04i%04i",temp,ref);
    tm.displayText(dest1);
    break;

    case 2:
//    char setpoint[1] = "set ";
//    char dest2[8];
//    sprintf(dest2,"%s%04i",setpoint,ref);
//    Serial.println(dest2);
//    tm.displayText(dest2);
      tm.displayText("hello");
      Serial.println("case 2");
    break;

    case 3:
    Serial.println("caso 3");
    char strkp[4] = " KP ";
    char dest3[8];
    sprintf(dest3,"%s%4f",strkp, kp);
    tm.displayText(dest3);
    break;

    case 4:
    char strti[4] = " tI ";
    char dest4[8];
    sprintf(dest4,"%s%04i",strti, Ti);
    tm.displayText(dest4);
    break;

    case 5:
    char strtd[4] = " td ";
    char dest5[8];
    sprintf(dest5,"%s%04i",strtd, Td);
    tm.displayText(dest5);
    break;    
  }
}

//void Parametros(uint8_t set float kp uint8_t Ti uint8_t Td)
//{
//  pid(set,kp,ti,td)
//}
