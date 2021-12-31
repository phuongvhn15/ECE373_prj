#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spi.h>
#include <linux/module.h>
#include <linux/init.h>
#include "FINAL_PROJECT_HDH_ver1.c"
#include <can.h>
#include <string.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple LKM to read and write some registers of a BMP280 sensor");


#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev;
static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = mcp2515_open,
	.release = mcp2515_close,
	.read = mcp2515_read,
	.write = mcp2515_write
};
/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	struct spi_master *master;

	/* Parameters for SPI device */
	struct spi_board_info spi_device_info = {
		.modalias = "mcp2515",
		.max_speed_hz = 1000000,
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 3,
	};

	/* Get access to spi bus */
	master = spi_busnum_to_master(MY_BUS_NUM);
	/* Check if we could get the master */
	if(!master) {
		printk("There is no spi bus with Nr. %d\n", MY_BUS_NUM);
		return -1;
	}

	/* Create new SPI device */
	mcp2515_dev = spi_new_device(master, &spi_device_info);
	if(!bmp280_dev) {
		printk("Could not create device!\n");
		return -1;
	}

	mcp2515_dev -> bits_per_word = 8;

	/* Setup the bus for device's parameters */
	if(spi_setup(mcp2515_dev) != 0){
		printk("Could not change bus setup!\n");
		spi_unregister_device(bmp280_dev);
		return -1;
	}

	/* Read Chip ID */
	reset();
	setBitrate(CAN_125KBPS);
	setMode(CANCTRL_REQOP_NORMAL);
	
	return 0;
}

char data_buffer[10];
mcp2515_read(hd, data_buffer, )
static ssize_t mcp2515_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	
	struct can_frame CAN_FRAME;
	if(readMessage(&CAN_FRAME) < 0){
		printk("Cant read message");
	}

	
	u32 can_id = CAN_FRAME.can_id;
	u8 can_dlc = CAN_FRAME.can_dlc;
	
	char id_dlc_buffer[4];
	sprintf(id_dlc_buffer,"%x%x", can_id, can_dlc);

	//Copy can_data to data buffer
	char data_buffer[can_dlc*2];
	
	int count = 0;
	for(int i = 0; i < can_dlc*2, i+=2){
		sprintf(can_buffer[i], "%x", CAN_FRAME.can_data[count]);
	}

	//Concatenate id, dlc, data into 1 data array
	char can_buffer[4 + can_dlc*2];

	for(int i = 0; i < 4; i++){
		can_buffer[i] = id_dlc_buffer[i];
	}

	for (int i = 4; i < (can_dlc*2+4); i++)
	{
		can_buffer[i] = data_buffer[i-4];
	}

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(can_buffer));

	/* Copy data to user */
	not_copied = copy_to_user(user_buffer, &can_buffer, to_copy);

	/* Calculate data */
	delta = to_copy - not_copied;

	return delta;
}


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
