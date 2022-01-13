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
uint8_t key[4]={0};
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

uint32_t ECU_id = 0x58;

void init()
{
  canMsg1.can_id  = ECU_id; //checked
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;

  canMsg2.can_id  = ECU_id; //checked
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

  canMsg11.can_id  = 0x60;
  canMsg11.can_dlc = 8;
  canMsg11.data[0] = 0x07;
  canMsg11.data[1] = 0x2E;
  canMsg11.data[2] = 0xF1;
  canMsg11.data[3] = 0x90;
  canMsg11.data[4] = 0x00;
  canMsg11.data[5] = 0x00;
  canMsg11.data[6] = 0x00;
  canMsg11.data[7] = 0x00;


  canMsg12.can_id  = ECU_id; //Check session 03
  canMsg12.can_dlc = 3;
  canMsg12.data[0] = 0x02;
  canMsg12.data[1] = 0x19;
  canMsg12.data[2] = 0x00;

  canMsg13.can_id  = ECU_id;
  canMsg13.can_dlc = 3;
  canMsg13.data[0] = 0x02;
  canMsg13.data[1] = 0x14;
  canMsg13.data[2] = 0x00;

  canMsg14.can_id  = ECU_id;
  canMsg14.can_dlc = 3;
  canMsg14.data[0] = 0x02;
  canMsg14.data[1] = 0x27;
  canMsg14.data[2] = 0x01;

  canMsg15.can_id  = ECU_id;
  canMsg15.can_dlc = 7;
  canMsg15.data[0] = 0x06;
  canMsg15.data[1] = 0x27;
  canMsg15.data[2] = 0x02;

  canMsg16.can_id  = ECU_id; //checked
  canMsg16.can_dlc = 3;
  canMsg16.data[0] = 0x02;
  canMsg16.data[1] = 0x11;
  canMsg16.data[2] = 0x01;
}
void menu()
{
    printf("===========MENU============\n");
    printf("Current selected ECU: ");
    if(ECU_id == 0x58)
    {
        printf("Engine ECU.\n");
    }
    else if(ECU_id == 0x60)
    {
        printf("Radar ECU.\n");
    }
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
    printf("17. Select ECU\n");
    printf("=======================\n");
}

void check_for_resp(char can_frame[10], char rx_frame[10])
{
    if(rx_frame[3] == 0x7F)
    {
        printf("ERROR: ");
        if(rx_frame[4] == 0x12)
        {
            printf("Sub function not supported!\n");
        }
        else if(rx_frame[4] == 0x13)
        {
            printf("Invalid format!\n");
        }
        else if(rx_frame[4] == 0x7E)
        {
            printf("Service not supported in active session!\n");
        }
        else if(rx_frame[4] == 0x31)
        {
            printf("Request out of range!\n");
        }
        else if(rx_frame[4] == 0x33)
        {
            printf("Security access denied!\n");
        }
    }
    else if(rx_frame[3] == 0x50)
    {
        printf("Change session success!\n");
    }
    else if(rx_frame[3] == 0x51)
    {
        printf("ECU reset success!\n");
    }
    else if(rx_frame[3] == 0x62)
    {
        printf("Read data success!\n");
    }
    else if(rx_frame[3] == 0x6E)
    {
        printf("Write data success!\n");
    }
    else if(rx_frame[3] == 0x59)
    {
        printf("Read DTC success!\n");
    }
    else if(rx_frame[3] == 0x54)
    {
        printf("Clean diagnostic information success!\n");
    }
    else if(rx_frame[3] == 0x67)
    {
        if(rx_frame[4] == 0x01)
        {
            printf("Request seed success!\n");
        }
        else if(rx_frame[4] == 0x02)
        {
            printf("Send key success!\n");
        }
    }
}

void physical_value()
{
    
}

