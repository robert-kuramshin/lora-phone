#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "SPI.h"

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

void resetScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(tft.width()-15,tft.height()-24);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(3);
}

void resetWriteArea() {
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(tft.width()-15,tft.height()-24, 15, 24, ILI9341_BLACK);
  tft.setCursor(tft.width()-15,tft.height()-24);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(3);

}

void screenSetup()
{
  tft.begin();
  pinMode(TFT_LED, OUTPUT);
  backlighting(false);

  tft.setRotation(3);
}

void screenWrite(char * mes)
{
    tft.print(mes);
}

void screenWriteChar(char mes)
{
    tft.print(mes);
}

void splashScreen()
{
    tft.setCursor(tft.width()/2,tft.height()/2);
    tft.setTextColor(ILI9341_RED);    tft.setTextSize(1);
    tft.print("LORA-PHONE");
    tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(3);
    tft.print("by: Robert Kuramshin");
}

void userNameScreen()
{
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
    tft.print("Enter a username: ");
    tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(3);
}