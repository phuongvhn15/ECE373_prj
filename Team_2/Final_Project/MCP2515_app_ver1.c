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
  canMsg1.can_id  = 0x58;
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;

  canMsg2.can_id  = 0x58;
  canMsg2.can_dlc = 3;
  canMsg2.data[0] = 0x02;
  canMsg2.data[1] = 0x10;
  canMsg2.data[2] = 0x03;

  canMsg3.can_id  = 0x58;
  canMsg3.can_dlc = 4;
  canMsg3.data[0] = 0x03;
  canMsg3.data[1] = 0x22;
  canMsg3.data[2] = 0xF1;
  canMsg3.data[3] = 0x00;

  canMsg4.can_id  = 0x58;
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = 0x03;
  canMsg4.data[1] = 0x22;
  canMsg4.data[2] = 0xF1;
  canMsg4.data[3] = 0x80;

  canMsg5.can_id  = 0x58;
  canMsg5.can_dlc = 4;
  canMsg5.data[0] = 0x03;
  canMsg5.data[1] = 0x22;
  canMsg5.data[2] = 0xF1;
  canMsg5.data[3] = 0x81;

  canMsg6.can_id  = 0x58;
  canMsg6.can_dlc = 4;
  canMsg6.data[0] = 0x03;
  canMsg6.data[1] = 0x22;
  canMsg6.data[2] = 0xF1;
  canMsg6.data[3] = 0x82;

  canMsg7.can_id  = 0x60;
  canMsg7.can_dlc = 4;
  canMsg7.data[0] = 0x03;
  canMsg7.data[1] = 0x22;
  canMsg7.data[2] = 0xF1;
  canMsg7.data[3] = 0x00;

  canMsg8.can_id  = 0x60;
  canMsg8.can_dlc = 4;
  canMsg8.data[0] = 0x03;
  canMsg8.data[1] = 0x22;
  canMsg8.data[2] = 0xF1;
  canMsg8.data[3] = 0x90;

  canMsg9.can_id  = 0x60;
  canMsg9.can_dlc = 4;
  canMsg9.data[0] = 0x03;
  canMsg9.data[1] = 0x22;
  canMsg9.data[2] = 0xF1;
  canMsg9.data[3] = 0x91;

  canMsg10.can_id  = 0x60;
  canMsg10.can_dlc = 4;
  canMsg10.data[0] = 0x03;
  canMsg10.data[1] = 0x22;
  canMsg10.data[2] = 0xF1;
  canMsg10.data[3] = 0x92;

  canMsg11.can_id  = 0x50;
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

  canMsg16.can_id  = 0x58;
  canMsg16.can_dlc = 3;
  canMsg16.data[0] = 0x02;
  canMsg16.data[1] = 0x11;
  canMsg16.data[2] = 0x01;
}
void menu()
{
    printf("===========MENU============\n");
    printf("1.  Session control 01\n");
    printf("2.  Session control 03\n");
    printf("3.  Read ECU voltage engine\n");
    printf("4.  Read temperature engine\n");
    printf("5.  Read odometer engine\n");
    printf("6.  Read velocity engine\n");
    printf("7.  Read ECU voltage radar\n");
    printf("8.  Read angel azimuth radar\n");
    printf("9.  Object detection radar\n");
    printf("10. Warning detection radar\n");
    printf("11. Write angel azimuth radar\n");
    printf("12. Read DTC\n");
    printf("13. Clear diagnostic\n");
    printf("14. Request seed\n");
    printf("15. Send seed\n");
    printf("16. ECU reset\n");
    printf("=======================\n");
}

void displayMessageCAN(char *buffer){
    for(int i = 0; i < sizeof(buffer) + 2; i++){
        printf("%02x ", buffer[i]);
    }
}
void clearBuffer(char *can_frame, char *rx_frame)
{
    for (int i=0; i<sizeof(can_frame)+2;i++)
    {
        can_frame[i]  = 0x00;
        rx_frame[i]  = 0x00;
    }
}
int main(int argc, char **argv)
{
    char *app_name = argv[0];
    //char *dev_name = "/dev/mcp2515_dev_ver2d";
    int fd = -1;
    char c;
    int select = 0;
    char con;
    char can_frame[11]={0};
    char rx_frame[11] = {0};
    init();
//     if ((fd = open(dev_name,O_RDWR)) < 0 )
// {
//     fprintf(stderr, "%s: unable to open %s: %s\n", app_name, dev_name, strerror(errno));		
//     return( 1 );
// }

    do{
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
            can_fram[0] = canmsg.can_id 
            can_frame[1] = canMsg1.can_dlc;
            can_frame[2] = canMsg1.data[0];
            can_frame[3] = canMsg1.data[1];
            can_frame[4] = canMsg1.data[2];

            write(fd, can_frame, 10);
            read(fd, rx_frame, 10);
        }
        else if(select == 2)
        {
            can_frame[0] = canmsg.can_id
            can_frame[1] = canMsg2.can_dlc;
            can_frame[2] = canMsg2.data[0];
            can_frame[3] = canMsg2.data[1];
            can_frame[4] = canMsg2.data[2];

            write(fd, can_frame, 10);
            read(fd, rx_frame, 10);
        }
        else if(select == 3)
        {
           for (int i =0;i<canMsg3.can_dlc;i++)
            {
                printf("%02x  ",canMsg3.data[i]);
            }
        }

        else if(select == 4 ){
          for (int i =0;i<canMsg4.can_dlc;i++)
            {
                printf("%02x  ",canMsg4.data[i]);
            }
        }
        else if(select == 5){
          for (int i =0;i<canMsg5.can_dlc;i++)
            {
                printf("%02x  ",canMsg5.data[i]);
            }
        }
        else if(select == 6){
          for (int i =0;i<canMsg6.can_dlc;i++)
            {
                printf("%02x  ",canMsg6.data[i]);
            }
        }
        else if(select == 7)
        {
  
             for (int i =0;i<canMsg7.can_dlc;i++)
            {
                printf("%02x  ",canMsg7.data[i]);
            }
        }
        else if(select == 8 ){
          for (int i =0;i<canMsg8.can_dlc;i++)
            {
                printf("%02x  ",canMsg8.data[i]);
            }
        }
        else if(select == 16)
       {
            can_fram[0] = canmsg.can_id ;
            can_frame[1] = canMsg8.can_dlc; 
            can_frame[2] = canMsg16.data[0];
            can_frame[3] = canMsg16.data[1];
            can_frame[4] = canMsg16.data[2];

            write(fd, can_frame, 10);
            read(fd, rx_frame, 10);
        }
        printf("CAN Transmission: ");
        displayMessageCAN(can_frame);
        printf("\n");
        printf("CAN Response: ");
        displayMessageCAN(rx_frame);
        printf("\n");

        clearBuffer(can_frame,rx_frame);

        printf("\nDo you want to continue? Y or N: ");
        scanf(" %c",&con);
    } while ( con =='Y'|| con =='y' );
    printf("========OUT==========");
    return 0;
}