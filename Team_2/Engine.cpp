#include <SPI.h>
#include <mcp2515.h>

struct can_frame CanMs1;
struct can_frame CanMs2;
struct can_frame CanMs3;
struct can_frame CanMs4;

MCP2515 = mcp2515(10);

//voltage
CanMsg1.Can_id = 0x750;
CanMsg1.Can_dlc = 3 ;
CanMsg1.data[3] ={22 , F1 , 79};

//temperature	
CanMsg2.Can_id = 0x750;
CanMsg2.Can_dlc = 3 ;
CanMsg2.data[2] ={02 , F1 , 80};

//adometer
CanMsg3.Can_id = 0x750;
CanMsg3.Can_dlc = 3;
CanMsg3.data[2] ={02 , F1 , 81};

//Velocity
CanMsg4.Can_id = 0x750;
CanMsg4.Can_dlc = 3;
CanMsg4.data[2] ={02 , F1 , 82};





