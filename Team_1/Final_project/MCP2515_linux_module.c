/****************************************************
* This driver is written by Group 1 for the ECE372  *
* course project. It is written based on Arduino  	*
* mcp2515 driver.									*
* 													*
* You are free to copy and modify as you like!!		*	
*													*
* Group 4.													*			
* Instructor : Hồ Văn Nguyên Phương					*
* Contributor : Nguyễn Cao Minh						*
*				Phan Anh Tú							*
*				Lưu Anh Khang						*
*				Vũ Việt Hoàng						*
* **************************************************/

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
MODULE_AUTHOR("Nhom4: Khang, Minhproviptk, Tu, Hoang");
MODULE_DESCRIPTION("MCP2515 linux module");

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

	//Setting bitrate of 500Kbs and MCP2515 clock of 12Mhz.
	if(setBitrate(mcp2515_dev)){
		printk("Set bit rate success");
	}
	else
		printk("Set bit rate fail");
	printk("%s","Inside setMode function");
	setMode(mcp2515_dev,CANCTRL_REQOP_NORMAL);

	////Test Sending and Receiving.
	// u8 rx_val[] = {0,0,0};
	// readRegisters(mcp2515_dev, 40, rx_val, 3);
	// printk("bitrate config registers: %x %x %x", rx_val[0], rx_val[1], rx_val[2]);

	// readMessage(mcp2515_dev, &can_frame_rx);
	// printk("can_dlc: %d, can_id: %x, can_data: %x %x %x %x ", can_frame_rx.can_dlc, can_frame_rx.can_id, can_frame_rx.can_data[0],can_frame_rx.can_data[1],can_frame_rx.can_data[2],can_frame_rx.can_data[3]);

	// can_frame_tx.can_id = 0xf2;
	// can_frame_tx.can_dlc = 8;
	// can_frame_tx.can_data[0] = 1;
	// can_frame_tx.can_data[1] = 2;
	// can_frame_tx.can_data[2] = 3;
	// can_frame_tx.can_data[3] = 4;
	// can_frame_tx.can_data[4] = 5;
	// can_frame_tx.can_data[5] = 6;
	// can_frame_tx.can_data[6] = 7;
	// can_frame_tx.can_data[7] = 8;
	// printk("Sending CAN message");
	// int count = 0;
	// while(count <10){
	// 	count++;
	// 	sendMessage(mcp2515_dev, &can_frame_tx);
	// }
	
	return 0;
}

/**
 * @brief 
 * 
 * @param File file handler được trả về từ hàm fopen
 * @param user_buffer buffer dùng để chứa giá trị
 * @param count số lượng byte của buffer
 * @param offs 
 * @return ssize_t 
 */

static ssize_t mcp2515_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
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
	else
		printk("Fail to read message ");

	
	u32 can_id = CAN_FRAME.can_id;
	u8 can_dlc = CAN_FRAME.can_dlc;
	
	char id_dlc_buffer[2];
	sprintf(id_dlc_buffer,"%x%x", can_id, can_dlc);
	printk("id_dlc_buffer: %x %x :", id_dlc_buffer[0], id_dlc_buffer[1]);
	
	//
	//Copy can_data to data buffer
	char data_buffer[8];
	for(i = 0; i < 8; i++){
		sprintf(&data_buffer[i], "%x", CAN_FRAME.can_data[i]);
	}
	//
	printk("data_buffer: %x %x %x %x %x %x %x %x:", data_buffer[0], id_dlc_buffer[1], data_buffer[2], data_buffer[3], data_buffer[4], data_buffer[5], data_buffer[6], data_buffer[7]);


	//Concatenate id, dlc, data into 1 data array
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
static struct file_operations fops = {
	.owner = THIS_MODULE,
	//.open = mcp2515_open,
	//.release = mcp2515_close,
	.read = mcp2515_read,
	.write = mcp2515_write
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
