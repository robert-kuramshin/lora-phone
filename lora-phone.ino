#include "Arduino.h"

#include "lora-phone.h"

char *username;
int currentLine = 0;

void setup()
{
  Serial.begin(115200);

  loraSetup();

#ifndef HEADLESS
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
      } else {
        screenWriteChar(res);
        username[count++] = res;
      }
    }
    last_res = res;
    delay(10);
  }

  resetScreen();
  clearWritingArea();
#else
  Serial.println("\n\n\n\nLoRa Phone [HEADLESS]");
  Serial.println("Robert Kuramshin\n\n");
  
  username = (char *)calloc(20, sizeof(char));
  Serial.println("Enter a username: ");
  while(Serial.available() < 1)
  {
    delay(10);  
  }
  
  while (Serial.available())
  {
    String usernameS = Serial.readString();
    usernameS.toCharArray(username, usernameS.length());
  }
  Serial.print("Hello ");
  Serial.println(username);
#endif
}

void loop()
{
#ifndef HEADLESS
  char res = scanKeyboard();
  static char last_res;
  static char *message = (char *)calloc(20, sizeof(char));
  static int count = 0;

  if (res != '\0' && last_res == '\0')
  {
    if (res == '\n')
    {
      message[count++] = '\0';
      message_t msg;
      msg.user = username;
      msg.body = message;
      msg.length = strlen(message);
      loraSend(msg);
      printLeft(message);
      clearWritingArea();
      count = 0;
      return;
    }
    else if (res == '\b')
    {
      clearWritingArea();
      message[--count] = '\0';
      screenWrite(message);
    }
    else if (res == (char)MENU_KEY)
    {
      pcMode();
    }
    else
    {
      screenWriteChar(res);
      message[count++] = res;
    }
  }
  checkIncoming();
  last_res = res;
  delay(10);
#else
  pcMode();

#endif
}

void clearWritingArea()
{
  resetWriteArea();
  screenWrite(username);
  screenWrite(": ");
}

void checkIncoming()
{
  message_t *message = loraRead();
  if (message != NULL)
  {
    int y = (currentLine++) * TEXT_HEIGHT;
    screenWriteAt(message->user, 0, y);
    screenWriteAt(":", USERNAME_LENGTH, y);
    screenWriteAt(message->body, USERNAME_LENGTH + 1, y);
    free(message->user);
    free(message->body);
  }
}

void pcMode()
{
  char *message;
  while (true)
  {
//    char res = scanKeyboard();
//    if (res == (char)MENU_KEY)
//    {
//      return;
//    }
    while (Serial.available())
    {
      String messageString = Serial.readString();
      message = (char *)malloc(messageString.length());
      messageString.toCharArray(message, messageString.length());

      message_t response;
      response.user = username;
      response.body = message;
      response.length = strlen(message);
      loraSend(response);
      Serial.print(username);
      Serial.print(": ");
      Serial.println(message);
    }
    message_t *message = loraRead();
    if (message != NULL)
    {
      Serial.print(message->user);
      Serial.print(": ");
      Serial.println(message->body);
      free(message->user);
      free(message->body);
      free(message);
    }
    delay(10);
  }
}

void printLeft(char * message)
{
  int y = (currentLine++) * TEXT_HEIGHT;
  screenWriteAt(username, 0, y);
  screenWriteAt(": ", (strlen(username) + 1)*TEXT_WIDTH, y);
  screenWriteAt(message, (strlen(username) + 3)*TEXT_WIDTH, y);
}
