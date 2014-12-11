/*
 * modify-2014.12.11 安全机制重做，确保应用/驱动不会产生冲突
 * modify-2014.11.27 再次优化了总线接口，去掉了初始化总线引脚的功能，因为会被其他多个驱动调用，总线只需要地址和值这两个参数即可
 * modify-2014.11.25 优化了总线接口，仔细想了一下，其实总线没有必要支持多设备，因为一条总线理论上可以挂无限多的设备
 * modify-2014.11.18 ultimate_drivers/ud_device_bus_emulated/ud_device_bus_emulated.c
 * 依据多设备驱动的模型构建，本来是想做成多设备的，而且模拟总线支持多设备也是理所当然的
 * 但是实际运用中，由于模拟总线需要的参数太多，故放弃了多设备的想法
 * 提供了open,release,write,read,ioctl接口
 * 适用范围：通用（会调用到GPIO的export_symbol接口，故需要GPIO支持）
 */
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
#include <linux/spinlock.h>

#include <asm/uaccess.h>

#include "../include/ud_device_bus_emulated.h"
#include "../include/common.h"

struct bus_io
{
    //模拟总线固有延时
    unsigned int        u32_bus_io_delay;
    //地址位数
    unsigned int        u32_bus_io_addr_bit;
    //数据位数
    unsigned int        u32_bus_io_data_bit;
    //片选脚配置
    enum gpio_enum_pin  x_bus_io_cs;
    //输出使能脚配置
    enum gpio_enum_pin  x_bus_io_oe;
    //写操作使能脚配置
    enum gpio_enum_pin  x_bus_io_we;
    //总线地址IO脚配置
    enum gpio_enum_pin  x_p_bus_io_addr[UD_BUS_ADDR_BIT];
    //总线数据IO脚配置
    enum gpio_enum_pin  x_p_bus_io_data[UD_BUS_DATA_BIT];
};

struct bus_dev
{
    //互斥锁
    struct mutex        x_lock;
    //cdev
    struct cdev         x_cdev;
};

static struct bus_io x_bus_io =
{
    .u32_bus_io_delay = 2,
    .u32_bus_io_addr_bit = 3,
    .u32_bus_io_data_bit = 8,
    .x_bus_io_cs = UD_PIN_PA29,
    .x_bus_io_oe = UD_PIN_PA31,
    .x_bus_io_we = UD_PIN_PA25,
    .x_p_bus_io_addr[0] = UD_PIN_PA28,
    .x_p_bus_io_addr[1] = UD_PIN_PA26,
    .x_p_bus_io_addr[2] = UD_PIN_PA22,
    .x_p_bus_io_data[0] = UD_PIN_PD14,
    .x_p_bus_io_data[1] = UD_PIN_PD15,
    .x_p_bus_io_data[2] = UD_PIN_PD16,
    .x_p_bus_io_data[3] = UD_PIN_PD17,
    .x_p_bus_io_data[4] = UD_PIN_PD18,
    .x_p_bus_io_data[5] = UD_PIN_PD19,
    .x_p_bus_io_data[6] = UD_PIN_PD20,
    .x_p_bus_io_data[7] = UD_PIN_PD21,
};

//主设备号
int major = UD_BUS_MAJOR;
//次设备号
int minor = 0;
//设备数量
int i32_bus_max_devs = UD_BUS_MAX_DEVS;

module_param(major, int ,S_IRUGO);
module_param(minor, int ,S_IRUGO);
//modify-2014.11.18 去掉了多设备的模块参数
//module_param(i32_bus_max_devs, int ,S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");

//载入GPIO驱动函数接口
extern int ud_gpio_export_set_dir (struct gpio_struct *);
extern int ud_gpio_export_set_value (struct gpio_struct *);
extern int ud_gpio_export_get_value (struct gpio_struct *);

struct bus_dev * x_p_bus_devices;

static void __exit ud_bus_module_exit (void);
static int __init ud_bus_module_init (void);

void ud_bus_delay (int i32_delay);
int ud_bus_reset(void);
int ud_bus_export_init (void);
int ud_bus_export_set_data (struct bus_struct * x_p_bus);
int ud_bus_export_get_data (struct bus_struct * x_p_bus);

int ud_bus_reset(void)
{
    struct gpio_struct x_tmp_gpio;

    x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_cs;
    ud_gpio_export_set_value(&x_tmp_gpio);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_oe;
    ud_gpio_export_set_value(&x_tmp_gpio);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_we;
    ud_gpio_export_set_value(&x_tmp_gpio);

    return (0);
}

