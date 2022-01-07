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
	.read = 	mcp2515_read,
	.write =	mcp215_write,
};

uint8_t mcp2515_read(struct spi_device *mcp2515_dev, uint8_t reg){
	u8 tx_val[] = {0x03, reg};
	u8 rx_val = 0x00;
	spi_write_then_read(mcp2515_dev, tx_val, 2, &rx_val, 1);
	printk("Value from register 0x%x: 0x%x", reg, rx_val);
    return rx_val;
}

void mcp2515_write(struct spi_device *mcp2515_dev, uint8_t reg, uint8_t val){
	u8 tx_val1[] = {0x02, reg, val};
	spi_write(mcp2515_dev, tx_val1, 3);
	printk("Write value 0x%x to register 0x%x", val, reg);
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
	printk("0x%x", rx_val);
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