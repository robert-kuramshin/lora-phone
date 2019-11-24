#include "Arduino.h"

#include "lora-phone.h"

char *username;
int currentLine = 0;

void setup()
{
  Serial.begin(115200);

  loraSetup();

  keyboardSetup();

  screenSetup();

  splashScreen();
  delay(2000);
  resetScreen();

  // if username not in eeprom
  userNameScreen();

  bool complete = false;
  username = (char *)calloc(20, sizeof(char));
  int count = 0;

  while (!complete)
  {
    char res = scanKeyboard();
    static char last_res;
    if (res != '\0' && last_res == '\0')
    {
      if (res == '\n')
      {
        complete = true;
      }

      screenWriteChar(res);
      username[count++] = res;
    }
    last_res = res;
    delay(10);
  }

  resetScreen();
  clearWritingArea();
}

void loop()
{
  char res = scanKeyboard();
  static char last_res;
  static char *message = (char *)calloc(20, sizeof(char));
  int count = 0;

  if (res != '\0' && last_res == '\0')
  {
    if (res == '\n')
    {
      message[count++] = '\0';
      loraSend(message);
      clearWritingArea();
      return;
    }
    else if (res == '\b')
    {
      clearWritingArea();
      message[--count] = '\0';
      screenWrite(message);
    }
    else
    {
      screenWriteChar(res);
      message[count++] = res;
    }
  }
  last_res = res;
  delay(100);
}

void clearWritingArea()
{
  resetWriteArea();
  screenWrite(username);
  screenWrite(": ");
}

void checkIncoming()
{
  char* message = loraRead();
  int y = (currentLine++)*8;
  screenWriteAt(message,0,y);
  free(message);
}
