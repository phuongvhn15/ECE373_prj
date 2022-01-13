#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

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
  canMsg1.data[1] = 0xAA;
  canMsg1.data[2] = 0x01;
}
int main()
{
    char can_frame[4] = {0};
    // init();
    // uint64_t hexnum  = 0x0023992;
    // printf("%02X\n",hexnum);
    // can_frame[0] = canMsg1.can_id;
    // can_frame[1] = canMsg1.can_dlc;
    // can_frame[2] = canMsg1.data[0];
    // can_frame[3] = canMsg1.data[1];
    // can_frame[4] = canMsg1.data[2];
    // printf("%02x\n",can_frame[3]);
    // printf("CAN Transmission: ");
    // for(int i = 0;i<sizeof(can_frame);i++)
    // {
    //     printf("%02X ",(unsigned char)can_frame[i]);
    // }
    // unsigned int res = ((int)(hexnum & 0xFF000000)+(int)(hexnum & 0x00FF0000)+(int)(hexnum &0x0000FF00)+(int)(hexnum &0x000000FF));
    // res= res*0.01-180;
    // printf("%d\n",res);
    // int raw = (angel+180)/0.01;printf("%d\n",raw);
    // unsigned int raw4 = raw & 0x0000FF00;
    // printf("%x\n",raw4);
    // printf("\n");
    //  uint8_t subfunction = 0;
    //             printf("Enter the subfunction from 00-->07: ");
    //             scanf("%x",&subfunction);
    //             while(subfunction<0x00 || subfunction > 0x07)
    //             {
    //                 printf("Error! Enter subfunction from 0-->7: ");
    //                 scanf("%x",&subfunction);
    //             }
    // printf("%02X",subfunction);
    // can_frame[0] = 0x00;
    // can_frame[1] = 0x00;
    // can_frame[2] = 0x8C;
    // can_frame[3] = 0xA0;
    // for(int i =0;i<4;i++)
    // {
    //     printf("%d ",(unsigned char)can_frame[i]);
    // }
    // printf("\n");
    // unsigned int res = ((int)(can_frame[0] & 0xFF000000)//+(int)(can_frame[0] & 0x00FF0000)+
    //                 //(int)(can_frame[0] &0x0000FF00)+(int)(can_frame[0] &0x000000FF));
     int angel = 147;
     int res = (angel+180)/0.01+1;
     printf("%d\n",res);
    char ang_p1 = res/10000;
    char ang_p2 = (res-ang_p1*10000)/1000;
    char ang_p3 = (res-ang_p1*10000-ang_p2*1000)/100;
    char ang_p4 = (res-ang_p1*10000-ang_p2*1000-ang_p3*100)/10;
    printf("%02X %02X %02X %02X\n",ang_p1,ang_p2,ang_p3,ang_p4);
    can_frame[0] = ang_p1;
    can_frame[1] = ang_p2;
    can_frame[2] = ang_p3;
    can_frame[3] = ang_p4;
    int val = (int)(can_frame[0])*10000+(int)(can_frame[1])*1000+(int)(can_frame[2])*100+(int)(can_frame[3])*10;
    printf("%d\n",val);
    return 0;
}