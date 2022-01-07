#include <linux/module.h>
#include <linux/init.h>
#include <linux/spi/spi.h>

/*Driver Information*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Van Thanh Huy");
MODULE_DESCRIPTION("SPI module for MCP2515");

#define MY_BUS_NUM 0
static struct spi_device *mcp2515_dev;


static const struct file_operations mcp2515_fops = {
	.owner =	THIS_MODULE,
};

/*Init and Exit module*/
static int __init ModuleInit(void)
{
	struct spi_master *master;
	val[] = {0x0F, 0x10};
	u8 control;
	
	//SPI device information
	struct spi_board_info spi_device_info = {
		.modalias = "mcp2515",
		.max_speed_hz = 12000000,
		.bus_num = MY_BUS_NUM,
		.chip_select = 0,
		.mode = 1,
	};
	
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
	
	printk("Hello kernel!\n");
	spi_write(mcp2515_dev, val, sizeof(8));
    control = spiw8r8(mcp2515_dev, 0x0F);
    printk("MCP2515 control mode: 0x%x\n", control);
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