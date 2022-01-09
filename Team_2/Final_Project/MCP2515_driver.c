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
#include <linux/bitfield.h>
#include <linux/clk.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/freezer.h>

/* SPEED MCP2515 */
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
 *  speed 12M
 */
#define MCP_12MHz_1000kBPS_CFG1 (0x00)
#define MCP_12MHz_1000kBPS_CFG2 (0xD0)
#define MCP_12MHz_1000kBPS_CFG3 (0x82)

#define MCP_12MHz_500kBPS_CFG1 (0x00)
#define MCP_12MHz_500kBPS_CFG2 (0xF0)
#define MCP_12MHz_500kBPS_CFG3 (0x86)

#define MCP_12MHz_250kBPS_CFG1 (0x41)
#define MCP_12MHz_250kBPS_CFG2 (0xF1)
#define MCP_12MHz_250kBPS_CFG3 (0x85)

#define MCP_12MHz_200kBPS_CFG1 (0x01)
#define MCP_12MHz_200kBPS_CFG2 (0xFA)
#define MCP_12MHz_200kBPS_CFG3 (0x87)

#define MCP_12MHz_125kBPS_CFG1 (0x03)
#define MCP_12MHz_125kBPS_CFG2 (0xF0)
#define MCP_12MHz_125kBPS_CFG3 (0x86)

#define MCP_12MHz_100kBPS_CFG1 (0x03)
#define MCP_12MHz_100kBPS_CFG2 (0xFA)
#define MCP_12MHz_100kBPS_CFG3 (0x87)

#define MCP_12MHz_80kBPS_CFG1 (0x03)
#define MCP_12MHz_80kBPS_CFG2 (0xFF)
#define MCP_12MHz_80kBPS_CFG3 (0x87)

#define MCP_12MHz_83k3BPS_CFG1 (0x03)
#define MCP_12MHz_83k3BPS_CFG2 (0xBE)
#define MCP_12MHz_83k3BPS_CFG3 (0x07)

#define MCP_12MHz_50kBPS_CFG1 (0x07)
#define MCP_12MHz_50kBPS_CFG2 (0xFA)
#define MCP_12MHz_50kBPS_CFG3 (0x87)

#define MCP_12MHz_40kBPS_CFG1 (0x07)
#define MCP_12MHz_40kBPS_CFG2 (0xFF)
#define MCP_12MHz_40kBPS_CFG3 (0x87)

#define MCP_12MHz_33k3BPS_CFG1 (0x4E)
#define MCP_12MHz_33k3BPS_CFG2 (0xF1)
#define MCP_12MHz_33k3BPS_CFG3 (0x85)

#define MCP_12MHz_20kBPS_CFG1 (0x0F)
#define MCP_12MHz_20kBPS_CFG2 (0xFF)
#define MCP_12MHz_20kBPS_CFG3 (0x87)

#define MCP_12MHz_10kBPS_CFG1 (0x1F)
#define MCP_12MHz_10kBPS_CFG2 (0xFF)
#define MCP_12MHz_10kBPS_CFG3 (0x87)

#define MCP_12MHz_5kBPS_CFG1 (0x3F)
#define MCP_12MHz_5kBPS_CFG2 (0xFF)
#define MCP_12MHz_5kBPS_CFG3 (0x87)
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
 *  speed 20M
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

static const uint8_t CANCTRL_REQOP = 0xE0;
static const uint8_t CANCTRL_ABAT = 0x10;
static const uint8_t CANCTRL_OSM = 0x08;
static const uint8_t CANCTRL_CLKEN = 0x04;
static const uint8_t CANCTRL_CLKPRE = 0x03;
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
static const uint8_t RXBnCTRL_RTR=         0x08;
static const uint8_t RXB0CTRL_BUKT       = 0x04;
static const uint8_t RXB0CTRL_FILHIT_MASK = 0x03;
static const uint8_t RXB1CTRL_FILHIT_MASK = 0x07;
static const uint8_t RXB0CTRL_FILHIT = 0x00;
static const uint8_t RXB1CTRL_FILHIT = 0x01;

static const uint8_t MCP_SIDH = 0;
static const uint8_t MCP_SIDL = 1;
static const uint8_t MCP_EID8 = 2;
static const uint8_t MCP_EID0 = 3;
static const uint8_t MCP_DLC  = 4;
static const uint8_t MCP_DATA = 5;

static const struct TXBn_REGS {
    enum REGISTER CTRL;
    enum REGISTER SIDH;
     enum REGISTER DATA;
} TXB[N_TXBUFFERS];

static const struct RXBn_REGS {
    enum REGISTER CTRL;
    enum REGISTER SIDH;
    enum REGISTER DATA;
    enum CANINTF  CANINTF_RXnIF;
};

struct RXBn_REGS RXB[2] = {
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
};
/* SPI interface instruction set */
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

/* MCP2515 registers */
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

/* MCP2515 flags */
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
/* MCP2515 stat */
enum  STAT{
            STAT_RX0IF = (1<<0),
            STAT_RX1IF = (1<<1)
};

/* RXF */
enum RXF {
            RXF0 = 0,
            RXF1 = 1,
            RXF2 = 2,
            RXF3 = 3,
            RXF4 = 4,
            RXF5 = 5
};
/* CAN speed */
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

/* MASK */
enum MASK {
            MASK0,
            MASK1
};

/* RXBn */
enum RXBn {
            RXB0 = 0,
            RXB1 = 1
};

/* CAN clock */
enum CAN_CLOCK {
            MCP_20MHZ,
            MCP_16MHZ,
            MCP_12MHZ,
            MCP_8MHZ
};

/*      */
enum CANCTRL_REQOP_MODE {
            CANCTRL_REQOP_NORMAL     = 0x00,
            CANCTRL_REQOP_SLEEP      = 0x20,
            CANCTRL_REQOP_LOOPBACK   = 0x40,
            CANCTRL_REQOP_LISTENONLY = 0x60,
            CANCTRL_REQOP_CONFIG     = 0x80,
            CANCTRL_REQOP_POWERUP    = 0xE0
};

#define CAN_FRAME_MAX_DATA_LEN 8
#define CAN_FRAME_MAX_BITS 128
struct can_frame {
    uint32_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    data[CAN_FRAME_MAX_DATA_LEN];
};

