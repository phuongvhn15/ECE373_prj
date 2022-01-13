/****************************************************
* This driver is based on group 1 with modifications to 
*   be competiable to our project												
* Group 2.														
* Instructor : Ho Van Nguyen Phuong					
* Contributor : Truong Phu Khanh Huy
*               Nguyen Van Thin
*               Nguyen Duc Minh				
* **************************************************/
/*********************************************************************************************************
	Enable SPI interface: sudo raspi-config
	Compile dts-overlay: dtc spidev_disabler.dts -O dtb >spidev_disabler.dtbo
	Load file dts: sudo dtoverlay -d . spidev_disabler
**********************************************************************************************************/
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
#include "MCP2515_CAN_Driver.c"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Team2: KhanhHuy,VanThin,DucMinh");
MODULE_DESCRIPTION("MCP2515 KERNEL");

#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev_spi;
static dev_t mcp2515_dev;
struct cdev mcp2515_cdev;
static struct class *my_class;

static ssize_t mcp2515_read(struct file *File, char __user *buf, size_t count, loff_t *offs) {
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

	if(readMessage(mcp2515_dev_spi,&CAN_FRAME)){
		printk("Read message successful");
	}
	else
		printk("Fail to read message ");

	
	u8 id_dlc_buffer[2];
	
	id_dlc_buffer[0] = CAN_FRAME.can_id;
	id_dlc_buffer[1] = CAN_FRAME.can_dlc;
	printk("id_dlc_buffer: %x %x :", id_dlc_buffer[0], id_dlc_buffer[1]);
	
	//
	//Copy can_data to data buffer
	u8 data_buffer[8];
	for(i = 0; i < 8; i++){
		data_buffer[i] = CAN_FRAME.can_data[i];
	}
	//
	printk("data_buffer: %x %x %x %x %x %x %x %x:", data_buffer[0], id_dlc_buffer[1], data_buffer[2], data_buffer[3], data_buffer[4], data_buffer[5], data_buffer[6], data_buffer[7]);


	//Concatenate id, dlc, data into 1 data array
	u8 can_buffer[2 + 8];

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
	copy_to_user(buf, can_buffer, 10);
	return 1;
}

static ssize_t mcp2515_write(struct file *filp, const char *buffer, size_t length, loff_t * offset) {
	int i;
	int count = 0;
	int error;
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
	CAN_FRAME.can_id = buffer[0];
	CAN_FRAME.can_dlc = buffer[1];

	//Copy 8 bytes of can_data to CAN_FRAME.
	for(i = 0; i < 8; i++){
		CAN_FRAME.can_data[i] = buffer[i+2];
	} 

	//printk("Sending CAN message : %s", CAN_FRAME.can_data);
	error = sendMessage(mcp2515_dev_spi, &CAN_FRAME);
	return error;
}

static const struct file_operations mcp2515_fops = {
	.owner =	THIS_MODULE,
	.read = 	mcp2515_read,
	.write =	mcp2515_write,
};

/*Init and Exit module*/
static int __init ModuleInit(void)
{
	struct spi_master *master;
	
	//SPI device information
	struct spi_board_info spi_device_info = {
		.modalias = "mcp2515_dev_spi",
		.max_speed_hz = 12000000,
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 4,
	};
	
	printk("Hello kernel!\n");

	//Access to SPI bus
	master = spi_busnum_to_master(MY_BUS_NUM);
	if(!master)
	{
		printk("There is no spi bus %d\n", MY_BUS_NUM);
		return -1;
	}
	
	//Create new SPI device
	mcp2515_dev_spi = spi_new_device(master, &spi_device_info);
	if(!mcp2515_dev_spi)
	{
		printk("Couldn't create device!\n");
		return -1;
	}
	
	mcp2515_dev_spi -> bits_per_word = 8;
	
	if(spi_setup(mcp2515_dev_spi) != 0)
	{
		printk("Could not change bus set-up!\n");
		spi_unregister_device(mcp2515_dev);
		return -1;
	}

	if(setBitrate(mcp2515_dev_spi))
	{
		printk("Set bit rate success");
	}
	else
	{
		printk("Set bit rate fail");
	}

	printk("%s","Inside setMode function");
	setMode(mcp2515_dev_spi, CANCTRL_REQOP_NORMAL);

	char buffer[64];

	alloc_chrdev_region(&mcp2515_dev, 0, 1, "mcp2515_dev");
    printk(KERN_INFO "%s\n", format_dev_t(buffer, mcp2515_dev));

	if((my_class = class_create(THIS_MODULE, "ModuleClass")) == NULL)
	{
		printk("Device class can not be created!\n");
	}
	else
	{
		printk("Device class created!\n");
	}

	if(device_create(my_class, NULL, mcp2515_dev, NULL, "mcp2515_dev") == NULL)
	{
		printk("Can not create device file!\n");
	}
	else
	{
		printk("Create device file!\n");
	}

	cdev_init(&mcp2515_cdev, &mcp2515_fops);
    mcp2515_cdev.owner = THIS_MODULE;
    cdev_add(&mcp2515_cdev, mcp2515_dev, 1);
	
	return 0;
}

static void __exit ModuleExit(void)
{
	cdev_del(&mcp2515_cdev);
	device_destroy(my_class, mcp2515_dev);
	class_destroy(my_class);
    unregister_chrdev_region(mcp2515_dev, 1);
    if(mcp2515_dev_spi)
    {
        spi_unregister_device(mcp2515_dev_spi);
    }
	printk("Goodbye kernel!\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);