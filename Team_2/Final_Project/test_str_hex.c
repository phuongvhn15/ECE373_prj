#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <string.h>
#define CAN_FRAME_MAX_DATA_LEN 8
#define CAN_FRAME_MAX_BITS 128

struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[CAN_FRAME_MAX_DATA_LEN];
};
struct can_frame canMsg1;
void init()
{
  canMsg1.can_id  = 0x750;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;
  canMsg1.data[3] = 0x01;
  canMsg1.data[4] = 0x00;
  canMsg1.data[5] = 0xED;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;
}
int main()
{
  init();
  char can_id[128]={0};
  char can_dlc[128];
  char can_data[128]={0};
  char can_frame[128]={0};
  sprintf(can_id,"%x",canMsg1.can_id);
  printf("CAN ID: %s\n",can_id);
  sprintf(can_dlc,"%d",canMsg1.can_dlc);
  printf("CAN DLC: %s\n",can_dlc);
  for(int i=0;i<8;i++)
  {
    char temp[2] = {0};
    sprintf(temp,"%02x",canMsg1.data[i]);
    strcat(can_data,temp);
  }
  printf("CAN DATA: %s\n",can_data);
  strcat(can_frame,can_id);
  strcat(can_frame,can_dlc);
  strcat(can_frame,can_data);
  printf("CAN FRAME: %s",can_frame);
  printf("%d",strlen(can_frame));
  return 0;
}