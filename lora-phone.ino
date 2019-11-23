#include <Wire.h>

#define ROW_1  0
#define ROW_2  1
#define ROW_3  2
#define ROW_4  3
#define ROW_5  4
#define ROW_6  5
#define ROW_7  6

#define COL_1  0
#define COL_2  1
#define COL_3  2
#define COL_4  3
#define COL_5  4

void setup() {
  Serial.begin(115200);
  keyboardSetup();
}



void loop() {
  Serial.println(scanKeyboard());
  delay(100);
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
//   Serial.println(res);
   if((res) & (1<<COL_1)) return 'Q';
   if((res) & (1<<COL_2)) return 'E';
   if((res) & (1<<COL_3)) return 'R';
   if((res) & (1<<COL_4)) return 'U';
   if((res) & (1<<COL_5)) return 'O';
   return '\0';
}

void setupMCP()
{
  Serial.begin(115200);
  Wire.begin(25, 21);
  Wire.beginTransmission(0x20);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // set all of port A to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x01); // IODIRA register
  Wire.write(0xFF); // set all of port A to outputs
  Wire.endTransmission();

  Wire.beginTransmission(0x20);
  Wire.write(0x0D); // IODIRA register
  Wire.write(0xFF); // set all of port A to outputs
  Wire.endTransmission();

  allHigh();
}


void allHigh()
{
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address bank A
  Wire.write(0xFF); // value to send - all HIGH
  Wire.endTransmission();
}

void setLow(byte row)
{
  Wire.beginTransmission(0x20);
  Wire.write(0x12); // address bank A
  Wire.write(~(1 << row)); // value to send - all HIGH
  Wire.endTransmission();
}

byte readAll()
{
  Wire.beginTransmission(0x20); // select device with "beginTransmission()"
  Wire.write(0x13); // select starting register with "write()"
  Wire.endTransmission(); // end write operation, as we just wanted to select the starting register
  Wire.requestFrom(0x20, 1); // select number of bytes to get from the device (2 bytes in this case)
  return 0x1F & Wire.read(); // read from the starting register
}
