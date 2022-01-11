#include <linux/module.h>
#include <linux/init.h>
#include <linux/spi/spi.h>
#include "mcp2515_driver.c"

/*Driver Information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Van Thanh Huy");
MODULE_DESCRIPTION("SPI module for MCP2515");

#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev;

enum CANCTRL_REQOP_MODE {
    CANCTRL_REQOP_NORMAL     = 0x00,
    CANCTRL_REQOP_SLEEP      = 0x20,
    CANCTRL_REQOP_LOOPBACK   = 0x40,
    CANCTRL_REQOP_LISTENONLY = 0x60,
    CANCTRL_REQOP_CONFIG     = 0x80,
    CANCTRL_REQOP_POWERUP    = 0xE0
};

struct can_frame {
    uint32_t 	can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t    	can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t    	can_data[8];
};

static const struct file_operations mcp2515_fops = {
	.owner =	THIS_MODULE,
	.read = 	mcp2515_read,
	.write =	mcp215_write,
};

static ssize_t mcp2515_read(struct file *File, char *user_buffer, size_t count, loff_t *offs){
	int i;
	struct can_frame CAN_FRAME;

	CAN_FRAME.can_data[0] = 0;
	CAN_FRAME.can_data[1] = 0;
	CAN_FRAME.can_data[2] = 0;
	CAN_FRAME.can_data[3] = 0;
	CAN_FRAME.can_data[4] = 0;
	CAN_FRAME.can_data[5] = 0;
	CAN_FRAME.can_data[6] = 0;
	CAN_FRAME.can_data[7] = 0;

	if(readMessage(mcp2515_dev,&CAN_FRAME)){
		printk("Read message successful");
	}
	else{
		printk("Fail to read message ");
	}

	u32 can_id = CAN_FRAME.can_id;
	u8 can_dlc = CAN_FRAME.can_dlc;

	char id_dlc_buffer[2];
	sprintf(id_dlc_buffer,"%x%x", can_id, can_dlc);
	printk("id_dlc_buffer: %x %x :", id_dlc_buffer[0], id_dlc_buffer[1]);

	char data_buffer[8];
	for(i = 0; i < 8; i++){
		sprintf(&data_buffer[i], "%x", CAN_FRAME.can_data[i]);
	}

	printk("data_buffer: %x %x %x %x %x %x %x %x:", data_buffer[0], id_dlc_buffer[1], data_buffer[2], data_buffer[3], data_buffer[4], data_buffer[5], data_buffer[6], data_buffer[7]);

	char can_buffer[2 + 8];

	//Copy id and dlc to can_buffer.
	for(i = 0; i < 2; i++){
		can_buffer[i] = id_dlc_buffer[i];
	}
	//Copy data to can_buffer
	for (i = 2; i < 10; i++)
	{
		can_buffer[i] = data_buffer[i-2];
	}

	printk("Copy to userbuffer");
	copy_to_user(user_buffer, can_buffer, 10);
	return 1;
}

static ssize_t mcp2515_write(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int i;
	struct can_frame CAN_FRAME;

	CAN_FRAME.can_data[0] = 0;
	CAN_FRAME.can_data[1] = 0;
	CAN_FRAME.can_data[2] = 0;
	CAN_FRAME.can_data[3] = 0;
	CAN_FRAME.can_data[4] = 0;
	CAN_FRAME.can_data[5] = 0;
	CAN_FRAME.can_data[6] = 0;
	CAN_FRAME.can_data[7] = 0;

	//Copy 2 bytes of can_id and can_dlc to CAN_FRAME.
	CAN_FRAME.can_id = user_buffer[0];
	CAN_FRAME.can_dlc = user_buffer[1];

	//Copy 8 bytes of can_data to CAN_FRAME.
	for(i = 0; i < 8; i++){
		CAN_FRAME.can_data[i] = user_buffer[i+2];
	} 

	printk("Sending CAN message");
	sendMessage(mcp2515_dev, &CAN_FRAME);
}

/*Init and Exit module*/
static int __init ModuleInit(void)
{
	struct spi_master *master;
	
	//SPI device information
	struct spi_board_info spi_device_info = {
		.modalias = "mcp2515_dev",
		.max_speed_hz = 12000000,
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 4,
	};
	
	printk("Hello kernel!\n");

	//Access to SPI bus
	master = spi_busnum_to_master(MY_BUS_NUM);
	if(!master){
		printk("There is no spi bus %d\n", MY_BUS_NUM);
		return -1;
	}
	
	//Create new SPI device
	mcp2515_dev = spi_new_device(master, &spi_device_info);
	if(!mcp2515_dev){
		printk("Couldn't create device!\n");
		return -1;
	}
	
	mcp2515_dev -> bits_per_word = 8;
	
	if(spi_setup(mcp2515_dev) != 0){
		printk("Could not change bus set-up!\n");
		spi_unregister_device(mcp2515_dev);
		return -1;
	}

	if(setBitrate(mcp2515_dev)){
		printk("Set bit rate success");
	}
	else
		printk("Set bit rate fail");
	printk("%s","Inside setMode function");
	setMode(mcp2515_dev, CANCTRL_REQOP_NORMAL);
	
	printk("Hello kernel!\n");
	return 0;
}

static void __exit ModuleExit(void)
{
    if(mcp2515_dev)
    {
        spi_unregister_device(mcp2515_dev);
    }
	printk("Goodbye kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);