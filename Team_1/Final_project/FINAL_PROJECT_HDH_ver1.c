/******************************************************************
*This file is written by Nguyen Cao Minh, 18ES. 		  *
*It is translated directly from Arduino MCP2515 driver to run on  *
*Raspberry. 							  *
******************************************************************/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/spi/spi.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Cao Minh");
MODULE_DESCRIPTION("SPI connection test");

#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev;

static int __init ModuleInit(void){
    struct spi_master *master;
    u8 id;

    struct spi_board_info spi_device_info = {
        .modalias = "mcp2515";
        .max_speed_hz = 100000,
        .bus_num = MY_BUS_NUM,
        .chip_select = 0,
        .mode = 3,
    };
    
    master = spi_busnum_to_master(MY_BUS_NUM);

    if(!master){
        printk("There is no spi bus with Nr. %d\n", MY_BUS_NUM);
		return -1;
    }

    mcp2515_dev = spi_new_device(master, &spi_device_info);
    if(!mcp2515_dev) {
		printk("Could not create device!\n");
		return -1;
	}

    mcp2515_dev->bits_per_word = 8;

    /* Setup the bus for device's parameters */
	if(spi_setup(mcp2515_dev) != 0){
		printk("Could not change bus setup!\n");
		spi_unregister_device(mcp2515_dev);
		return -1;
	}


}

//SPI INSTRUCTIONS SET
enum INSTRUCTION : uint8_t {
            INSTRUCTION_WRITE       = 0x02,
            INSTRUCTION_READ        = 0x03,
            INSTRUCTION_BITMOD      = 0x05,
            INSTRUCTION_LOAD_TX0    = 0x40,
            INSTRUCTION_LOAD_TX1    = 0x42,
            INSTRUCTION_LOAD_TX2    = 0x44,
            INSTRUCTION_RTS_TX0     = 0x81,
            INSTRUCTION_RTS_TX1     = 0x82,
            INSTRUCTION_RTS_TX2     = 0x84,
            INSTRUCTION_RTS_ALL     = 0x87,
            INSTRUCTION_READ_RX0    = 0x90,
            INSTRUCTION_READ_RX1    = 0x94,
            INSTRUCTION_READ_STATUS = 0xA0,
            INSTRUCTION_RX_STATUS   = 0xB0,
            INSTRUCTION_RESET       = 0xC0
        };

