/******************************************************************
*This file is written by Nguyen Cao Minh, 18ES. 		  *
*It is translated directly from Arduino MCP2515 driver to run on  *
*Raspberry. 							  *
******************************************************************/
#include <linux/types.h>
#include <linux/spi/spi.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
 
#include <linux/kdev_t.h>
#include <linux/fs.h>   
#include <linux/cdev.h> 
#include <asm/uaccess.h>

#include <linux/gpio.h>

#include <linux/interrupt.h>

#include <linux/kobject.h> 
#include <linux/sysfs.h>

#include <linux/time.h>
#include <linux/ktime.h>
#include <asm/delay.h> 
#include <linux/delay.h>
/*
 *  Speed 8M
 */
#define MCP_8MHz_1000kBPS_CFG1 (0x00)
#define MCP_8MHz_1000kBPS_CFG2 (0x80)
#define MCP_8MHz_1000kBPS_CFG3 (0x80)

#define MCP_8MHz_500kBPS_CFG1 (0x00)
#define MCP_8MHz_500kBPS_CFG2 (0x90)
#define MCP_8MHz_500kBPS_CFG3 (0x82)

#define MCP_8MHz_250kBPS_CFG1 (0x00)
#define MCP_8MHz_250kBPS_CFG2 (0xB1)
#define MCP_8MHz_250kBPS_CFG3 (0x85)

#define MCP_8MHz_200kBPS_CFG1 (0x00)
#define MCP_8MHz_200kBPS_CFG2 (0xB4)
#define MCP_8MHz_200kBPS_CFG3 (0x86)

#define MCP_8MHz_125kBPS_CFG1 (0x01)
#define MCP_8MHz_125kBPS_CFG2 (0xB1)
#define MCP_8MHz_125kBPS_CFG3 (0x85)

#define MCP_8MHz_100kBPS_CFG1 (0x01)
#define MCP_8MHz_100kBPS_CFG2 (0xB4)
#define MCP_8MHz_100kBPS_CFG3 (0x86)

#define MCP_8MHz_80kBPS_CFG1 (0x01)
#define MCP_8MHz_80kBPS_CFG2 (0xBF)
#define MCP_8MHz_80kBPS_CFG3 (0x87)

#define MCP_8MHz_50kBPS_CFG1 (0x03)
#define MCP_8MHz_50kBPS_CFG2 (0xB4)
#define MCP_8MHz_50kBPS_CFG3 (0x86)

#define MCP_8MHz_40kBPS_CFG1 (0x03)
#define MCP_8MHz_40kBPS_CFG2 (0xBF)
#define MCP_8MHz_40kBPS_CFG3 (0x87)

#define MCP_8MHz_33k3BPS_CFG1 (0x47)
#define MCP_8MHz_33k3BPS_CFG2 (0xE2)
#define MCP_8MHz_33k3BPS_CFG3 (0x85)

#define MCP_8MHz_31k25BPS_CFG1 (0x07)
#define MCP_8MHz_31k25BPS_CFG2 (0xA4)
#define MCP_8MHz_31k25BPS_CFG3 (0x84)

#define MCP_8MHz_20kBPS_CFG1 (0x07)
#define MCP_8MHz_20kBPS_CFG2 (0xBF)
#define MCP_8MHz_20kBPS_CFG3 (0x87)

#define MCP_8MHz_10kBPS_CFG1 (0x0F)
#define MCP_8MHz_10kBPS_CFG2 (0xBF)
#define MCP_8MHz_10kBPS_CFG3 (0x87)

#define MCP_8MHz_5kBPS_CFG1 (0x1F)
#define MCP_8MHz_5kBPS_CFG2 (0xBF)
#define MCP_8MHz_5kBPS_CFG3 (0x87)

/*
 *  speed 16M
 */
#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1 (0x00)
#define MCP_16MHz_500kBPS_CFG2 (0xF0)
#define MCP_16MHz_500kBPS_CFG3 (0x86)

#define MCP_16MHz_250kBPS_CFG1 (0x41)
#define MCP_16MHz_250kBPS_CFG2 (0xF1)
#define MCP_16MHz_250kBPS_CFG3 (0x85)

