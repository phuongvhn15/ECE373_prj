/****************************************************
* This driver is written by Group 2 for the ECE372  
* course project. It is written based on Arduino  	
* mcp2515 driver.									
* 													
* You are free to copy and modify as you like!!	Thanks you!!		
*													
* Group 2.														
* Instructor : Hồ Văn Nguyên Phương					
* Contributor : Trương Phú Khánh Huy 
                Nguyễn Văn Thìn 
                Nguyễn Đức Minh		
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

static dev_t mcp2515_dev;		//defines structure to hold major and minor number of device//

struct cdev mcp2515_cdev;		 //defines structure to hold character device properties//

static struct class *my_class;

static struct spi_device *mcp2515_dev_spi;
static struct spi_device *mcp2515_dev_spi;
/**
 * @brief This function is called, when the module is loaded into the kernel
 */


/**
 * @brief 
 * 
 * @param File file handler được trả về từ hàm fopen
 * @param user_buffer buffer dùng để chứa giá trị
 * @param count số lượng byte của buffer
 * @param offs 
 * @return ssize_t 
 */
static ssize_t mcp2515_read(struct file *File, char __user *buf, size_t count, loff_t *offs) {

}
static ssize_t mcp2515_write(struct file *filp, const char *buffer, size_t length, loff_t * offset) {

}
/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
    cdev_del(&mcp2515_cdev);
	device_destroy(my_class,mcp2515_dev);
	class_destroy(my_class);
    unregister_chrdev_region( mcp2515_dev, 1 );
	if(mcp2515_dev_spi)
		spi_unregister_device(mcp2515_dev_spi);
	printk("Goodbye, Kernel\n");
}
module_init(ModuleInit);
module_exit(ModuleExit);