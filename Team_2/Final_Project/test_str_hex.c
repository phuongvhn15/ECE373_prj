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
  canMsg1.data[5] = 0x00;
  canMsg1.data[6] = 0x00;
  canMsg1.data[7] = 0x00;

}
int main()
{
    init();
    // char str1[] = "75030203100000000000"; // string --> ID:750  DLC:3 DATA: 02 03 10 00 00 00 00 00
    // printf("%s\n",str1);
    // for (int i = 0;i<strlen(str1);i++)
    // {
    //     printf("%c\n",str1[i]);
    // }
    // int num1  =(int)strtol(str1,NULL,16);
    // int hex1 = 0x45;
    // char temp[] ={0};
    // sprintf(temp,"%x",hex1); // hex ->string
    // printf("%s\n",temp);
    // printf("\n%x",num1);
    // char temp[] ={0};
    // char can_frame[50] = {0};
    // int hex = 0x32;
    // sprintf(can_frame[0],"%x",hex);
    // printf("%s   ",&can_frame[0]);
    // sprintf(can_frame[1],"%d",canMsg1.can_dlc);
    // printf("%s   ",can_frame[1]);
    // for(int i =0;i<8;i++)
    // {
    //     sprintf(&can_frame[i+2],"%02x",canMsg1.data[i]);
    //     printf("%s    ",can_frame[i+2]);
    // }
    // printf("%s\n",can_frame);
  char can_id[3];
  char can_dlc[1];
  char can_data[]
  for (int i =0;i<canMsg1.can_dlc;i++)
  {
    printf("%02x  ",canMsg1.data[i]);
  }
  printf("\n");
  for (int i =0;i<strlen(can_frame);i++)
  {
    printf("%c ",can_frame[i]);
  }
  printf("\n");
  sprintf(&can_frame,"%x",canMsg1.can_id);
  printf("%s",can_frame);
  return 0;
}