//MCP2515 REGISTERS MAP
enum REGISTER : uint8_t {
            MCP_RXF0SIDH = 0x00,
            MCP_RXF0SIDL = 0x01,
            MCP_RXF0EID8 = 0x02,
            MCP_RXF0EID0 = 0x03,
            MCP_RXF1SIDH = 0x04,
            MCP_RXF1SIDL = 0x05,
            MCP_RXF1EID8 = 0x06,
            MCP_RXF1EID0 = 0x07,
            MCP_RXF2SIDH = 0x08,
            MCP_RXF2SIDL = 0x09,
            MCP_RXF2EID8 = 0x0A,
            MCP_RXF2EID0 = 0x0B,
            MCP_CANSTAT  = 0x0E,
            MCP_CANCTRL  = 0x0F,
            MCP_RXF3SIDH = 0x10,
            MCP_RXF3SIDL = 0x11,
            MCP_RXF3EID8 = 0x12,
            MCP_RXF3EID0 = 0x13,
            MCP_RXF4SIDH = 0x14,
            MCP_RXF4SIDL = 0x15,
            MCP_RXF4EID8 = 0x16,
            MCP_RXF4EID0 = 0x17,
            MCP_RXF5SIDH = 0x18,
            MCP_RXF5SIDL = 0x19,
            MCP_RXF5EID8 = 0x1A,
            MCP_RXF5EID0 = 0x1B,
            MCP_TEC      = 0x1C,
            MCP_REC      = 0x1D,
            MCP_RXM0SIDH = 0x20,
            MCP_RXM0SIDL = 0x21,
            MCP_RXM0EID8 = 0x22,
            MCP_RXM0EID0 = 0x23,
            MCP_RXM1SIDH = 0x24,
            MCP_RXM1SIDL = 0x25,
            MCP_RXM1EID8 = 0x26,
            MCP_RXM1EID0 = 0x27,
            MCP_CNF3     = 0x28,
            MCP_CNF2     = 0x29,
            MCP_CNF1     = 0x2A,
            MCP_CANINTE  = 0x2B,
            MCP_CANINTF  = 0x2C,
            MCP_EFLG     = 0x2D,
            MCP_TXB0CTRL = 0x30,
            MCP_TXB0SIDH = 0x31,
            MCP_TXB0SIDL = 0x32,
            MCP_TXB0EID8 = 0x33,
            MCP_TXB0EID0 = 0x34,
            MCP_TXB0DLC  = 0x35,
            MCP_TXB0DATA = 0x36,
            MCP_TXB1CTRL = 0x40,
            MCP_TXB1SIDH = 0x41,
            MCP_TXB1SIDL = 0x42,
            MCP_TXB1EID8 = 0x43,
            MCP_TXB1EID0 = 0x44,
            MCP_TXB1DLC  = 0x45,
            MCP_TXB1DATA = 0x46,
            MCP_TXB2CTRL = 0x50,
            MCP_TXB2SIDH = 0x51,
            MCP_TXB2SIDL = 0x52,
            MCP_TXB2EID8 = 0x53,
            MCP_TXB2EID0 = 0x54,
            MCP_TXB2DLC  = 0x55,
            MCP_TXB2DATA = 0x56,
            MCP_RXB0CTRL = 0x60,
            MCP_RXB0SIDH = 0x61,
            MCP_RXB0SIDL = 0x62,
            MCP_RXB0EID8 = 0x63,
            MCP_RXB0EID0 = 0x64,
            MCP_RXB0DLC  = 0x65,
            MCP_RXB0DATA = 0x66,
            MCP_RXB1CTRL = 0x70,
            MCP_RXB1SIDH = 0x71,
            MCP_RXB1SIDL = 0x72,
            MCP_RXB1EID8 = 0x73,
            MCP_RXB1EID0 = 0x74,
            MCP_RXB1DLC  = 0x75,
            MCP_RXB1DATA = 0x76
};

enum  STAT : uint8_t {
    STAT_RX0IF = (1<<0),
    STAT_RX1IF = (1<<1)
};

static const struct RXBn_REGS {
    REGISTER CTRL;
    REGISTER SIDH;
    REGISTER DATA;
    CANINTF  CANINTF_RXnIF;
} RXB[N_RXBUFFERS];

const struct RXBn_REGS RXB[2] = {
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
}

//This struct handles CAN data frame.
struct can_frame {
    u32 can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    u8 can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    u8 data[8];
};

static const uint8_t MCP_SIDH = 0;
static const uint8_t MCP_SIDL = 1;
static const uint8_t MCP_EID8 = 2;
static const uint8_t MCP_EID0 = 3;
static const uint8_t MCP_DLC  = 4;
static const uint8_t MCP_DATA = 5;

static const uint8_t TXB_EXIDE_MASK = 0x08;
static const uint8_t DLC_MASK       = 0x0F;
static const uint8_t RTR_MASK       = 0x40;

//This function is used to read status of RXBn buffer.
u8 getStatus(){
    u8 ret_val;
    u8 tx_val;
    tx_val = INSTRUCTION_WRITE;

    spi_write(mcp2515_dev, tx_val, 1);

    spi_read(mcp2515_dev, &ret_val, 1);
    return ret_val;
}

//This function is used to modify several bits on register without changing old data
void modifyRegister(u8 reg, u8 mask, const u8 data)
{
    u8 val;
    u8 tx_val[4];

    tx_val[0] = INSTRUCTION_BITMODE;
    tx_val[1] = reg;
    tx_val[2] = mask;
    tx_val[3] = data;
    spi_write(mcp2515_dev, tx_val, 2);
}
//

