#include <MePort.h>
#include <MeLEDMatrix.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeMCore.h>

MeIR ir;
MeBuzzer buzzer;
MeLEDMatrix Matrix_1(PORT_1);
char string_data[] = "MAKEBLOCK";
double count;
char s[5];
int lightValue;
uint8_t mensaje[16]=
{
                   0x00,
                   0x00,
                   0x00,
                   0x3F,
                   0x30,
                   0x30,
                   0x28,
                   0x24,
                   0x24,
                   0x28,
                   0x30,
                   0x30,
                   0x3F,
                   0x00,
                   0x00,
                   0x00,
};

void _delay(float seconds) {
  delay(seconds * 1000);
}

void scrollText(char *text, double scroll_delay, int mode)
{
    switch (mode) {
  
      case 0: // no scroll. Good to check the LED Matrix is working
        Matrix_1.drawStr(0,0+7,text);
        break;
      case 1:
        for(count = 0;count <(strlen(text)) * (9);++count) {
          _delay(scroll_delay);
          Matrix_1.drawStr((-1*count)+10,0+7,text);
        }
        break;

    }
}


void setup()
{
    ir.begin();
    Serial.begin(115200);
    Serial.setTimeout(1);
    Matrix_1.setColorIndex(1);
    Matrix_1.setBrightness(Brightness_6);
}



void loop()
{
  if (Serial.available())
  {
    String receivedString;
    receivedString = Serial.readStringUntil('\n');

    if (receivedString.length() > 0)
    {
      Matrix_1.clearScreen();
      Matrix_1.drawBitmap(0, 0, sizeof(mensaje), mensaje);
      delay(1000);
      Matrix_1.clearScreen();
      delay(1000);
      Matrix_1.drawBitmap(0, 0, sizeof(mensaje), mensaje);
      delay(1000);
      Matrix_1.clearScreen();
      scrollText(receivedString.c_str(), 0.1, 1);
  }
}
}
