#ifndef __UD_DEVICE_BUS_EMULATED__
#define __UD_DEVICE_BUS_EMULATED__

#include <linux/ioctl.h>
#include "ud_driver_gpio.h"


#define UD_BUS_DEBUG

#ifdef UD_BUS_DEBUG
#define printd(arg,x...)    printk(KERN_ALERT"bus debug:"arg,##x)
#else
#define printd(arg,x...)
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
#define UD_BUS_ADDR_BIT    (16)
#endif

#ifndef UD_BUS_DATA_BIT
#define UD_BUS_DATA_BIT    (16)
#endif

struct bus_data
{
    unsigned long   x_bus_addr;
    unsigned long   x_bus_data;
};

struct gpio_io_next
{
    struct gpio_struct  *   x_io;
    struct gpio_io_next *   x_p_next;
};

struct bus_io
{
    unsigned char           u8_bus_io_delay;
    unsigned char           u8_bus_io_addr_bit;
    unsigned char           u8_bus_io_data_bit;
    struct gpio_struct      x_bus_io_cs;
    struct gpio_struct      x_bus_io_oe;
    struct gpio_struct      x_bus_io_we;
    struct gpio_io_next *   x_p_bus_io_addr;
    struct gpio_io_next *   x_p_bus_io_data;
};

struct bus_dev
{
    struct bus_io       x_bus_io;
    spinlock_t          x_spinlock;
    struct cdev         x_cdev;
};

int ud_bus_open(struct inode * x_p_inode, struct file * x_p_file);
int ud_bus_release(struct inode * x_p_inode, struct file * x_p_file);
ssize_t ud_bus_read(struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);
ssize_t ud_bus_write(struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);

#endif
