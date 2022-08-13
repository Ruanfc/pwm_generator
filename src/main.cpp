#include <Arduino.h>

float pwmxval = 0;
float pwmyval = 0;
int x_pin = 11;
int y_pin = 10;
unsigned long time = 0;
String inputStr = "";
#define INTERVAL 100
void setup()
{
  Serial.begin(9600);
  pinMode(x_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);

}

void newcheck()
{
    // analogWrite(x_pin, pwmxval);
    // analogWrite(y_pin, pwmyval);
    Serial.print(pwmxval, pwmyval);
}

void loop()
{
  unsigned long newtime = millis();
  if ((newtime - time) > INTERVAL)
  {
    newcheck();
    time = millis();
  }

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

      pwmxval = (pwmxStr.toFloat());
      pwmyval = (pwmyStr.toFloat());
    }
  }
}
