#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsgRadar;
void setup() {
  // put your setup code here, to run once:
  canMsgRadar.can_id = 0x760;
  //Read Radar
  //ecu voltage
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;//PCI Length
  canMsgRadar.data[1] = 0x22;// Service ID
  canMsgRadar.data[2] = 0xF1;//Sub function
  canMsgRadar.data[3] = 0x00;//Data parameter
  //angel azimuth
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;
  canMsgRadar.data[1] = 0x22;
  canMsgRadar.data[2] = 0xF1;
  canMsgRadar.data[3] = 0x90;
  //objective detection
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;
  canMsgRadar.data[1] = 0x22;
  canMsgRadar.data[2] = 0xF1;
  canMsgRadar.data[3] = 0x91;
  //warning detection
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;
  canMsgRadar.data[1] = 0x22;
  canMsgRadar.data[2] = 0xF1;
  canMsgRadar.data[3] = 0x92;

  
  //angel azimuth write radar
  canMsgRadar.can_dlc = 4;
  canMsgRadar.data[0] = 0x03;
  canMsgRadar.data[1] = 0x2E;
  canMsgRadar.data[2] = 0xF1;
  canMsgRadar.data[3] = 0x90;
}

void loop() {
  // put your main code here, to run repeatedly:

}
