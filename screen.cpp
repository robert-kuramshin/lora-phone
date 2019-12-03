#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "lora-phone.h"

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
  tft.setCursor(0,tft.height()-TEXT_HEIGHT);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(FONT_SIZE);
}

void resetWriteArea() {
  tft.fillRect(0,tft.height()-TEXT_HEIGHT, tft.width(), TEXT_HEIGHT, ILI9341_BLACK);
  tft.setCursor(0,tft.height()-TEXT_HEIGHT);
  tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(FONT_SIZE);

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

void screenWriteAt(char * mes,int x,int y)
{
    tft.setCursor(x,y);
    tft.print(mes);
}

void screenWriteChar(char mes)
{
    tft.print(mes);
}

void splashScreen()
{
    tft.setCursor(0,tft.height()/2);
    tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
    tft.print("LORA-PHONE\n");
    tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(FONT_SIZE);
    tft.print("by: Robert Kuramshin");
}

void userNameScreen()
{
    tft.setCursor(0,0);
    tft.setTextColor(ILI9341_RED);    tft.setTextSize(FONT_SIZE);
    tft.print("Enter a username: ");
    tft.setTextColor(ILI9341_WHITE);    tft.setTextSize(FONT_SIZE);
}

int screenWidth()
{
  return tft.width();
}

int screenHeight()
{
  return tft.height();
}
