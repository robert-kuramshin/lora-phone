
#include <stdint.h>
#include "heltec.h"

#include "lora-phone.h"

#define BAND    915E6  //you can set band here directly,e.g. 868E6,915E6

void loraSetup()
{
    Heltec.begin(false /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /**/);
}

uint8_t *encode(message_t message)
{
  int len = USERNAME_LENGTH + message.length;
  uint8_t *packet = (uint8_t *)malloc(len);
  memcpy(packet,message.user,USERNAME_LENGTH);
  memcpy(packet + USERNAME_LENGTH,message.body,strlen(message.body));
  return packet;
}

void loraSend(message_t message)
{
    LoRa.beginPacket();
    LoRa.write(encode(message),message.length);
    LoRa.endPacket();
}

message_t decode(char* message)
{
  message_t res;
  res.user = (char *)malloc(USERNAME_LENGTH);
  memcpy(res.user, message, USERNAME_LENGTH);
  int len = strlen(message+USERNAME_LENGTH);
  res.body = (char *)malloc(len);
  res.length = len;
  memcpy(res.body,message+USERNAME_LENGTH,len);

  return res;
}

message_t loraRead()
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
  message_t res = decode(message);
  free(message);
  return res;
}
