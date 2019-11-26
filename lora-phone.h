
#define FONT_SIZE   2

#define TEXT_HEIGHT (8*FONT_SIZE)
#define TEXT_WIDTH  (5*FONT_SIZE)

#define USERNAME_LENGTH 8

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

void loraSend(char* messsage);

char * loraRead();