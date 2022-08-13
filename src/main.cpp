#include <Arduino.h>

int x = 0;
int y = 0;
//timer 1 pins
// int RF_pin = 10;
// int RB_pin = 9;
//timer 0 pins
int RF_pin = 6;
int RB_pin = 5;
//timer 2 pins
int LF_pin = 11;
int LB_pin = 3;

unsigned long time = 0;
String inputStr = "";
#define INTERVAL 100
#define MEIO 127
void setup()
{
  Serial.begin(9600);
  pinMode(LF_pin, OUTPUT);
  pinMode(LB_pin, OUTPUT);
  pinMode(RF_pin, OUTPUT);
  pinMode(RB_pin, OUTPUT);

  TCCR0B = _BV(CS21);
  TCCR2B = _BV(CS21);
}

void newcheck()
{

	int valorL = y+x;
	int valorR = y-x;
	int _y = abs(y);
	int _x = abs(x);
	int modulo = _y - _x;
	// int _y_x = abs(modulo);
	if ((x^y) < 0) valorR += (modulo < 0) ? -y : x;
	else valorL -= (modulo < 0) ? y : x;
  Serial.print(valorL);
  Serial.print(";");
  Serial.print(valorR);
  Serial.println();

  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM20);
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM20);
  OCR0A = MEIO + (valorR >> 2);
  OCR0B = MEIO - (valorR >> 2);
  OCR2A = MEIO + (valorL >> 2);
  OCR2B = MEIO - (valorL >> 2);
}

void loop()
{
  // unsigned long newtime = millis();
  // if ((newtime - time) > INTERVAL)
  // {
  //   newcheck();
  //   time = millis();
  // }

}

void serialEvent()
{
  if (Serial.available()) {
    inputStr = Serial.readString();
    //int len = sizeof(inputStr);

    // Remove b' vindo da aplicação em python
    inputStr.replace("b'","");
    
    // Dá split na string recebida
    int dotcommaIndex = inputStr.indexOf(";");
    if (dotcommaIndex > 0) {
      String pwmxStr = inputStr.substring(0, dotcommaIndex);
      String pwmyStr = inputStr.substring(dotcommaIndex + 1);

      // x = (pwmxStr.toFloat());
      // y = (pwmyStr.toFloat());
      x = (pwmxStr.toInt());
      y = (pwmyStr.toInt());
    }
    newcheck();
  }
}
