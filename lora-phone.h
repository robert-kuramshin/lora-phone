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