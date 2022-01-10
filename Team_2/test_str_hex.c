#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;
}
int main()
{
    init();
    char str1[] = "0x7503020310"; // string --> ID:750  DLC:3 DATA: 02 03 10
    printf("%s\n",str1);
    for (int i = 0;i<strlen(str1);i++)
    {
        printf("%c\n",str1[i]);
    }
    int num1  =(int)strtol(str1,NULL,16);
    int hex1 = 0x45;
    char temp[] ={0};
    sprintf(temp,"%x",hex1); // hex ->string
    printf("%s\n",temp);
    printf("\n%x",num1);
}