//This function used to read 1 register from MCP2515
u8 readRegister(u8 reg){
    
    u8 val;
    u8 tx_val[2];

    tx_val[0] = INSTRUCTION_WRITE;
    tx_val[1] = reg;
    spi_write(mcp2515_dev, tx_val, 2);

    spi_read(mcp2515_dev, &val, 1);

    return val;
}
//

//This function is used to read multiple registers from MCP2515
void readRegisters(u8 reg, u8 val[], u8 len){
    u8 tx_val[2];
    tx_val[0] = INSTRUCTION_WRITE;
    tx_val[1] = reg;
    spi_write(mcp2515_dev, tx_val, 2);

    spi_read(mcp2515_dev, val, len);
}


//This function is called indirectly to read message out of RXBn buffers.
int readMessagefromHardwware(const RXBn rxbn, struct can_frame *frame)
{
    const struct RXBn_REGS *rxb = &RXB[rxbn];


    // Five bytes are used to store Standard and Extend Identifiers
    // Reading 5 bytes of Identifier to tbufdata
    u8 tbufdata[5];
    readRegisters(rxb->SIDH, tbufdata, 5); // <- This function is platform dependent
    //

    //Bit manipulation to obtain ID field in the message
    //Inside tbufdata[5] array there are registers:
    //      + [0] SIDH 
    //      + [1] SIDL
    //      + [2] EIDH
    //      + [3] EIDL
    //      + [4] DLC
    //ID has 11 bits in length
    u32 id = (tbufdata[MCP_SIDH]<<3) + (tbufdata[MCP_SIDL]>>5);

    //If extended standard id is used then modify id
    //In final project, we dont use extended id so this code can be removed with no effect. 
    if ( (tbufdata[MCP_SIDL] & TXB_EXIDE_MASK) ==  TXB_EXIDE_MASK ) {
        id = (id<<2) + (tbufdata[MCP_SIDL] & 0x03);
        id = (id<<8) + tbufdata[MCP_EID8];
        id = (id<<8) + tbufdata[MCP_EID0];
        id |= CAN_EFF_FLAG;
    }
    //

    //Data length (DLC) is obtained by masking DLC_MASK with tbufdata[4]
    //If data length is more then 8 then return error.
    //CAN_MAX_DLEN(maximum data length) is 8
    //DLC has 4 bit in length
    u8 dlc = (tbufdata[MCP_DLC] & DLC_MASK);
    if (dlc > 8) {
        return -1;
    }

    //Read value of CTRL register
    //CTRL register has 8 bits, including RTR bit, IDE bit, Reserved bit, Data filtering bits. 
    u8 ctrl = readRegister(rxb->CTRL); // <- This function is platform dependent.
    if (ctrl & RXBnCTRL_RTR) // <- If RTR bit of CTRL register is 1 then 
    {
        id |= CAN_RTR_FLAG; // <- Switch the corresponding RTR bit in the id to 1
    }

    //Assigning value to frame struct
    frame->can_id = id;
    frame->can_dlc = dlc;

    //Reading data and assigning to frame data
    readRegisters(rxb->DATA, frame->data, dlc); // <- This function is platform dependent

    //Clearing CAN interrupt flag for new data to reside.
    modifyRegister(MCP_CANINTF, rxb->CANINTF_RXnIF, 0); // <- This function is platform dependent

    return 1;
}

//This function will be called directly to get data frame
int readMessage(struct can_frame *frame)
{
    int rc;
    u8 stat = getStatus();

    //If RX0IF is 1,there is data inside RXB0 buffer.Then read RBX0
    //
    //If RX1IF is 1,there is data inside RXB1 buffer.Then read RBX1
    //
    //Else, buffer is empty, quit the process.
    if ( stat & STAT_RX0IF ) {
        //Read CAN message from RXB0
        rc = readMessagefromHardware(0, frame);
    } 
    else if ( stat & STAT_RX1IF) {
        //Read CAN message from RXB1
        rc = readMessagefromHardware(1, frame);
    } else
    {
        //Quit function
        rc = -1;
    }
    return rc;
}