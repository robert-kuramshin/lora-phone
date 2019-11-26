
#ifndef LORA_PHONE_H_
#define LORA_PHONE_H_

#define FONT_SIZE   2

#define TEXT_HEIGHT (8*FONT_SIZE)
#define TEXT_WIDTH  (5*FONT_SIZE)

#define USERNAME_LENGTH 8

typedef struct lora_message
{
    char * user;
    char * body;
    uint8_t length;
} message_t;

//------------------------------------------

char keyboardSetup();

char scanKeyboard();

//------------------------------------------
void resetScreen();

void screenSetup();

void screenWrite(char * mes);

void screenWriteChar(char mes);

void splashScreen();

void userNameScreen();

void resetWriteArea();

void screenWriteAt(char * mes,int x,int y);

//------------------------------------------

void loraSetup();

void loraSend(message_t messsage);

message_t loraRead();

#endif