int ud_bus_export_init (void)
{
    int i;
    struct gpio_struct x_tmp_gpio;

    x_tmp_gpio.x_dir = UD_GPIO_DIR_OUTPUT;

    x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_cs;
    ud_gpio_export_set_dir(&x_tmp_gpio);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_oe;
    ud_gpio_export_set_dir(&x_tmp_gpio);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_we;
    ud_gpio_export_set_dir(&x_tmp_gpio);

    for(i = 0; i<x_bus_io.u32_bus_io_addr_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_addr[i];
        ud_gpio_export_set_dir(&x_tmp_gpio);
    }

    for(i = 0; i<x_bus_io.u32_bus_io_data_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_data[i];
        ud_gpio_export_set_dir(&x_tmp_gpio);
    }

    return (0);
}

int ud_bus_export_set_data (struct bus_struct * x_p_bus)
{
    int i;
    unsigned long u32_temp;
    struct gpio_struct x_tmp_gpio;

    mutex_lock(x_p_bus_devices->x_lock);

    u32_temp = x_p_bus->u32_bus_addr;

    //逐位设置每个对应地址参数IO脚的电平
    for (i = 0; i < x_bus_io.u32_bus_io_addr_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_addr[i];
        if (u32_temp & 0x00000001)
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
        }
        else
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
        }
        ud_gpio_export_set_value(&x_tmp_gpio);
        u32_temp >>= 1;
    }

    u32_temp = x_p_bus->u32_bus_data;

    x_tmp_gpio.x_dir = UD_GPIO_DIR_OUTPUT;
    //逐位设置每个对应数据参数IO脚的电平，IO口统一设置为输出
    for (i = 0; i < x_bus_io.u32_bus_io_data_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_data[i];

        if (u32_temp & 0x00000001)
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
        }
        else
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
        }
        ud_gpio_export_set_dir(&x_tmp_gpio);
        u32_temp >>= 1;
    }

    //oe高：输出禁能，we低：写使能，cs低->cs高
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_oe;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
    ud_gpio_export_set_value(&x_tmp_gpio);
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_we;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
    ud_gpio_export_set_value(&x_tmp_gpio);

    //ud_bus_delay(x_bus_io.u32_bus_io_delay);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_cs;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
    ud_gpio_export_set_value(&x_tmp_gpio);

    ud_bus_delay(x_bus_io.u32_bus_io_delay);
    ud_bus_reset();
    ud_bus_delay(x_bus_io.u32_bus_io_delay);

    mutex_unlock(x_p_bus_devices->x_lock);

    return (0);
}

int ud_bus_export_get_data (struct bus_struct * x_p_bus)
{
    int i;
    unsigned long u32_temp;
    struct gpio_struct x_tmp_gpio;

    mutex_lock(x_p_bus_devices->x_lock);

    u32_temp = x_p_bus->u32_bus_addr;

    //逐位设置每个对应地址参数IO脚的电平
    for (i = 0; i < x_bus_io.u32_bus_io_addr_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_addr[i];
        if (u32_temp & 0x00000001)
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
        }
        else
        {
            x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
        }
        ud_gpio_export_set_value(&x_tmp_gpio);
        u32_temp >>= 1;
    }

    u32_temp = 0;

    x_tmp_gpio.x_dir = UD_GPIO_DIR_INPUT;
    x_tmp_gpio.x_pullup = UD_GPIO_PULLUP_ON;
    //数据IO设置为输入
    for (i = 0; i < x_bus_io.u32_bus_io_data_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_data[i];
        ud_gpio_export_set_dir(&x_tmp_gpio);
    }

    //oe低：输出使能，we高：读使能，cs低->cs高
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_oe;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
    ud_gpio_export_set_value(&x_tmp_gpio);
    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_we;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_HIGH;
    ud_gpio_export_set_value(&x_tmp_gpio);

    //ud_bus_delay(x_bus_io.u32_bus_io_delay);

    x_tmp_gpio.x_pin = x_bus_io.x_bus_io_cs;
    x_tmp_gpio.x_value = UD_GPIO_VALUE_LOW;
    ud_gpio_export_set_value(&x_tmp_gpio);

    ud_bus_delay(x_bus_io.u32_bus_io_delay);

    for (i = 0 ; i < x_bus_io.u32_bus_io_data_bit; i++)
    {
        x_tmp_gpio.x_pin = x_bus_io.x_p_bus_io_data[x_bus_io.u32_bus_io_data_bit - i - 1];
        ud_gpio_export_get_value(&x_tmp_gpio);
        //printd("bus %d : %d\n", i, x_tmp_gpio.x_value);
        if (x_tmp_gpio.x_value == UD_GPIO_VALUE_HIGH)
        {
            u32_temp |= 0x00000001;
        }

        if(i != x_bus_io.u32_bus_io_data_bit - 1)
        {
        u32_temp <<= 1;
        }
    }

    ud_bus_reset();

    x_p_bus->u32_bus_data = u32_temp;

    mutex_unlock(x_p_bus_devices->x_lock);

    return (0);
}


void ud_bus_delay (int i32_delay)
{
    while (i32_delay--)
        ;
}

