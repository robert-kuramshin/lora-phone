#include "Arduino.h"

#include <Wire.h>
#include "SPI.h"

#include "heltec.h"

#include "lora-phone.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

void setup() {
  Serial.begin(115200);

  Heltec.begin(false /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /**/);
  
  keyboardSetup();

  screenSetup();
}

void loop() {
  char res = scanKeyboard();
  static char last_res;
  if (res != '\0' && last_res == '\0')
  {
    screenWriteChar(res);
    if(res == '\n')
    {
      loraSend("test");
    }
  }
  last_res = res;
  delay(100);
}

void loraSend(char* messsage)
{
    LoRa.beginPacket();
    LoRa.print(messsage);
    LoRa.endPacket();
}
