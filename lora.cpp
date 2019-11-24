
#include "heltec.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

void loraSetup()
{
    Heltec.begin(false /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /**/);
}

void loraSend(char* messsage)
{
    LoRa.beginPacket();
    LoRa.print(messsage);
    LoRa.endPacket();
}

char * loraRead()
{
int packetSize = LoRa.parsePacket();
char *message = NULL;
int count = 0;
  if (packetSize) {
    message = (char *)calloc(packetSize,sizeof(char));
    while (LoRa.available()) {
      message[count++] = (char)LoRa.read();
    }
  }
  return message;
}
