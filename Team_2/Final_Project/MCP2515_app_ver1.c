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
#define CAN_FRAME_MAX_BITS 128

struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[CAN_FRAME_MAX_DATA_LEN];
};

struct can_frame canMsg1;
struct can_frame canMsg2;
struct can_frame canMsg3;
struct can_frame canMsg4;
struct can_frame canMsg5;
struct can_frame canMsg6;
struct can_frame canMsg7;
struct can_frame canMsg8;
struct can_frame canMsg9;
struct can_frame canMsg10;
struct can_frame canMsg11;
struct can_frame canMsg12;
struct can_frame canMsg13;
struct can_frame canMsg14;
struct can_frame canMsg15;
struct can_frame canMsg16;
void init()
{
  canMsg1.can_id  = 0x750;
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;

  canMsg2.can_id  = 0x750;
  canMsg2.can_dlc = 3;
  canMsg2.data[0] = 0x02;
  canMsg2.data[1] = 0x10;
  canMsg2.data[2] = 0x03;

  canMsg3.can_id  = 0x750;
  canMsg3.can_dlc = 4;
  canMsg3.data[0] = 0x03;
  canMsg3.data[1] = 0x22;
  canMsg3.data[2] = 0xF1;
  canMsg3.data[3] = 0x00;

  canMsg4.can_id  = 0x750;
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = 0x03;
  canMsg4.data[1] = 0x22;
  canMsg4.data[2] = 0xF1;
  canMsg4.data[3] = 0x80;

  canMsg5.can_id  = 0x750;
  canMsg5.can_dlc = 4;
  canMsg5.data[0] = 0x03;
  canMsg5.data[1] = 0x22;
  canMsg5.data[2] = 0xF1;
  canMsg5.data[3] = 0x81;

  canMsg6.can_id  = 0x750;
  canMsg6.can_dlc = 4;
  canMsg6.data[0] = 0x03;
  canMsg6.data[1] = 0x22;
  canMsg6.data[2] = 0xF1;
  canMsg6.data[3] = 0x82;

  canMsg7.can_id  = 0x750;
  canMsg7.can_dlc = 4;
  canMsg7.data[0] = 0x03;
  canMsg7.data[1] = 0x22;
  canMsg7.data[2] = 0xF1;
  canMsg7.data[3] = 0x00;

  canMsg8.can_id  = 0x750;
  canMsg8.can_dlc = 4;
  canMsg8.data[0] = 0x03;
  canMsg8.data[1] = 0x22;
  canMsg8.data[2] = 0xF1;
  canMsg8.data[3] = 0x90;

  canMsg9.can_id  = 0x750;
  canMsg9.can_dlc = 4;
  canMsg9.data[0] = 0x03;
  canMsg9.data[1] = 0x22;
  canMsg9.data[2] = 0xF1;
  canMsg9.data[3] = 0x91;

  canMsg10.can_id  = 0x750;
  canMsg10.can_dlc = 4;
  canMsg10.data[0] = 0x03;
  canMsg10.data[1] = 0x22;
  canMsg10.data[2] = 0xF1;
  canMsg10.data[3] = 0x92;

  canMsg11.can_id  = 0x750;
  canMsg11.can_dlc = 4;
  canMsg11.data[0] = 0x03;
  canMsg11.data[1] = 0x2E;
  canMsg11.data[2] = 0xF1;
  canMsg11.data[3] = 0x90;

  canMsg12.can_id  = 0x0;
  canMsg12.can_dlc = 0x0;
  canMsg12.data[0] = 0x0;
  canMsg12.data[1] = 0x0;
  canMsg12.data[2] = 0x0;
  canMsg12.data[3] = 0x0;

  canMsg13.can_id  = 0x0;
  canMsg13.can_dlc = 0x0;
  canMsg13.data[0] = 0x0;
  canMsg13.data[1] = 0x0;
  canMsg13.data[2] = 0x0;
  canMsg13.data[3] = 0x0;

  canMsg14.can_id  = 0x0;
  canMsg14.can_dlc = 0x0;
  canMsg14.data[0] = 0x0;
  canMsg14.data[1] = 0x0;
  canMsg14.data[2] = 0x0;
  canMsg14.data[3] = 0x0;

  canMsg15.can_id  = 0x0;
  canMsg15.can_dlc = 0x0;
  canMsg15.data[0] = 0x0;
  canMsg15.data[1] = 0x0;
  canMsg15.data[2] = 0x0;
  canMsg15.data[3] = 0x0;

  canMsg16.can_id  = 0x750;
  canMsg16.can_dlc = 3;
  canMsg16.data[0] = 0x02;
  canMsg16.data[1] = 0x11;
  canMsg16.data[2] = 0x01;
}
void menu()
{
    printf("===========MENU============\n");
    printf("1. Session control 01\n");
    printf("2. Session control 03\n");
    printf("3. Read engine\n");
    printf("4. Read radar\n");
    printf("5. Write radar\n");
    printf("6. Read DTC\n");
    printf("7. Clear diagnostic\n");
    printf("8. Request seed\n");
    printf("9.ECU reset\n");
    printf("=======================\n");

}
int main()
{
    int select = 0;
    char con;
    init();
    do{
        system("cls");
        menu();
        printf("Enter your choice (1-->16): ");
        scanf("%d",&select);
        while(select<1 || select > 16)
        {
            printf("Error! Enter your choice (1-->16): ");
            scanf("%d",&select);
        }
        if(select == 1)
        {
            for (int i =0;i<canMsg1.can_dlc;i++)
            {
                printf("%02x  ",canMsg1.data[i]);
            }
        }
        else if(select == 3)
        {
            for (int i =0;i<canMsg3.can_dlc;i++)
            {
                printf("%02x  ",canMsg3.data[i]);
            }
        }
        else if(select == 16)
        {
            for (int i =0;i<canMsg16.can_dlc;i++)
            {
                printf("%02x  ",canMsg16.data[i]);
            }
        }
        printf("\nDo you want to continue? Y or N: ");
        scanf(" %c",&con);
    } while ( con =='Y'|| con =='y' );
    printf("========OUT==========");
    
    return 0;
}