#define MCP_16MHz_200kBPS_CFG1 (0x01)
#define MCP_16MHz_200kBPS_CFG2 (0xFA)
#define MCP_16MHz_200kBPS_CFG3 (0x87)

#define MCP_16MHz_125kBPS_CFG1 (0x03)
#define MCP_16MHz_125kBPS_CFG2 (0xF0)
#define MCP_16MHz_125kBPS_CFG3 (0x86)

#define MCP_16MHz_100kBPS_CFG1 (0x03)
#define MCP_16MHz_100kBPS_CFG2 (0xFA)
#define MCP_16MHz_100kBPS_CFG3 (0x87)

#define MCP_16MHz_80kBPS_CFG1 (0x03)
#define MCP_16MHz_80kBPS_CFG2 (0xFF)
#define MCP_16MHz_80kBPS_CFG3 (0x87)

#define MCP_16MHz_83k3BPS_CFG1 (0x03)
#define MCP_16MHz_83k3BPS_CFG2 (0xBE)
#define MCP_16MHz_83k3BPS_CFG3 (0x07)

#define MCP_16MHz_50kBPS_CFG1 (0x07)
#define MCP_16MHz_50kBPS_CFG2 (0xFA)
#define MCP_16MHz_50kBPS_CFG3 (0x87)

#define MCP_16MHz_40kBPS_CFG1 (0x07)
#define MCP_16MHz_40kBPS_CFG2 (0xFF)
#define MCP_16MHz_40kBPS_CFG3 (0x87)

#define MCP_16MHz_33k3BPS_CFG1 (0x4E)
#define MCP_16MHz_33k3BPS_CFG2 (0xF1)
#define MCP_16MHz_33k3BPS_CFG3 (0x85)

#define MCP_16MHz_20kBPS_CFG1 (0x0F)
#define MCP_16MHz_20kBPS_CFG2 (0xFF)
#define MCP_16MHz_20kBPS_CFG3 (0x87)

#define MCP_16MHz_10kBPS_CFG1 (0x1F)
#define MCP_16MHz_10kBPS_CFG2 (0xFF)
#define MCP_16MHz_10kBPS_CFG3 (0x87)

#define MCP_16MHz_5kBPS_CFG1 (0x3F)
#define MCP_16MHz_5kBPS_CFG2 (0xFF)
#define MCP_16MHz_5kBPS_CFG3 (0x87)

/*
    speed 20
*/
#define MCP_20MHz_1000kBPS_CFG1 (0x00)
#define MCP_20MHz_1000kBPS_CFG2 (0xD9)
#define MCP_20MHz_1000kBPS_CFG3 (0x82)

#define MCP_20MHz_500kBPS_CFG1 (0x00)
#define MCP_20MHz_500kBPS_CFG2 (0xFA)
#define MCP_20MHz_500kBPS_CFG3 (0x87)

#define MCP_20MHz_250kBPS_CFG1 (0x41)
#define MCP_20MHz_250kBPS_CFG2 (0xFB)
#define MCP_20MHz_250kBPS_CFG3 (0x86)

#define MCP_20MHz_200kBPS_CFG1 (0x01)
#define MCP_20MHz_200kBPS_CFG2 (0xFF)
#define MCP_20MHz_200kBPS_CFG3 (0x87)

#define MCP_20MHz_125kBPS_CFG1 (0x03)
#define MCP_20MHz_125kBPS_CFG2 (0xFA)
#define MCP_20MHz_125kBPS_CFG3 (0x87)

#define MCP_20MHz_100kBPS_CFG1 (0x04)
#define MCP_20MHz_100kBPS_CFG2 (0xFA)
#define MCP_20MHz_100kBPS_CFG3 (0x87)

#define MCP_20MHz_83k3BPS_CFG1 (0x04)
#define MCP_20MHz_83k3BPS_CFG2 (0xFE)
#define MCP_20MHz_83k3BPS_CFG3 (0x87)