int ud_bus_open (struct inode * x_p_inode, struct file * x_p_file)
{
    struct bus_dev * x_p_devices;
    x_p_devices = container_of(x_p_inode->i_cdev, struct bus_dev, x_cdev);
    x_p_file->private_data = x_p_devices;

    return (0);
}

int ud_bus_release (struct inode * x_p_inode, struct file * x_p_file)
{
    return (0);
}

ssize_t ud_bus_read (struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}

ssize_t ud_bus_write (struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}

long ud_bus_ioctl (struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg)
{
    long i32_result = 0;
    unsigned long u32_flags;

    struct bus_dev * x_p_devices;
    struct bus_struct * x_p_bus;

    x_p_devices = (struct bus_dev *) x_p_file->private_data;

    //创建struct bus_struct用以接受外部参数
    x_p_bus = (struct bus_struct *) kmalloc(sizeof(struct bus_struct), GFP_KERNEL);
    if (!x_p_bus)
    {
        printd("out of memory \n");
        i32_result = -ENOMEM;
        goto fail0;
    }

    //拷贝到内部空间
    if (0 != copy_from_user(x_p_bus, (struct bus_struct*) u32_arg, sizeof(struct bus_struct)))
    {
        printd("copy error \n");
        i32_result = -EPERM;
        goto fail0;
    }

    switch (u32_cmd)
    {
    case UD_BUS_CMD_SET_DATA :
        ud_bus_export_set_data(x_p_bus);
        break;
    case UD_BUS_CMD_GET_DATA :
        ud_bus_export_get_data(x_p_bus);

        if (0 != copy_to_user((struct bus_struct*) u32_arg, x_p_bus, sizeof(struct bus_struct)))
        {
            printd("copy error \n");
            i32_result = -EPERM;
            goto fail0;
        }
        ud_bus_delay(x_bus_io.u32_bus_io_delay);

        break;
    default :
        printd("cmd error \n");
        i32_result = -EINVAL;
        goto fail0;
    }

    fail0 : kfree(x_p_bus);
    return (i32_result);
}

struct file_operations bus_fops =
{
    .owner = THIS_MODULE,
    .read = ud_bus_read,
    .write = ud_bus_write,
    .unlocked_ioctl = ud_bus_ioctl,
    .open = ud_bus_open,
    .release = ud_bus_release, };

static int __init ud_bus_module_init (void)
{
    int i32_result, i32_err;
    dev_t x_dev = 0;
    int i;

    if (major)
    {
        x_dev = MKDEV(major, minor);
        i32_result = register_chrdev_region(x_dev, i32_bus_max_devs, "ud_bus");
    }
    else
    {
        i32_result = alloc_chrdev_region(&x_dev, minor, i32_bus_max_devs, "ud_bus");
        major = MAJOR(x_dev);
        printd("dev major is %d\n", major);
    }

    if (i32_result < 0)
    {
        printd("can't get major \n");
        return (i32_result);
    }

    x_p_bus_devices = kmalloc(i32_bus_max_devs * sizeof(struct bus_dev), GFP_KERNEL);
    if (!x_p_bus_devices)
    {
        printd("out of memory \n");
        i32_result = -ENOMEM;
        goto fail;
    }

    memset(x_p_bus_devices, 0, i32_bus_max_devs * sizeof(struct bus_dev));

    ud_bus_export_init();

    for (i = 0; i < i32_bus_max_devs; i++)
    {
        x_dev = MKDEV(major, minor + i);
        cdev_init(&x_p_bus_devices[i].x_cdev, &bus_fops);
        x_p_bus_devices[i].x_cdev.owner = THIS_MODULE;
        x_p_bus_devices[i].x_cdev.ops = &bus_fops;
        i32_err = cdev_add(&x_p_bus_devices[i].x_cdev, x_dev, 1);
        if (i32_err)
        {
            printd("error %d adding cdev %d", i32_err, i);
            i32_result = -ENOSPC;
            goto fail;
        }
    }

    printd("insmod successfully\n");
    return (0);

    fail : ud_bus_module_exit();
    return (i32_result);
}

static void __exit ud_bus_module_exit (void)
{
    dev_t x_dev = MKDEV(major, minor);
    int i;

    if (x_p_bus_devices)
    {
        for (i = 0; i < i32_bus_max_devs; i++)
        {
            cdev_del(&x_p_bus_devices[i].x_cdev);
        }
        kfree(x_p_bus_devices);
    }

    unregister_chrdev_region(x_dev, i32_bus_max_devs);

    printd("rmmod successfully\n");
}

EXPORT_SYMBOL(ud_bus_export_init);
EXPORT_SYMBOL(ud_bus_export_set_data);
EXPORT_SYMBOL(ud_bus_export_get_data);

module_init(ud_bus_module_init);
module_exit(ud_bus_module_exit);
