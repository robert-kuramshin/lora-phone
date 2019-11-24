#include "Arduino.h"
#include "Wire.h"
#include "lora-phone.h"

#define MCP23017_ID 0x20

#define ROW_1 0
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3
#define ROW_5 4
#define ROW_6 5
#define ROW_7 6

#define COL_1 0
#define COL_2 1
#define COL_3 2
#define COL_4 3
#define COL_5 4

static void allHigh()
{
    Wire.beginTransmission(MCP23017_ID);
    Wire.write(0x12); // address bank A
    Wire.write(0xFF); // value to send - all HIGH
    Wire.endTransmission();
}

static void setupMCP()
{
    Serial.begin(115200);
    Wire.begin(25, 21);
    Wire.beginTransmission(MCP23017_ID);
    Wire.write(0x00); // IODIRA register
    Wire.write(0x00); // set all of port A to outputs
    Wire.endTransmission();

    Wire.beginTransmission(MCP23017_ID);
    Wire.write(0x01); // IODIRA register
    Wire.write(0xFF); // set all of port A to outputs
    Wire.endTransmission();

    Wire.beginTransmission(MCP23017_ID);
    Wire.write(0x0D); // IODIRA register
    Wire.write(0xFF); // set all of port A to outputs
    Wire.endTransmission();

    allHigh();
}

static void setLow(byte row)
{
    Wire.beginTransmission(MCP23017_ID);
    Wire.write(0x12);        // address bank A
    Wire.write(~(1 << row)); // value to send - all HIGH
    Wire.endTransmission();
}

static byte readAll()
{
    Wire.beginTransmission(MCP23017_ID); // select device with "beginTransmission()"
    Wire.write(0x13);                    // select starting register with "write()"
    Wire.endTransmission();              // end write operation, as we just wanted to select the starting register
    Wire.requestFrom(MCP23017_ID, 1);    // select number of bytes to get from the device (2 bytes in this case)
    return 0x1F & Wire.read();           // read from the starting register
}

char keyboardSetup()
{
    setupMCP();
}

char scanKeyboard()
{
    int res;
    setLow(ROW_1);
    res = readAll();
    res = (~res) & 0x1F;
    if ((res) & (1 << COL_1))
        return 'Q';
    if ((res) & (1 << COL_2))
        return 'E';
    if ((res) & (1 << COL_3))
        return 'R';
    if ((res) & (1 << COL_4))
        return 'U';
    if ((res) & (1 << COL_5))
        return 'O';

    setLow(ROW_2);
    res = readAll();
    res = (~res) & 0x1F;
    if ((res) & (1 << COL_1))
        return 'W';
    if ((res) & (1 << COL_2))
        return 'S';
    if ((res) & (1 << COL_3))
        return 'G';
    if ((res) & (1 << COL_4))
        return 'H';
    if ((res) & (1 << COL_5))
        return 'L';

    setLow(ROW_3);
    res = readAll();
    res = (~res) & 0x1F;
    //  if((res) & (1<<COL_1)) return 'SYM';
    if ((res) & (1 << COL_2))
        return 'D';
    if ((res) & (1 << COL_3))
        return 'T';
    if ((res) & (1 << COL_4))
        return 'Y';
    if ((res) & (1 << COL_5))
        return 'I';

    setLow(ROW_4);
    res = readAll();
    res = (~res) & 0x1F;
    if ((res) & (1 << COL_1))
        return 'A';
    if ((res) & (1 << COL_2))
        return 'P';
    //  if((res) & (1<<COL_3)) return 'R';Right up
    if ((res) & (1 << COL_4))
        return '\n'; //enter
    if ((res) & (1 << COL_5))
        return '\b'; //backspace

    setLow(ROW_5);
    res = readAll();
    res = (~res) & 0x1F;
    //  if((res) & (1<<COL_1)) return 'alt';
    if ((res) & (1 << COL_2))
        return 'X';
    if ((res) & (1 << COL_3))
        return 'V';
    if ((res) & (1 << COL_4))
        return 'B';
    if ((res) & (1 << COL_5))
        return '$';

    setLow(ROW_6);
    res = readAll();
    res = (~res) & 0x1F;
    if ((res) & (1 << COL_1))
        return ' ';
    if ((res) & (1 << COL_2))
        return 'Z';
    if ((res) & (1 << COL_3))
        return 'C';
    if ((res) & (1 << COL_4))
        return 'N';
    if ((res) & (1 << COL_5))
        return 'M';

    setLow(ROW_7);
    res = readAll();
    res = (~res) & 0x1F;
    //  if((res) & (1<<COL_1)) return 'MIC';
    //  if((res) & (1<<COL_2)) return 'S'; left shift
    if ((res) & (1 << COL_3))
        return 'F';
    if ((res) & (1 << COL_4))
        return 'J';
    if ((res) & (1 << COL_5))
        return 'K';

    return '\0';
}
