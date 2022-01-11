#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>

#define CAN_FRAME_MAX_DATA_LEN 8
struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[CAN_FRAME_MAX_DATA_LEN];
};
struct can_frame canMsg1;
void init()
{
  canMsg1.can_id  = 0x758;
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;
}

int main()
{
    char can_frame[11] = {0};
    init();
    uint32_t res = 0x758 & 0xFF0;
    uint32_t mod = 0x758 - res;
    res = res >> 4;
    printf("%x  %x",res,mod);
    can_frame[0] = res;
    can_frame[1] = mod; 
    can_frame[2] = canMsg1.can_dlc;
    can_frame[3] = canMsg1.data[0];
    can_frame[4] = canMsg1.data[1];
    can_frame[5] = canMsg1.data[2];
    can_frame[6] = canMsg1.data[3];

    printf("CAN Transmission: ");
    for(int i = 0;i<strlen(can_frame);i++)
    {
        printf("%02x ",can_frame[i]);
    }
    printf("\n");
}