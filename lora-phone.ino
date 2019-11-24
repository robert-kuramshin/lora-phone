#include "Arduino.h"

#include "lora-phone.h"

void setup() {
  Serial.begin(115200);

  loraSetup();
  
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