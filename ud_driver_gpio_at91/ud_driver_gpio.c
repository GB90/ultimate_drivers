#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/cdev.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/seq_file.h>

#include <mach/gpio.h>
#include <mach/at91_pmc.h>
#include <mach/at91_pio.h>

#include <asm/uaccess.h>

#include "ud_driver_gpio.h"

int i32_gpio_major = UD_GPIO_MAJOR;
int i32_gpio_minor = 0;
int i32_gpio_max_devs = UD_GPIO_MAX_DEVS;

module_param(i32_gpio_major, int ,S_IRUGO);
module_param(i32_gpio_minor, int ,S_IRUGO);
module_param(i32_gpio_max_devs, int ,S_IRUGO);

MODULE_LICENSE("Proprietary");

struct gpio_dev * x_p_gpio_devices;

static void __exit ud_gpio_module_exit(void);
static int __init ud_gpio_module_init(void);


int ud_gpio_open(struct inode * x_p_inode, struct file * x_p_file)
{
    struct gpio_dev * x_p_devices;
    x_p_devices = container_of(x_p_inode->i_cdev, struct gpio_dev, x_cdev);
    x_p_file->private_data = x_p_devices;
    return (0);
}

int ud_gpio_release(struct inode * x_p_inode, struct file * x_p_file)
{
    return (0);
}

ssize_t ud_gpio_read(struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}

ssize_t ud_gpio_write(struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}

long ud_gpio_ioctl(struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg)
{
    long                    i32_result = 0;
    unsigned long           u32_flags;
    unsigned int            u32_port_pin;
    struct gpio_dev *       x_p_devices;
    struct gpio_struct *    x_p_gpio;

    x_p_devices = (struct gpio_dev *)x_p_file->private_data;
    spin_lock_irqsave(&x_p_devices->x_spinlock, u32_flags);

    x_p_gpio    = (struct gpio_struct *)kmalloc(sizeof(struct gpio_struct), GFP_KERNEL);
    if(!x_p_gpio)
    {
        printd("out of memory /n");
        i32_result = -ENOMEM;
        goto fail1;
    }

    if(0 != copy_from_user(x_p_gpio, (struct gpio_struct*)u32_arg, sizeof(struct gpio_struct)))
    {
        printd("copy error /n");
        i32_result = -EPERM;
        goto fail0;
    }

    if(x_p_gpio->x_pin > 31)
    {
        printd("pin error /n");
        i32_result = -EINVAL;
        goto fail0;
    }

    switch(x_p_gpio->x_port)
    {
    case 0: u32_port_pin = PIN_BASE + 0x00 + x_p_gpio->x_pin; break;
    case 1: u32_port_pin = PIN_BASE + 0x20 + x_p_gpio->x_pin; break;
    case 2: u32_port_pin = PIN_BASE + 0x40 + x_p_gpio->x_pin; break;
    case 3: u32_port_pin = PIN_BASE + 0x60 + x_p_gpio->x_pin; break;
    case 4: u32_port_pin = PIN_BASE + 0x80 + x_p_gpio->x_pin; break;
    default :
        printd("port error /n");
        i32_result = -EINVAL;
        goto fail0;
    }

    switch(u32_cmd)
    {
    case UD_GPIO_CMD_SET_DIR :
        if(x_p_gpio->x_dir)
        {
            at91_set_gpio_output(u32_port_pin, x_p_gpio->x_value);
        }
        else
        {
            at91_set_gpio_input(u32_port_pin, x_p_gpio->x_pullup);
        }
        break;
    case UD_GPIO_CMD_SET_VALUE :
        at91_set_gpio_value(u32_port_pin, x_p_gpio->x_value);
        break;
    case UD_GPIO_CMD_GET_VALUE :
        if(at91_get_gpio_value(u32_port_pin) == 0)
        {
            x_p_gpio->x_value = UD_GPIO_VALUE_LOW;
        }
        else
        {
            x_p_gpio->x_value = UD_GPIO_VALUE_HIGH;
        }

        if(0 != copy_from_user((struct gpio_struct*)u32_arg, x_p_gpio, sizeof(struct gpio_struct)))
        {
            printd("copy error /n");
            i32_result = -EPERM;
            goto fail0;
        }
        break;
    default :
        printd("cmd error /n");
        i32_result = -EINVAL;
        goto fail0;
    }

    fail0:
    kfree(x_p_gpio);
    fail1:
    spin_unlock_irqrestore(&x_p_devices->x_spinlock, u32_flags);
    return (i32_result);
}


struct file_operations gpio_fops = {
    .owner          = THIS_MODULE,
    .read           = ud_gpio_read,
    .write          = ud_gpio_write,
    .unlocked_ioctl = ud_gpio_ioctl,
    .open           = ud_gpio_open,
    .release        = ud_gpio_release,
};


static int __init ud_gpio_module_init(void)
{
    int     i32_result, i32_err;
    dev_t   x_dev = 0;
    int     i;

    if(i32_gpio_major)
    {
        x_dev = MKDEV(i32_gpio_major, i32_gpio_minor);
        i32_result = register_chrdev_region(x_dev, i32_gpio_max_devs, "ud_gpio");
    }
    else
    {
        i32_result = alloc_chrdev_region(&x_dev, i32_gpio_minor, i32_gpio_max_devs, "ud_gpio");
        i32_gpio_major = MAJOR(x_dev);
    }

    if(i32_result < 0)
    {
        printd("can't get major /n");
        return (i32_result);
    }

    x_p_gpio_devices = kmalloc(i32_gpio_max_devs * sizeof(struct gpio_dev), GFP_KERNEL);
    if(!x_p_gpio_devices)
    {
        printd("out of memory /n");
        i32_result = -ENOMEM;
        goto fail;
    }

    memset(x_p_gpio_devices, 0, i32_gpio_max_devs * sizeof(struct gpio_dev));

    for(i=0; i<i32_gpio_max_devs; i++)
    {
        spin_lock_init(&x_p_gpio_devices[i].x_spinlock);

        x_dev = MKDEV(i32_gpio_major, i32_gpio_minor + i);
        cdev_init(&x_p_gpio_devices[i].x_cdev, &gpio_fops);
        x_p_gpio_devices[i].x_cdev.owner   = THIS_MODULE;
        x_p_gpio_devices[i].x_cdev.ops     = &gpio_fops;
        i32_err = cdev_add(&x_p_gpio_devices[i].x_cdev, x_dev, 1);
        if(i32_err)
        {
            printd("error %d adding cdev %d", i32_err, i);
            i32_result = -ENOSPC;
            goto fail;
        }
    }

    return (0);

    fail:
    ud_gpio_module_exit();
    return (i32_result);
}

static void __exit ud_gpio_module_exit(void)
{
    dev_t   x_dev = MKDEV(i32_gpio_major, i32_gpio_minor);
    int     i;

    if(x_p_gpio_devices)
    {
        for(i=0; i<i32_gpio_max_devs; i++)
        {
            cdev_del(&x_p_gpio_devices[i].x_cdev);
        }
        kfree(x_p_gpio_devices);
    }

    unregister_chrdev_region(x_dev, i32_gpio_max_devs);
}

module_init(ud_gpio_module_init);
module_exit(ud_gpio_module_exit);
