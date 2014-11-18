#ifndef __UD_DEVICE_BUS_EMULATED__
#define __UD_DEVICE_BUS_EMULATED__

#include <linux/ioctl.h>
#include "ud_driver_gpio.h"

#ifndef __UD_PRINT__
#define __UD_PRINT__
#define UD_DEBUG
#ifdef UD_DEBUG
#define printd(arg,x...)    printk(KERN_ALERT"UD debug:"arg,##x)
#else
#define printd(arg,x...)
#endif
#endif

#ifndef UD_BUS_MAJOR
#define UD_BUS_MAJOR       (0)
#endif

#ifndef UD_BUS_MAX_DEVS
#define UD_BUS_MAX_DEVS    (1)
#endif

#define UD_BUS_IOC_MAGIC  'b'
#define UD_BUS_CMD_SET_ADDR  _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_BUS_CMD_SET_DATA  _IO(UD_GPIO_IOC_MAGIC, 1)
#define UD_BUS_CMD_GET_DATA  _IO(UD_GPIO_IOC_MAGIC, 2)

#ifndef UD_BUS_ADDR_BIT
#define UD_BUS_ADDR_BIT    (3)
#endif

#ifndef UD_BUS_DATA_BIT
#define UD_BUS_DATA_BIT    (8)
#endif

struct bus_struct
{
    //地址
    unsigned long   u32_bus_addr;
    //数据
    unsigned long   u32_bus_data;
};

struct bus_io
{
    //模拟总线固有延时
    unsigned char       u8_bus_io_delay;
    //片选脚配置
    struct gpio_struct  x_bus_io_cs;
    //输出使能脚配置
    struct gpio_struct  x_bus_io_oe;
    //写操作使能脚配置
    struct gpio_struct  x_bus_io_we;
    //总线地址IO脚配置
    struct gpio_struct  x_p_bus_io_addr[UD_BUS_ADDR_BIT];
    //总线数据IO脚配置
    struct gpio_struct  x_p_bus_io_data[UD_BUS_DATA_BIT];
};

struct bus_dev
{
    //总线配置
    struct bus_io       x_bus_io;
    //自旋锁
    spinlock_t          x_spinlock;
    //cdev
    struct cdev         x_cdev;
};

int ud_bus_open(struct inode * x_p_inode, struct file * x_p_file);
int ud_bus_release(struct inode * x_p_inode, struct file * x_p_file);
ssize_t ud_bus_read(struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);
ssize_t ud_bus_write(struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);

#endif
