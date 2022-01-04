#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsgRadar;
struct can_frame canMsgRadar1;  //ecu voltage
struct can_frame canMsgRadar2;  //angel azimuth
struct can_frame canMsgRadar3;  //obj detection 
struct can_frame canMsgRadar4;  //warning detection
 
void setup() {
  canMsgRadar.can_id = 0x760;
  canMsgRadar.can_dlc = 4;
  //ecu voltage
  canMsgRadar1.data[0] = 0x03;//PCI Length
  canMsgRadar1.data[1] = 0x22;// Service ID
  canMsgRadar1.data[2] = 0xF1;//Sub function
  canMsgRadar1.data[3] = 0x00;//Data parameter
  //angel azimuth
  canMsgRadar2.data[0] = 0x03;
  canMsgRadar2.data[1] = 0x22;
  canMsgRadar2.data[2] = 0xF1;
  canMsgRadar2.data[3] = 0x90;
  //objective detection
  canMsgRadar3.data[0] = 0x03;
  canMsgRadar3.data[1] = 0x22;
  canMsgRadar3.data[2] = 0xF1;
  canMsgRadar3.data[3] = 0x91;
  //warning detection
  canMsgRadar4.data[0] = 0x03;
  canMsgRadar4.data[1] = 0x22;
  canMsgRadar4.data[2] = 0xF1;
  canMsgRadar4.data[3] = 0x92;

  
  /*angel azimuth write radar
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;
  canMsgRadar.data[1] = 0x2E;
  canMsgRadar.data[2] = 0xF1;
  canMsgRadar.data[3] = 0x90;*/
}

void loop() {
  // put your main code here, to run repeatedly:

}
