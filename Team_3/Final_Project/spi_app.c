/****************************************************
* This application is developed by KhanhHuy											
* Group 2.														
* Instructor : Hồ Văn Nguyên Phương					
* Contributor : Truong Phu Khanh Huy
*               Nguyen Van Thin
*               Nguyen Duc Minh				
* **************************************************/

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
#define ENGINE 0x58
#define RADAR 0x60
struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[CAN_FRAME_MAX_DATA_LEN];
};
uint8_t key[4]={0};
char can_frame[10]={0};
char rx_frame[10] = {0};

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
void init_Engine()
{
  canMsg1.can_id  = ENGINE; // SUB FUNCTION 01
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;

  canMsg2.can_id  = ENGINE; // SUB FUNCTION 03
  canMsg2.can_dlc = 3;
  canMsg2.data[0] = 0x02;
  canMsg2.data[1] = 0x10;
  canMsg2.data[2] = 0x03;

  canMsg3.can_id  = ENGINE; // VOLTAGE
  canMsg3.can_dlc = 4;
  canMsg3.data[0] = 0x03;
  canMsg3.data[1] = 0x22;
  canMsg3.data[2] = 0xF1;
  canMsg3.data[3] = 0x00;

  canMsg4.can_id  = ENGINE; // TEMP
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = 0x03;
  canMsg4.data[1] = 0x22;
  canMsg4.data[2] = 0xF1;
  canMsg4.data[3] = 0x80;

  canMsg5.can_id  = ENGINE; // ODOMETER
  canMsg5.can_dlc = 4;
  canMsg5.data[0] = 0x03;
  canMsg5.data[1] = 0x22;
  canMsg5.data[2] = 0xF1;
  canMsg5.data[3] = 0x81;

  canMsg6.can_id  = ENGINE; // VELOCITY
  canMsg6.can_dlc = 4;
  canMsg6.data[0] = 0x03;
  canMsg6.data[1] = 0x22;
  canMsg6.data[2] = 0xF1;
  canMsg6.data[3] = 0x82;

  canMsg7.can_id  = ENGINE; // READ DTC
  canMsg7.can_dlc = 3;
  canMsg7.data[0] = 0x02;
  canMsg7.data[1] = 0x19;
  canMsg7.data[2] = 0x00;

  canMsg8.can_id  = ENGINE; // CLEAR DIAGNOSTIC
  canMsg8.can_dlc = 3;
  canMsg8.data[0] = 0x02;
  canMsg8.data[1] = 0x14;
  canMsg8.data[2] = 0x00;

  canMsg9.can_id  = ENGINE; // REQUEST SEED
  canMsg9.can_dlc = 3;
  canMsg9.data[0] = 0x02;
  canMsg9.data[1] = 0x27;
  canMsg9.data[2] = 0x01;

  canMsg10.can_id  = ENGINE; // SEND KEY
  canMsg10.can_dlc = 7;
  canMsg10.data[0] = 0x06;
  canMsg10.data[1] = 0x27;
  canMsg10.data[2] = 0x02;
  canMsg10.data[3] = 0x00;
  canMsg10.data[4] = 0x00;
  canMsg10.data[5] = 0x00;
  canMsg10.data[6] = 0x00;

  canMsg11.can_id  = ENGINE; // RESET
  canMsg11.can_dlc = 3;
  canMsg11.data[0] = 0x02;
  canMsg11.data[1] = 0x11;
  canMsg11.data[2] = 0x01;
}
void init_Radar()
{
  canMsg1.can_id  = RADAR; // SUB FUNCTION 01
  canMsg1.can_dlc = 3;
  canMsg1.data[0] = 0x02;
  canMsg1.data[1] = 0x10;
  canMsg1.data[2] = 0x01;

  canMsg2.can_id  = RADAR; // SUB FUNCTION 03
  canMsg2.can_dlc = 3;
  canMsg2.data[0] = 0x02;
  canMsg2.data[1] = 0x10;
  canMsg2.data[2] = 0x03;

  canMsg3.can_id  = RADAR; // VOLTAGE
  canMsg3.can_dlc = 4;
  canMsg3.data[0] = 0x03;
  canMsg3.data[1] = 0x22;
  canMsg3.data[2] = 0xF1;
  canMsg3.data[3] = 0x00;

  canMsg4.can_id  = RADAR; // ANGEL
  canMsg4.can_dlc = 4;
  canMsg4.data[0] = 0x03;
  canMsg4.data[1] = 0x22;
  canMsg4.data[2] = 0xF1;
  canMsg4.data[3] = 0x90;

  canMsg5.can_id  = RADAR; // OBJECT DETECTION
  canMsg5.can_dlc = 4;
  canMsg5.data[0] = 0x03;
  canMsg5.data[1] = 0x22;
  canMsg5.data[2] = 0xF1;
  canMsg5.data[3] = 0x91;

  canMsg6.can_id  = RADAR; // WARNING DETECTION
  canMsg6.can_dlc = 4;
  canMsg6.data[0] = 0x03;
  canMsg6.data[1] = 0x22;
  canMsg6.data[2] = 0xF1;
  canMsg6.data[3] = 0x92;

  canMsg7.can_id  = RADAR; // WRITE ANGEL
  canMsg7.can_dlc = 8;
  canMsg7.data[0] = 0x07;
  canMsg7.data[1] = 0x2E;
  canMsg7.data[2] = 0xF1;
  canMsg7.data[3] = 0x90;
  canMsg7.data[4] = 0x00;
  canMsg7.data[5] = 0x00;
  canMsg7.data[6] = 0x00;
  canMsg7.data[7] = 0x00;

  canMsg8.can_id  = RADAR; // READ DTC
  canMsg8.can_dlc = 3;
  canMsg8.data[0] = 0x02;
  canMsg8.data[1] = 0x19;
  canMsg8.data[2] = 0x00;

  canMsg9.can_id  = RADAR; // CLEAR DIAGNOSTIC
  canMsg9.can_dlc = 3;
  canMsg9.data[0] = 0x02;
  canMsg9.data[1] = 0x14;
  canMsg9.data[2] = 0x00;

  canMsg10.can_id  = RADAR; // REQUEST SEED
  canMsg10.can_dlc = 3;
  canMsg10.data[0] = 0x02;
  canMsg10.data[1] = 0x27;
  canMsg10.data[2] = 0x01;

  canMsg11.can_id  = RADAR; // SEND KEY
  canMsg11.can_dlc = 7;
  canMsg11.data[0] = 0x06;
  canMsg11.data[1] = 0x27;
  canMsg11.data[2] = 0x02;
  canMsg11.data[3] = 0x00;
  canMsg11.data[4] = 0x00;
  canMsg11.data[5] = 0x00;
  canMsg11.data[6] = 0x00;

  canMsg12.can_id  = RADAR; // ECU RESET
  canMsg12.can_dlc = 3;
  canMsg12.data[0] = 0x02;
  canMsg12.data[1] = 0x11;
  canMsg12.data[2] = 0x01;
}
void display()
{
    printf("CAN Transmission: ");
    for(int i = 0;i<sizeof(can_frame);i++)
    {
        printf("%02X ",(unsigned char)can_frame[i]);
    }
    printf("\n");
    printf("CAN Response: ");
    for(int i = 0;i<sizeof(rx_frame);i++)
    {
        printf("%02X ",(unsigned char)rx_frame[i]);
    }
}
void clear()
{
    for(int k = 0; k < 10; k++)
    {
        can_frame[k] = 0;
        rx_frame[k] = 0;
    }
}
void errorRead()
{
    if(rx_frame[5]==0x7E)
        printf("Service not Supported in Active Session\n");
    else if(rx_frame[5]==0x13)
        printf("Invalid Format\n");
    else if(rx_frame[5]==0x31)
        printf("Request out of range\n");
    else if(rx_frame[5]==0x33)
        printf("Security access denied\n");
    else
        printf("Cannot identify\n");
}
void errorDiagnostic()
{
    if(rx_frame[5]==0x14)
        printf("Service not Supported in Active Session\n");
    else if(rx_frame[5]==0x12)
        printf("Sub function not supported\n");
    else if(rx_frame[5]==0x13)
        printf("Invalid format\n");
    else
        printf("Cannot identify\n");
}
void errorRequest()
{
    if(rx_frame[5]==0x7E)
        printf("Service not Supported in Active Session\n");
    else if(rx_frame[5]==0x13)
        printf("Invalid Format\n");
    else if(rx_frame[5]==0x31)
        printf("Security Access Denied\n");
    else if(rx_frame[5]==0x33)
        printf("Security access denied\n");
    else if(rx_frame[3]==0x12)
        printf("Subfunction not supported\n");
    else
        printf("Cannot identify\n");
}
void errorDTC()
{
    if(rx_frame[5]==0x7E)
        printf("Service not Supported in Active Session\n");
    else if(rx_frame[5]==0x12)
        printf("Sub function not supported\n");
    else if(rx_frame[5]==0x13)
        printf("Invalid format\n");
    else
        printf("Cannot identify\n");
}
void menuEngine()
{
    printf("===========MENU TEAM 3============\n");
    printf("1.  Session control 01\n");
    printf("2.  Session control 03\n");
    printf("3.  Read ECU voltage engine\n");
    printf("4.  Read temperature engine\n");
    printf("5.  Read odometer engine\n");
    printf("6.  Read velocity engine\n");
    printf("7.  Read DTC\n");
    printf("8.  Clear diagnostic\n");
    printf("9.  Request seed\n");
    printf("10. Send key\n");
    printf("11. ECU reset\n");
    printf("=======================\n");
}
void menuRadar()
{
    printf("===========MENU TEAM 3============\n");
    printf("1.  Session control 01\n");
    printf("2.  Session control 03\n");
    printf("3.  Read ECU voltage radar\n");
    printf("4.  Read angel azimuth radar\n");
    printf("5.  Object detection radar\n");
    printf("6.  Warning detection radar\n");
    printf("7.  Write angel azimuth radar\n");
    printf("8.  Read DTC\n");
    printf("9.  Clear diagnostic\n");
    printf("10. Request seed\n");
    printf("11. Send key\n");
    printf("12. ECU reset\n");
    printf("=======================\n");
}
int main(int argc, char **argv)
{
    char *app_name = argv[0];
    char *dev_name = "/dev/mcp2515_dev";
    int fd = -1;
    char c;
    int select = 0;
    int choice = 0;
    int next = 0;
    char con;
    if ((fd = open(dev_name,O_RDWR)) < 0 )
    {
        fprintf(stderr, "%s: unable to open %s: %s\n", app_name, dev_name, strerror(errno));		
        return( 1 );
    }
    do{
        read(fd, rx_frame, 10);
        clear();
        printf("Team 3: Thanh Huy - Quoc Kien - Van Y - Dai Viet.\n");
        printf("Enter(1 or 2) parts to work: 1. Engine  2. Radar: ");
        scanf("%d",&select);
        while(select<1 || select > 2)
        {
            printf("Error! Enter your selection (1-->2): ");
            scanf("%d",&select);
        }
    if(select==1)
    {
        do{
            init_Engine();
            menuEngine();
            printf("Enter your choice (1-->11): ");
            scanf("%d",&choice);
            while(choice<1 || choice > 11)
            {
                printf("Error! Enter your choice (1-->11): ");
                scanf("%d",&choice);
            }
            if(choice == 1)
            { 
                can_frame[0] = canMsg1.can_id;
                can_frame[1] = canMsg1.can_dlc;
                can_frame[2] = canMsg1.data[0];
                can_frame[3] = canMsg1.data[1];
                can_frame[4] = canMsg1.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                if(rx_frame[3]==0x50)
                {
                    printf("\nSuccessfully changed session");
                }
                else if(rx_frame[3] == 0x7F)
                {
                    printf("Error! ");
                    if(rx_frame[5] == 0x12)
                        printf("\nSub Function Not Supported");
                    else if(rx_frame[5] == 0x13)
                        printf("\nInvalid Format");
                    else
                        printf("\nCannot Identify");
                }
            }
            else if(choice == 2)
            {
                can_frame[0] = canMsg2.can_id;
                can_frame[1] = canMsg2.can_dlc;
                can_frame[2] = canMsg2.data[0];
                can_frame[3] = canMsg2.data[1];
                can_frame[4] = canMsg2.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                if(rx_frame[3]==0x50)
                {
                    printf("\nSuccessfully changed session");
                }
                else if(rx_frame[3] == 0x7F)
                {
                    printf("Error! ");
                    if(rx_frame[5] == 0x12)
                        printf("\nSub Function Not Supported");
                    else if(rx_frame[5] == 0x13)
                        printf("\nInvalid Format");
                    else
                        printf("\nCannot Identify");
                }
            }
            else if(choice == 3)
            {
                can_frame[0] = canMsg3.can_id;
                can_frame[1] = canMsg3.can_dlc;
                can_frame[2] = canMsg3.data[0];
                can_frame[3] = canMsg3.data[1];
                can_frame[4] = canMsg3.data[2];
                can_frame[5] = canMsg3.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The voltage of engine: %dV",rx_frame[6]);
                }
            }
            else if(choice == 4 ){
                can_frame[0] = canMsg4.can_id;
                can_frame[1] = canMsg4.can_dlc;
                can_frame[2] = canMsg4.data[0];
                can_frame[3] = canMsg4.data[1];
                can_frame[4] = canMsg4.data[2];
                can_frame[5] = canMsg4.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The temperature of engine: %doC",rx_frame[6]);
                }
            }
            else if(choice == 5){
                can_frame[0] = canMsg5.can_id;
                can_frame[1] = canMsg5.can_dlc;
                can_frame[2] = canMsg5.data[0];
                can_frame[3] = canMsg5.data[1];
                can_frame[4] = canMsg5.data[2];
                can_frame[5] = canMsg5.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The odometer of engine: ");
                    printf("%d%dKm", rx_frame[6], rx_frame[7]);
                }
            }
            else if(choice == 6){
                can_frame[0] = canMsg6.can_id;
                can_frame[1] = canMsg6.can_dlc;
                can_frame[2] = canMsg6.data[0];
                can_frame[3] = canMsg6.data[1];
                can_frame[4] = canMsg6.data[2];
                can_frame[5] = canMsg6.data[3];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The velocity of engine: %dKm/h",rx_frame[6]);
                    
                }
            }
            else if(choice == 7)
            {
                uint8_t subfunction = 0;
                printf("Enter the subfunction from 00-->07: ");
                scanf("%d",&subfunction);
                while(subfunction<0x00 || subfunction > 0x07)
                {
                    printf("Error! Enter subfunction from 0-->7: ");
                    scanf("%d",&subfunction);
                }
                can_frame[0] = canMsg7.can_id; 
                can_frame[1] = canMsg7.can_dlc;
                can_frame[2] = canMsg7.data[0];
                can_frame[3] = canMsg7.data[1];
                can_frame[4] = subfunction;

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDTC();
                }
                else{
                    printf("The data recorded is: %d",rx_frame[5]);
                }
            }
            else if(choice == 8)
            {
                can_frame[0] = canMsg8.can_id;
                can_frame[1] = canMsg8.can_dlc;
                can_frame[2] = canMsg8.data[0];
                can_frame[3] = canMsg8.data[1];
                can_frame[4] = canMsg8.data[2];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDiagnostic();
                }
                else   
                    printf("Successfully cleared diagonstic!");
            }
            else if(choice == 9)
            {
                can_frame[0] = canMsg9.can_id;
                can_frame[1] = canMsg9.can_dlc;
                can_frame[2] = canMsg9.data[0];
                can_frame[3] = canMsg9.data[1];
                can_frame[4] = canMsg9.data[2];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRequest();
                }
                else
                {
                    printf("Key: %02X %02X %02X %02X",(unsigned char)rx_frame[5],(unsigned char)rx_frame[6],(unsigned char)rx_frame[7],(unsigned char)rx_frame[8]);
                }
                for(int i =0;i<5;i++)
                {
                    key[i] = rx_frame[5+i];
                }
                key[0] = key[0] ^ 0xFF;
                key[1] = key[1] ^ 0xFF;
                key[2] = key[2] ^ 0xFF;
                key[3] = key[3] ^ 0xFF;
            }
            else if(choice == 10)
            {
                can_frame[0] = canMsg10.can_id;
                can_frame[1] = canMsg10.can_dlc;
                can_frame[2] = canMsg10.data[0];
                can_frame[3] = canMsg10.data[1];
                can_frame[4] = canMsg10.data[2];
                can_frame[5] = key[0];
                can_frame[6] = key[1];
                can_frame[7] = key[2];
                can_frame[8] = key[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRequest();
                }
                else
                {
                    printf("Successfully accessed");
                }
                for(int i =0;i<5;i++)
                {
                    key[i] = 0x00;
                }
            }
            else if(choice == 11)
            {
                can_frame[0] = canMsg11.can_id;
                can_frame[1] = canMsg11.can_dlc;
                can_frame[2] = canMsg11.data[0];
                can_frame[3] = canMsg11.data[1];
                can_frame[4] = canMsg11.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDiagnostic();
                }
                else  
                    printf("Successfully resetted ECU");
            }
            clear();
            printf("\nDo you want to continue? Y or N: ");
            scanf(" %c",&con);
            printf("\n");
        }while(con == 'Y' || con == 'y');
    }
    else if(select == 2)
    {
        do{
            init_Radar();
            menuRadar();
            printf("Enter your choice (1-->12): ");
            scanf("%d",&choice);
            while(choice< 1 || choice > 12)
            {
                printf("Error! Enter your choice (1-->12): ");
                scanf("%d",&choice);
            }
            if(choice == 1)
            { 
                can_frame[0] = canMsg1.can_id;
                can_frame[1] = canMsg1.can_dlc;
                can_frame[2] = canMsg1.data[0];
                can_frame[3] = canMsg1.data[1];
                can_frame[4] = canMsg1.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x50)
                {
                    printf("Successfully changed session");
                }
                else if(rx_frame[3] == 0x7F)
                {
                    printf("Error! ");
                    if(rx_frame[5] == 0x12)
                        printf("Sub Function Not Supported");
                    else if(rx_frame[5] == 0x13)
                        printf("Invalid Format");
                    else
                        printf("Cannot Identify");
                }
            }
            else if(choice == 2)
            {
                can_frame[0] = canMsg2.can_id;
                can_frame[1] = canMsg2.can_dlc;
                can_frame[2] = canMsg2.data[0];
                can_frame[3] = canMsg2.data[1];
                can_frame[4] = canMsg2.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x50)
                {
                    printf("Successfully changed session");
                }
                else if(rx_frame[3] == 0x7F)
                {
                    printf("Error! ");
                    if(rx_frame[5] == 0x12)
                        printf("Sub Function Not Supported");
                    else if(rx_frame[5] == 0x13)
                        printf("Invalid Format");
                    else
                        printf("Cannot Identify");
                }
            }
            else if(choice == 3)
            {
                can_frame[0] = canMsg3.can_id;
                can_frame[1] = canMsg3.can_dlc;
                can_frame[2] = canMsg3.data[0];
                can_frame[3] = canMsg3.data[1];
                can_frame[4] = canMsg3.data[2];
                can_frame[5] = canMsg3.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The voltage of radar: %dV",rx_frame[6]);
                }
            }
            else if(choice == 4 ){
                can_frame[0] = canMsg4.can_id;
                can_frame[1] = canMsg4.can_dlc;
                can_frame[2] = canMsg4.data[0];
                can_frame[3] = canMsg4.data[1];
                can_frame[4] = canMsg4.data[2];
                can_frame[5] = canMsg4.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The angel azimuth correction of radar: ");
                    char angle[2] = {0};
                    angle[0] = rx_frame[6];
                    angle[1] = rx_frame[7];
                    int angle_raw = (int)angle;
                    angle_raw = (angle_raw/100) - 180;
                    printf("%d degree",angle_raw);
                }
            }
            else if(choice == 5){
                can_frame[0] = canMsg5.can_id;
                can_frame[1] = canMsg5.can_dlc;
                can_frame[2] = canMsg5.data[0];
                can_frame[3] = canMsg5.data[1];
                can_frame[4] = canMsg5.data[2];
                can_frame[5] = canMsg5.data[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The object detection of radar: ");
                    if(rx_frame[6]==0x01)
                        printf("Yes");
                    if(rx_frame[6]==0x00)
                        printf("No");
                }
            }
            else if(choice == 6){
                can_frame[0] = canMsg6.can_id;
                can_frame[1] = canMsg6.can_dlc;
                can_frame[2] = canMsg6.data[0];
                can_frame[3] = canMsg6.data[1];
                can_frame[4] = canMsg6.data[2];
                can_frame[5] = canMsg6.data[3];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRead();
                }
                else{
                    printf("The warning detection of engine: ");
                    if(rx_frame[6]==0x01)
                        printf("Yes");
                    if(rx_frame[6]==0x00)
                        printf("No");
                }
            }
            else if(choice == 7)
            {
                float angel  = 0;
                printf("Enter the value of angel for radar (-180-->180): ");
                scanf("%.02f",&angel);
                while(angel<-180 || angel>180)
                {
                    printf("Error! Enter the value of angel for radar (-180-->180): ");
                    scanf("%.02f",&angel);
                }
                int raw_value = (angel+180)*100;
                printf("\n%.02f\n", angel);
                printf("\n%d\n", raw_value);
                char angle_msg1 = raw_value/10000;
                char angle_msg2 = (raw_value/100) - ((raw_value/10000)*100);
                char angle_msg3 = raw_value - ((raw_value/10000)*10000) - ((raw_value/100) - ((raw_value/10000)*100))*100;
                can_frame[0] = canMsg7.can_id; 
                can_frame[1] = canMsg7.can_dlc;
                can_frame[2] = canMsg7.data[0];
                can_frame[3] = canMsg7.data[1];
                can_frame[4] = canMsg7.data[2];
                can_frame[5] = canMsg7.data[3];
                can_frame[6] = angle_msg1;
                can_frame[7] = angle_msg2;
                can_frame[8] = angle_msg3;
                can_frame[9] = 0x00;
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRequest();
                }
                else{
                    printf("Successfully wrote the angle of radar");
                }
            }
            else if(choice == 8)
            {
                uint8_t subfunction = 0;
                printf("Enter the subfunction from 00-->07: ");
                scanf("%d",&subfunction);
                while(subfunction<0 || subfunction > 7)
                {
                    printf("Error! Enter subfunction from 0-->7: ");
                    scanf("%d",&subfunction);
                }
                can_frame[0] = canMsg8.can_id; 
                can_frame[1] = canMsg8.can_dlc;
                can_frame[2] = canMsg8.data[0];
                can_frame[3] = canMsg8.data[1];
                can_frame[4] = subfunction;

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDTC();
                }
                else{
                    printf("The data recorded is: %d",rx_frame[5]);
                }
            }
            else if(choice == 9)
            {
                can_frame[0] = canMsg9.can_id;
                can_frame[1] = canMsg9.can_dlc;
                can_frame[2] = canMsg9.data[0];
                can_frame[3] = canMsg9.data[1];
                can_frame[4] = canMsg9.data[2];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDiagnostic();
                }
                else   
                    printf("Successfully cleared diagonstic");
            }
            else if(choice == 10)
            {
                can_frame[0] = canMsg10.can_id;
                can_frame[1] = canMsg10.can_dlc;
                can_frame[2] = canMsg10.data[0];
                can_frame[3] = canMsg10.data[1];
                can_frame[4] = canMsg10.data[2];

                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRequest();
                }
                else
                {
                    printf("Key: %02X %02X %02X %02X",(unsigned char)rx_frame[5],(unsigned char)rx_frame[6],(unsigned char)rx_frame[7],(unsigned char)rx_frame[8]);
                }
                for(int i =0;i<5;i++)
                {
                    key[i] = rx_frame[5+i];
                }
                key[0] = key[0] ^ 0xFF;
                key[1] = key[1] ^ 0xFF;
                key[2] = key[2] ^ 0xFF;
                key[3] = key[3] ^ 0xFF;
            }
            else if(choice == 11)
            {
               can_frame[0] = canMsg11.can_id;
                can_frame[1] = canMsg11.can_dlc;
                can_frame[2] = canMsg11.data[0];
                can_frame[3] = canMsg11.data[1];
                can_frame[4] = canMsg11.data[2];
                can_frame[5] = key[0];
                can_frame[6] = key[1];
                can_frame[7] = key[2];
                can_frame[8] = key[3];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorRequest();
                }
                else
                {
                    printf("Successfully accessed");
                }
                for(int i =0;i<5;i++)
                {
                    key[i] = 0x00;
                }
            }
            else if(choice==12)
            {
                can_frame[0] = canMsg12.can_id;
                can_frame[1] = canMsg12.can_dlc;
                can_frame[2] = canMsg12.data[0];
                can_frame[3] = canMsg12.data[1];
                can_frame[4] = canMsg12.data[2];
                write(fd, can_frame, 10);
                sleep(2);
                read(fd, rx_frame, 10);
                display();
                printf("\n");
                if(rx_frame[3]==0x7F)
                {
                    printf("Error! ");
                    errorDiagnostic();
                }
                else  
                    printf("Successfully resetted ECU");
            }
            clear();
            printf("\nDo you want to continue? Y or N: ");
            scanf(" %c",&con);
            printf("\n");
        }while(con == 'Y' || con == 'y');
    }
    printf("Do you want to change parts(Enter 1 or 2)? 1. Yes 2. No? ");
    scanf("%d",&next);
    printf("\n");
    } while(next == 1);
    printf("===============OUT============");
    return 0;
}