
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
