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
  canMsg1.data[3] = 0x00;

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
    printf("3. Read ECU voltage engine\n");
    printf("4. Read temperature engine\n");
    printf("5. Read odometer engine\n");
    printf("6. Read velocity engine\n");

    printf("7. Read ECU voltage radar\n");
    printf("8. Read angel azimuth radar\n");
    printf("9. Object detection radar\n");
    printf("10. Warning detection radar\n");

    printf("11. Write angel azimuth radar\n");

    printf("12. Read DTC\n");
    printf("13. Clear diagnostic\n");
    printf("14. Request seed\n");
    printf("15. Send seed\n");
    printf("16.ECU reset\n");
    printf("=======================\n");

}
int main(int argc, char **argv)
{
    char *app_name = argv[0];
    char *dev_name = "/dev/mcp2515_dev_ver2d";
    int fd = -1;
    char c;
    int select = 0;
    char con;
    char can_id={0};
    char can_dlc;
    char can_data[8]={0};
    char can_frame[10]={0};
    char rx_frame[10] = {0};
    init();
    if ((fd = open(dev_name,O_RDWR)) < 0 )
{
    fprintf(stderr, "%s: unable to open %s: %s\n", app_name, dev_name, strerror(errno));		
    return( 1 );
}

    do{
        //system("cls");
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
            // sprintf(can_id,"%x",canMsg1.can_id);
            // printf("CAN ID: %s\n",can_id);
            // sprintf(can_dlc,"%d",canMsg1.can_dlc);
            // printf("CAN DLC: %s\n",can_dlc);
            // for(int i=0;i<8;i++)
            // {
            //     char temp[2] = {0};
            //     sprintf(temp,"%02x",canMsg1.data[i]);
            //     strcat(can_data,temp);
            // }
            // printf("CAN DATA: %s\n",can_data);
            // strcat(can_frame,can_id);
            // strcat(can_frame,can_dlc);
            // strcat(can_frame,can_data);
            // printf("CAN FRAME: %s",can_frame);
            
            can_frame[0] = canMsg1.can_id;
            can_frame[1] = canMsg1.can_dlc;
            can_frame[2] = canMsg1.data[0];
            can_frame[3] = canMsg1.data[1];
            can_frame[4] = canMsg1.data[2];
            can_frame[5] = canMsg1.data[3];

            
            write(fd, can_frame, 10);
            printf("Sending can message: %s \n", can_frame);

            read(fd, rx_frame, 10);
            printf("Respond can message: %s", rx_frame);


            // char can_frame[10] = {0};
            // can_frame[0] = 0xf2;
            // can_frame[1] =  8;
            // can_frame[2] = 1;
            // can_frame[3] = 2;
            // can_frame[4] = 3;
            // can_frame[5] = 4;
            // can_frame[6] = 5;
            // can_frame[7] = 6;
            // can_frame[8] = 7;
            // can_frame[9] = 8;
            // printf("Sending CAN message");

            // //read(fd,can_frame,10);
            // write(fd,can_frame,10);

            // printf("CAN_MESSAGE %s: ", can_frame);
        }
        else if(select == 2)
        {
            for (int i =0;i<canMsg2.can_dlc;i++)
            {
                printf("%02x  ",canMsg2.data[i]);
            }
        }
        else if(select == 3)
        {
            for (int i =0;i<canMsg3.can_dlc;i++)
            {
                printf("%02x  ",canMsg3.data[i]);
            }
        }
        else if(select == 7)
        {
            for (int i =0;i<canMsg7.can_dlc;i++)
            {
                printf("%02x  ",canMsg7.data[i]);
            }
        }
        else if(select == 16)
        {
            for (int i =0;i<canMsg16.can_dlc;i++)
            {
                printf("%02x  ",canMsg16.data[i]);
            }
        }
        // strcpy(can_id,"0");
        // strcpy(can_dlc,"0");
        // strcpy(can_data,"0");
        // strcpy(can_frame,"0");
        printf("\nDo you want to continue? Y or N: ");
        scanf(" %c",&con);
    } while ( con =='Y'|| con =='y' );
    printf("========OUT==========");
    return 0;
}