int main(int argc, char **argv)
{
    char *app_name = argv[0];
    char *dev_name = "/dev/mcp2515_dev";
    int fd = -1;
    char c;
    int select = 0;
    char con;
    int ecu = 0;
    char can_frame[10] = {0};
    char rx_frame[10] = {0};
    init();
    if ((fd = open(dev_name,O_RDWR)) < 0 )
    {
        fprintf(stderr, "%s: unable to open %s: %s\n", app_name, dev_name, strerror(errno));		
        return( 1 );
    }

    do{
        menu();
        printf("Enter your choice (1-->17): ");
        scanf("%d",&select);
        while(select<1 || select > 17)
        {
            printf("Error! Enter your choice (1-->17): ");
            scanf("%d",&select);
        }
        if(select == 1)
        { 
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg1.can_dlc;
            can_frame[2] = canMsg1.data[0];
            can_frame[3] = canMsg1.data[1];
            can_frame[4] = canMsg1.data[2];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 2)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg2.can_dlc;
            can_frame[2] = canMsg2.data[0];
            can_frame[3] = canMsg2.data[1];
            can_frame[4] = canMsg2.data[2];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 3)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg3.can_dlc;
            can_frame[2] = canMsg3.data[0];
            can_frame[3] = canMsg3.data[1];
            can_frame[4] = canMsg3.data[2];
            can_frame[5] = canMsg3.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 4 ){
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg4.can_dlc;
            can_frame[2] = canMsg4.data[0];
            can_frame[3] = canMsg4.data[1];
            can_frame[4] = canMsg4.data[2];
            can_frame[5] = canMsg4.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 5){
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg5.can_dlc;
            can_frame[2] = canMsg5.data[0];
            can_frame[3] = canMsg5.data[1];
            can_frame[4] = canMsg5.data[2];
            can_frame[5] = canMsg5.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 6){
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg6.can_dlc;
            can_frame[2] = canMsg6.data[0];
            can_frame[3] = canMsg6.data[1];
            can_frame[4] = canMsg6.data[2];
            can_frame[5] = canMsg6.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 7)
        {
            can_frame[0] = ECU_id; 
            can_frame[1] = canMsg7.can_dlc;
            can_frame[2] = canMsg7.data[0];
            can_frame[3] = canMsg7.data[1];
            can_frame[4] = canMsg7.data[2];
            can_frame[5] = canMsg7.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 8)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg8.can_dlc;
            can_frame[2] = canMsg8.data[0];
            can_frame[3] = canMsg8.data[1];
            can_frame[4] = canMsg8.data[2];
            can_frame[5] = canMsg8.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 9)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg9.can_dlc;
            can_frame[2] = canMsg9.data[0];
            can_frame[3] = canMsg9.data[1];
            can_frame[4] = canMsg9.data[2];
            can_frame[5] = canMsg9.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 10)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg10.can_dlc;
            can_frame[2] = canMsg10.data[0];
            can_frame[3] = canMsg10.data[1];
            can_frame[4] = canMsg10.data[2];
            can_frame[5] = canMsg10.data[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 11)
        {
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg11.can_dlc;
            can_frame[2] = canMsg11.data[0];
            can_frame[3] = canMsg11.data[1];
            can_frame[4] = canMsg11.data[2];
            can_frame[5] = canMsg11.data[3];
            can_frame[6] = canMsg11.data[4];
            can_frame[7] = canMsg11.data[5];
            can_frame[8] = canMsg11.data[6];
            can_frame[9] = canMsg11.data[7];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 12)
        {
            uint8_t sub_func = 0;
            printf("Choose sub function (00 -> 07): ");
            scanf("%x", &sub_func);
            can_frame[0] = ECU_id;
            can_frame[1] = canMsg12.can_dlc;
            can_frame[2] = canMsg12.data[0];
            can_frame[3] = sub_func;

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 13)
        {
            can_frame[0] = ECU_id; 
            can_frame[1] = canMsg13.can_dlc;
            can_frame[2] = canMsg13.data[0];
            can_frame[3] = canMsg13.data[1];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 14)
        {
            can_frame[0] = ECU_id; 
            can_frame[1] = canMsg14.can_dlc;
            can_frame[2] = canMsg14.data[0];
            can_frame[3] = canMsg14.data[1];
            can_frame[4] = canMsg14.data[2];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
            
            key[0] = rx_frame[5];
            key[1] = rx_frame[6];
            key[2] = rx_frame[7];
            key[3] = rx_frame[8];
            key[0] = key[0] ^ 0XFF;
            key[1] = key[1] ^ 0XFF;
            key[2] = key[2] ^ 0XFF;
            key[3] = key[3] ^ 0XFF;

        }
        else if(select == 15)
        {
            can_frame[0] = ECU_id; 
            can_frame[1] = canMsg15.can_dlc;
            can_frame[2] = canMsg15.data[0];
            can_frame[3] = canMsg15.data[1];
            can_frame[4] = canMsg15.data[2];
            can_frame[5] = key[0];
            can_frame[6] = key[1];
            can_frame[7] = key[2];
            can_frame[8] = key[3];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }   
        else if(select == 16)
        {
            can_frame[0] = ECU_id; 
            can_frame[1] = canMsg16.can_dlc;
            can_frame[2] = canMsg16.data[0];
            can_frame[3] = canMsg16.data[1];
            can_frame[4] = canMsg16.data[2];

            write(fd, can_frame, 10);
            sleep(2);
            read(fd, rx_frame, 10);
        }
        else if(select == 17)
        {
            printf("\t1. Engine.\n");
            printf("\t2. Radar.\n");
            printf("Enter your choice (1 or 2): ");
            scanf("%c", &ecu);
            while(ecu > 2 || ecu < 1)
            {
                printf("Error! Enter your choice again (1 or 2): ");
                scanf("%c", &ecu);
            }
            if(ecu == 1)
            {
                ECU_id = 0x58;
            }
            else if(ecu == 2)
            {
                ECU_id = 0x60;
            }
        }
        printf("CAN Transmission: ");
        for(int i = 0;i<sizeof(can_frame);i++)
        {
            printf("%02X ",(unsigned char)can_frame[i]);
        }
        printf("\n");
        printf("CAN Response: ");
        for(int i = 0;i<sizeof(can_frame);i++)
        {
            printf("%02X ",(unsigned char)rx_frame[i]);
        }
        printf("\n");
        check_for_resp(can_frame, rx_frame);
        for(int k = 0; k < 10; k++)
        {
            can_frame[k] = 0;
            rx_frame[k] = 0;
        }
        printf("\nDo you want to continue? Y or N: ");
        scanf(" %c",&con);
    } while (con =='Y'|| con =='y');
    printf("========OUT==========");
    return 0;
}