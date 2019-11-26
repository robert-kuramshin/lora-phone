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
      message_t res;
      res.user = username;
      res.body = message;
      res.length = strlen(message);
      loraSend(res);
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
  message_t message = loraRead();
  int y = (currentLine++)*TEXT_HEIGHT;
  screenWriteAt(message.user,0,y);
  screenWriteAt(":",USERNAME_LENGTH,y);
  screenWriteAt(message.body,USERNAME_LENGTH+1,y);
  free(message.user);
  free(message.body);
}