#define MCP_20MHz_80kBPS_CFG1 (0x04)
#define MCP_20MHz_80kBPS_CFG2 (0xFF)
#define MCP_20MHz_80kBPS_CFG3 (0x87)

#define MCP_20MHz_50kBPS_CFG1 (0x09)
#define MCP_20MHz_50kBPS_CFG2 (0xFA)
#define MCP_20MHz_50kBPS_CFG3 (0x87)

#define MCP_20MHz_40kBPS_CFG1 (0x09)
#define MCP_20MHz_40kBPS_CFG2 (0xFF)
#define MCP_20MHz_40kBPS_CFG3 (0x87)

#define MCP_20MHz_33k3BPS_CFG1 (0x0B)
#define MCP_20MHz_33k3BPS_CFG2 (0xFF)
#define MCP_20MHz_33k3BPS_CFG3 (0x87)

#define CAN_EFF_FLAG 0x80000000UL /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL /* omit EFF, RTR, ERR flags */

#define CAN_SFF_ID_BITS     11
#define CAN_EFF_ID_BITS     29

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

//SPI INSTRUCTIONS SET
enum INSTRUCTION{
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
enum REGISTER{
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

//MCP2515 flags.
 enum CANINTF {
    CANINTF_RX0IF = 0x01,
    CANINTF_RX1IF = 0x02,
    CANINTF_TX0IF = 0x04,
    CANINTF_TX1IF = 0x08,
    CANINTF_TX2IF = 0x10,
    CANINTF_ERRIF = 0x20,
    CANINTF_WAKIF = 0x40,
    CANINTF_MERRF = 0x80 
};

enum  STAT{
    STAT_RX0IF = (1<<0),
    STAT_RX1IF = (1<<1)
};

static const struct RXBn_REGS {
    enum REGISTER CTRL;
    enum REGISTER SIDH;
    enum REGISTER DATA;
    enum CANINTF  CANINTF_RXnIF;
};

static const struct TXBn_REGS {
    enum REGISTER CTRL;
    enum REGISTER SIDH;
    enum REGISTER DATA;
};

enum RXF {
    RXF0 = 0,
    RXF1 = 1,
    RXF2 = 2,
    RXF3 = 3,
    RXF4 = 4,
    RXF5 = 5
};

enum CAN_SPEED {
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_1000KBPS
};

enum MASK {
    MASK0,
    MASK1
};

enum TXBn {
    TXB0 = 0,
    TXB1 = 1,
    TXB2 = 2
};

enum RXBn {
    RXB0 = 0,
    RXB1 = 1
};

enum CAN_CLOCK {
    MCP_20MHZ,
    MCP_16MHZ,
    MCP_8MHZ
};

enum CANCTRL_REQOP_MODE {
    CANCTRL_REQOP_NORMAL     = 0x00,
    CANCTRL_REQOP_SLEEP      = 0x20,
    CANCTRL_REQOP_LOOPBACK   = 0x40,
    CANCTRL_REQOP_LISTENONLY = 0x60,
    CANCTRL_REQOP_CONFIG     = 0x80,
    CANCTRL_REQOP_POWERUP    = 0xE0
};

enum TXBnCTRL {
    TXB_ABTF   = 0x40,
    TXB_MLOA   = 0x20,
    TXB_TXERR  = 0x10,
    TXB_TXREQ  = 0x08,
    TXB_TXIE   = 0x04,
    TXB_TXP    = 0x03
};

struct TXBn_REGS TXB[3] = {
    {MCP_TXB0CTRL, MCP_TXB0SIDH, MCP_TXB0DATA},
    {MCP_TXB1CTRL, MCP_TXB1SIDH, MCP_TXB1DATA},
    {MCP_TXB2CTRL, MCP_TXB2SIDH, MCP_TXB2DATA}
};


struct RXBn_REGS RXB[2] = {
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
};

//This struct handles CAN data frame.
struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t can_data[8];
};


static const uint8_t MCP_SIDH = 0;
static const uint8_t MCP_SIDL = 1;
static const uint8_t MCP_EID8 = 2;
static const uint8_t MCP_EID0 = 3;
static const uint8_t MCP_DLC  = 4;
static const uint8_t MCP_DATA = 5;

static const uint8_t CANSTAT_OPMOD = 0xE0;
static const uint8_t CANSTAT_ICOD = 0x0E;

static const uint8_t CNF3_SOF = 0x80;

static const uint8_t TXB_EXIDE_MASK = 0x08;
static const uint8_t DLC_MASK       = 0x0F;
static const uint8_t RTR_MASK       = 0x40;

static const uint8_t RXBnCTRL_RXM_STD    = 0x20;
static const uint8_t RXBnCTRL_RXM_EXT    = 0x40;
static const uint8_t RXBnCTRL_RXM_STDEXT = 0x00;
static const uint8_t RXBnCTRL_RXM_MASK   = 0x60;
static const uint8_t RXBnCTRL_RTR        = 0x08;
static const uint8_t RXB0CTRL_BUKT       = 0x04;
static const uint8_t RXB0CTRL_FILHIT_MASK = 0x03;
static const uint8_t RXB1CTRL_FILHIT_MASK = 0x07;
static const uint8_t RXB0CTRL_FILHIT = 0x00;
static const uint8_t RXB1CTRL_FILHIT = 0x01;

static const uint8_t CANCTRL_REQOP = 0xE0;
static const uint8_t CANCTRL_ABAT = 0x10;
static const uint8_t CANCTRL_OSM = 0x08;
static const uint8_t CANCTRL_CLKEN = 0x04;
static const uint8_t CANCTRL_CLKPRE = 0x03;

static const int N_TXBUFFERS = 3;
static const int N_RXBUFFERS = 2;









//Following functions are used to manipulate MCP2515 registers.
//
//This function is used to read status of RXBn buffer.
uint8_t getStatus(struct spi_device *mcp2515_dev){
    uint8_t ret_val;
    uint8_t tx_val;
    tx_val = INSTRUCTION_READ_STATUS;

    spi_write_then_read(mcp2515_dev, &tx_val, 1,&ret_val, 1);
    return ret_val;
}

//This function is used to modify several bits on register without changing old data
void modifyRegister(struct spi_device *mcp2515_dev,enum REGISTER reg, uint8_t mask, const uint8_t data)
{
    uint8_t tx_val[4];

    tx_val[0] = INSTRUCTION_BITMOD;
    tx_val[1] = reg;
    tx_val[2] = mask;
    tx_val[3] = data;
    spi_write(mcp2515_dev, tx_val, 4);
}
//

//This function used to read 1 register from MCP2515
uint8_t readRegister(struct spi_device *mcp2515_dev, uint8_t reg){
    
    uint8_t val;
    uint8_t tx_val[2];

    tx_val[0] = INSTRUCTION_READ;
    tx_val[1] = reg;

    spi_write_then_read(mcp2515_dev, tx_val, 2,&val, 1);

    return val;
}
//

//This function is used to read multiple registers from MCP2515
void readRegisters(struct spi_device *mcp2515_dev, enum REGISTER reg, uint8_t rx_val[], uint8_t len){
    uint8_t tx_val[2];
    uint8_t i;

    //2 bytes of tx_val.
    tx_val[0] = INSTRUCTION_READ;
    tx_val[1] = reg;

    //MCP2515 has auto-increment of address-pointer.
    //Write 1 byte of dummny instruction then read 1 byte.
    for(i = 0; i < len; i++){
        spi_write_then_read(mcp2515_dev, tx_val, 2,&rx_val[i], 1);
        reg+=1;
        tx_val[1] = reg;
    }
}


void setRegister(struct spi_device *mcp2515_dev, enum REGISTER reg, uint8_t value)
{
    uint8_t tx_val[3];
    tx_val[0] = INSTRUCTION_WRITE;
    tx_val[1] = reg;
    tx_val[2] = value;
    
    spi_write(mcp2515_dev, tx_val, 3);
}

void setRegisters(struct spi_device *mcp2515_dev, enum REGISTER reg, uint8_t values[], uint8_t len)
{
    uint8_t tx_val[3];
    uint8_t i;

    //2 bytes of tx_val_first.
    tx_val[0] = INSTRUCTION_WRITE;
    tx_val[1] = reg;
    tx_val[2] = 0;

    //MCP2515 has auto-increment of address-pointer.
    //Write 1 byte of data continuously.
    for(i = 0; i < len; i++){
        tx_val[2] = values[i];
        spi_write(mcp2515_dev, tx_val, 3);
        reg+=1;
        tx_val[1] = reg;
    }
}
/////////////////////////////////////////////////////////////////////////////



















int setMode(struct spi_device *mcp2515_dev,enum CANCTRL_REQOP_MODE mode)
{
    int modeMatch = 0;
    int count = 0;
    uint8_t newmode;
    modifyRegister(mcp2515_dev,MCP_CANCTRL, CANCTRL_REQOP, mode);
    while (count < 1000) {
        count++;
        newmode = readRegister(mcp2515_dev,MCP_CANSTAT);
        newmode &= CANSTAT_OPMOD;

        if(newmode == mode)
            modeMatch = 1;

        if (modeMatch) {
            break;
        }
    }
    return modeMatch;
}


void prepareId(uint8_t *buffer, const int ext, const uint32_t id)
{
    u16 canid = (u16)(id & 0x0FFFF);

    if (ext) {
        buffer[MCP_EID0] = (uint8_t) (canid & 0xFF);
        buffer[MCP_EID8] = (uint8_t) (canid >> 8);
        canid = (u16)(id >> 16);
        buffer[MCP_SIDL] = (uint8_t) (canid & 0x03);
        buffer[MCP_SIDL] += (uint8_t) ((canid & 0x1C) << 3);
        buffer[MCP_SIDL] |= TXB_EXIDE_MASK;
        buffer[MCP_SIDH] = (uint8_t) (canid >> 5);
    } else {
        buffer[MCP_SIDH] = (uint8_t) (canid >> 3);
        buffer[MCP_SIDL] = (uint8_t) ((canid & 0x07 ) << 5);
        buffer[MCP_EID0] = 0;
        buffer[MCP_EID8] = 0;
    }
}

int setFilter(struct spi_device *mcp2515_dev,enum RXF num, int ext, uint32_t ulData)
{
    enum REGISTER reg;
    uint8_t tbufdata[4];
    int res = setMode(mcp2515_dev,CANCTRL_REQOP_CONFIG);
    if (res != 0) {
        return res;
    }

   

    switch (num) {
        case RXF0: reg = MCP_RXF0SIDH; break;
        case RXF1: reg = MCP_RXF1SIDH; break;
        case RXF2: reg = MCP_RXF2SIDH; break;
        case RXF3: reg = MCP_RXF3SIDH; break;
        case RXF4: reg = MCP_RXF4SIDH; break;
        case RXF5: reg = MCP_RXF5SIDH; break;
        default:
            return 0;
    }
    prepareId(tbufdata, ext, ulData);
    setRegisters(mcp2515_dev,reg, tbufdata, 4);

    return 0;
}

int setFilterMask(struct spi_device *mcp2515_dev,enum MASK mask, int ext, const uint32_t ulData)
{
    uint8_t tbufdata[4];
    enum REGISTER reg;
    int res = setMode(mcp2515_dev,CANCTRL_REQOP_CONFIG);
    if (res != 0) {
        return res;
    }
    
    
    prepareId(tbufdata, ext, ulData);
    switch (mask) {
        case MASK0: reg = MCP_RXM0SIDH; break;
        case MASK1: reg = MCP_RXM1SIDH; break;
        default:
            return 0;
    }

    setRegisters(mcp2515_dev,reg, tbufdata, 4);
    
    return 1;
}


int setBitrate(struct spi_device *mcp2515_dev)
{
    uint8_t set, cfg1, cfg2, cfg3;
    printk("Setting config mode");
    int error = setMode(mcp2515_dev,CANCTRL_REQOP_CONFIG);
    if (error != 1) {
        return error;
    }
    printk("Setting config mode success");
    set = 1;
    cfg1 = 0x01;
    cfg2 = 0x9A;
    cfg3 = 0x87;

    if (set) {
        printk("Inside setting config regs");
        setRegister(mcp2515_dev,MCP_CNF1, cfg1);
        setRegister(mcp2515_dev,MCP_CNF2, cfg2);
        setRegister(mcp2515_dev,MCP_CNF3, cfg3);
        return 1;
    }
    else {
        return 0;
    }
}






//These functions are used to Read CAN message from MCP2515.
//
//This function is called indirectly to read message out of RXBn buffers.
int readMessagefromHardware(struct spi_device *mcp2515_dev, enum RXBn rxbn, struct can_frame *frame)
{
    const struct RXBn_REGS *rxb = &RXB[rxbn];
    uint32_t id;
    uint8_t dlc;
    uint8_t ctrl;

    // Five bytes are used to store Standard and Extend Identifiers
    // Reading 5 bytes of Identifier to tbufdata
    uint8_t tbufdata[5];
    readRegisters(mcp2515_dev,rxb->SIDH, tbufdata, 5); // <- This function is platform dependent
    //

    //Bit manipulation to obtain ID field in the message
    //Inside tbufdata[5] array there are registers:
    //      + [0] SIDH 
    //      + [1] SIDL
    //      + [2] EIDH
    //      + [3] EIDL
    //      + [4] DLC
    //ID has 11 bits in length
    id = (tbufdata[MCP_SIDH]<<3) + (tbufdata[MCP_SIDL]>>5);

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
    dlc = (tbufdata[MCP_DLC] & DLC_MASK);
    if (dlc > 8) {
        return 0;
    }

    //Read value of CTRL register
    //CTRL register has 8 bits, including RTR bit, IDE bit, Reserved bit, Data filtering bits. 
    ctrl = readRegister(mcp2515_dev,rxb->CTRL); // <- This function is platform dependent.
    if (ctrl & RXBnCTRL_RTR) // <- If RTR bit of CTRL register is 1 then 
    {
        id |= CAN_RTR_FLAG; // <- Switch the corresponding RTR bit in the id to 1
    }

    //Assigning value to frame struct
    frame->can_id = id;
    frame->can_dlc = dlc;

    //Reading data and assigning to frame data
    readRegisters(mcp2515_dev,rxb->DATA, frame->can_data, dlc); // <- This function is platform dependent

    //Clearing CAN interrupt flag for new data to reside.
    modifyRegister(mcp2515_dev,MCP_CANINTF, rxb->CANINTF_RXnIF, 0); // <- This function is platform dependent

    return 0;
}

//This function will be called directly to get data frame
int readMessage(struct spi_device *mcp2515_dev,struct can_frame *frame)
{
    int rc;
    uint8_t stat = getStatus(mcp2515_dev);

    //If RX0IF is 1,there is data inside RXB0 buffer.Then read RBX0
    //
    //If RX1IF is 1,there is data inside RXB1 buffer.Then read RBX1
    //
    //Else, buffer is empty, quit the process.
    if ( stat & STAT_RX0IF ) {
        //Read CAN message from RXB0
        rc = readMessagefromHardware(mcp2515_dev,RXB0, frame);
    } 
    else if ( stat & STAT_RX1IF) {
        //Read CAN message from RXB1
        rc = readMessagefromHardware(mcp2515_dev,RXB1, frame);
    } else
    {
        //Quit function
        rc = 0;
    }
    return rc;
}
//////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
int reset(struct spi_device *mcp2515_dev)
{
    enum MASK masks[] = {MASK0, MASK1};
    uint8_t tx_val;
    uint8_t zeros[14];
    int i;
    enum RXF filters[] = {RXF0, RXF1, RXF2, RXF3, RXF4, RXF5};
    tx_val = INSTRUCTION_RESET;
   

    spi_write(mcp2515_dev, &tx_val, 1);

    mdelay(5);

    memset(zeros, 0, sizeof(zeros));
    setRegisters(mcp2515_dev,MCP_TXB0CTRL, zeros, 14);
    setRegisters(mcp2515_dev,MCP_TXB1CTRL, zeros, 14);
    setRegisters(mcp2515_dev,MCP_TXB2CTRL, zeros, 14);

    setRegister(mcp2515_dev, MCP_RXB0CTRL, 0);
    setRegister(mcp2515_dev, MCP_RXB1CTRL, 0);

    setRegister(mcp2515_dev, MCP_CANINTE, CANINTF_RX0IF | CANINTF_RX1IF | CANINTF_ERRIF | CANINTF_MERRF);

    // receives all valid messages using either Standard or Extended Identifiers that
    // meet filter criteria. RXF0 is applied for RXB0, RXF1 is applied for RXB1
    modifyRegister(mcp2515_dev, MCP_RXB0CTRL,
                   RXBnCTRL_RXM_MASK | RXB0CTRL_BUKT | RXB0CTRL_FILHIT_MASK,
                   RXBnCTRL_RXM_STDEXT | RXB0CTRL_BUKT | RXB0CTRL_FILHIT);
    modifyRegister(mcp2515_dev, MCP_RXB1CTRL,
                   RXBnCTRL_RXM_MASK | RXB1CTRL_FILHIT_MASK,
                   RXBnCTRL_RXM_STDEXT | RXB1CTRL_FILHIT);

    // clear filters and masks
    // do not filter any standard frames for RXF0 used by RXB0
    // do not filter any extended frames for RXF1 used by RXB1
    
    
    for (i=0; i<6; i++) {
        int ext = (i == 1);
        int result = setFilter(mcp2515_dev,filters[i], ext, 0);
        if (result != 1) {
            return result;
        }
    }

    
    for (i=0; i<2; i++) {
        int result = setFilterMask(mcp2515_dev,masks[i], 1, 0);
        if (result != 1) {
            return result;
        }
    }

    //Set the MCP2515 to config mode.
    setMode(mcp2515_dev, CANCTRL_REQOP_CONFIG);

    return 1;
}
////////////////////////////////////////////////////



////

int sendMessageinHardware(struct spi_device *mcp2515_dev, enum TXBn txbn, const struct can_frame *frame)
{
    if (frame->can_dlc > CAN_MAX_DLEN) {
        return 0;
    }

    const struct TXBn_REGS *txbuf = &TXB[txbn];

    uint8_t data[13];

    int ext = (frame->can_id & CAN_EFF_FLAG);
    int rtr = (frame->can_id & CAN_RTR_FLAG);
    uint32_t id = (frame->can_id & (ext ? CAN_EFF_MASK : CAN_SFF_MASK));

    prepareId(data, ext, id);

    data[MCP_DLC] = rtr ? (frame->can_dlc | RTR_MASK) : frame->can_dlc;

    memcpy(&data[MCP_DATA], frame->can_data, frame->can_dlc);

    setRegisters(mcp2515_dev,txbuf->SIDH, data, 5 + frame->can_dlc);

    modifyRegister(mcp2515_dev,txbuf->CTRL, TXB_TXREQ, TXB_TXREQ);

    uint8_t ctrl = readRegister(mcp2515_dev, txbuf->CTRL);
    if ((ctrl & (TXB_ABTF | TXB_MLOA | TXB_TXERR)) != 0) {
        return 0;
    }
    return 1;
}

int sendMessage(struct spi_device *mcp2515_dev, const struct can_frame *frame)
{
    int i=0;
    if (frame->can_dlc > CAN_MAX_DLEN) {
        return 0;
    }

    enum TXBn txBuffers[3] = {TXB0, TXB1, TXB2};

    for (i; i<N_TXBUFFERS; i++) {
        const struct TXBn_REGS *txbuf = &TXB[txBuffers[i]];
        uint8_t ctrlval = readRegister(mcp2515_dev, txbuf->CTRL);
        if ( (ctrlval & TXB_TXREQ) == 0 ) {
            return sendMessageinHardware(mcp2515_dev, txBuffers[i], frame);
        }
    }

    return 0;
}