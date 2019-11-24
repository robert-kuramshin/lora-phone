#include "Arduino.h"

#include <Wire.h>
#include "SPI.h"

#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "heltec.h"

#include "lora-phone.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

// For the ESP-WROVER_KIT, these are the default.
#define TFT_CS   4
#define TFT_DC   15
#define TFT_MOSI 32
#define TFT_CLK  33
#define TFT_RST  2
#define TFT_MISO 23
#define TFT_LED   22  // GPIO not managed by library

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void backlighting(bool state) {
  if (state) {
    digitalWrite(TFT_LED, LOW);
  }
  else {
    digitalWrite(TFT_LED, HIGH);
  }
}

void setup() {
  Serial.begin(115200);

  Heltec.begin(false /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /**/);

  
  keyboardSetup();

  tft.begin();
  pinMode(TFT_LED, OUTPUT);
  backlighting(false);

  tft.setRotation(3);
  resetScreen();
}

void loop() {
  char res = scanKeyboard();
  static char last_res;
  if (res != '\0' && last_res == '\0')
  {
    tft.print(res);
    if(res == '\n')
    {
      loraSend("test");
    }
  }
  last_res = res;
  delay(100);
}

void resetScreen() {
  tft.fillScreen(ILI9341_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
}

void loraSend(char* messsage)
{
    LoRa.beginPacket();
    LoRa.print(messsage);
    LoRa.endPacket();
}
