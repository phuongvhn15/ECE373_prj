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
#include "mcp2515_driver.c"

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple LKM to read and write some registers of a BMP280 sensor");

char data_buffer[10];

#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev;
/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	struct spi_master *master;

	/* Parameters for SPI device */
	struct spi_board_info spi_device_info = {
		.modalias = "mcp2515_dev",
		.max_speed_hz = 12000000, //High speed SPI Interface 12Mhz
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 4, // SPI mode 0,0 and 0,1
	};

	printk("Inside busum_to_master function");
	/* Get access to spi bus */
	master = spi_busnum_to_master(MY_BUS_NUM);
	/* Check if we could get the master */
	if(!master) {
		printk("There is no spi bus with Nr. %d\n", MY_BUS_NUM);
		return -1;
	}

	printk("Inside spi_new_device function");
	/* Create new SPI device */
	mcp2515_dev = spi_new_device(master, &spi_device_info);
	if(!mcp2515_dev) {
		printk("Could not create device!\n");
		return -1;
	}

	mcp2515_dev -> bits_per_word = 8;

	printk("%s","Inside spi_setups function");
	/* Setup the bus for device's parameters */
	if(spi_setup(mcp2515_dev) != 0){
		printk("Could not change bus setup!\n");
		spi_unregister_device(mcp2515_dev);
		return -1;
	}

	// /* Read Chip ID */
	// printk("%s","Inside reset function");
	// //Reset and enter config mode.
	// reset(mcp2515_dev);
	// printk("%s","Inside setBitrate function");
	// setBitrate(mcp2515_dev,CAN_500KBPS, MCP_8MHZ);
	// printk("%s","Inside setMode function");
	// setMode(mcp2515_dev,CANCTRL_REQOP_NORMAL);

	// printk("Inside gpio set value");
	// gpio_set_value(24,0);

	// printk("Inside set Register value");
	// setRegister(mcp2515_dev, MCP_CANSTAT,10);
	// printk("%s","Inside readRegister function");
	// int reg_val = readRegister(mcp2515_dev, MCP_CANSTAT);
	// printk("CAN state register value :%d", reg_val);
	// gpio_set_value(24,1);
	// mdelay(2000);

	// gpio_set_value(24,0);
	// u8 tx_val1[] = {0x02, 0x36, 0x12};
	// u8 rx_val = 0;
	// printk("a %d", rx_val);
	
	// spi_write(mcp2515_dev, tx_val1, 3);
	// //gpio_set_value(24,1);

	// //gpio_set_value(24,0);
	// u8 tx_val2[] = {0x03, 0x36};
	// spi_write_then_read(mcp2515_dev, tx_val2, 2, &rx_val,1);
	// //gpio_set_value(24,1);
	// printk("b %x", rx_val);

	// u8 rx_val[] = {0,0,0};
	// //setRegister(mcp2515_dev, 0x36, 0x13);
	// readRegisters(mcp2515_dev, 0x36, rx_val, 3);
	// //gpio_set_value(24,1);
	// printk("b %d %d %d", rx_val[0], rx_val[1], rx_val[2]);

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

    //Reading data and assigning to frame data
    readRegisters(mcp2515_dev,rxb->DATA, frame->can_data, dlc); // <- This function is platform dependent

	printk("can id :%d can_dlc: %d", id, dlc);
    //Clearing CAN interrupt flag for new data to reside.
    modifyRegister(mcp2515_dev,MCP_CANINTF, rxb->CANINTF_RXnIF, 0); // <- This function is platform dependent

	return 0;
}


static ssize_t mcp2515_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	
	// struct can_frame CAN_FRAME;
	// if(readMessage(mcp2515_dev,&CAN_FRAME) < 0){
	// 	printk("Cant read message");
	// }

	
	// u32 can_id = CAN_FRAME.can_id;
	// u8 can_dlc = CAN_FRAME.can_dlc;
	
	// char id_dlc_buffer[4];
	// sprintf(id_dlc_buffer,"%x%x", can_id, can_dlc);

	// //Copy can_data to data buffer
	// char data_buffer[can_dlc*2];
	
	// int count_data = 0;
	// int i;
	// for(i = 0; i < can_dlc*2; i+=2){
	// 	sprintf(data_buffer[i], "%x", CAN_FRAME.can_data[count_data]);
	// }

	// //Concatenate id, dlc, data into 1 data array
	// char can_buffer[4 + can_dlc*2];

	// for(i = 0; i < 4; i++){
	// 	can_buffer[i] = id_dlc_buffer[i];
	// }

	// for (i = 4; i < (can_dlc*2+4); i++)
	// {
	// 	can_buffer[i] = data_buffer[i-4];
	// }

	int returned_val = readRegister(mcp2515_dev, MCP_CANSTAT);

	int to_copy = 0;
	int not_copied = 0;
	int delta = 0;
	/* Get amount of data to copy */
	//to_copy = min(count, sizeof(can_buffer));
	to_copy = min(count, sizeof(returned_val));
	/* Copy data to user */
	not_copied = copy_to_user(user_buffer, &returned_val, to_copy);

	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}
static struct file_operations fops = {
	.owner = THIS_MODULE,
	//.open = mcp2515_open,
	//.release = mcp2515_close,
	.read = mcp2515_read,
	//.write = mcp2515_write
};

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	if(mcp2515_dev)
		spi_unregister_device(mcp2515_dev);
		
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
