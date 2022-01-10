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
    char ID[] = "";
    char DLC[] = "";
    char Data[] = "" ;
    for(int i = 0 ; i < 3 ; i++){
         printf("%c\n",str1[i+2]);
         ID[i] = str1[i+2];
         DLC[i] = str1[5];
    }
     printf("%s\n",ID);
      printf("%s\n",DLC);

    for (int i = 6 ; i < strlen(str1);i++ ){
        Data[i - 6] = str1[i] ; 
    }
     printf("%s\n",Data);
}
