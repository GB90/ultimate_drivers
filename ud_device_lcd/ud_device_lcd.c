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
#include <linux/fb.h>

#include <asm/uaccess.h>

#include "../include/ud_device_lcd.h"
#include "../include/common.h"

struct glcd_dev
{
    //自旋锁
    spinlock_t x_spinlock;
    //cdev
    struct cdev x_cdev;
};

//主设备号
int major = UD_GLCD_MAJOR;
//次设备号
int minor = 0;
//设备数量
int max_devs = UD_GLCD_MAX_DEVS;

module_param(major, int ,S_IRUGO);
module_param(minor, int ,S_IRUGO);
module_param(max_devs, int ,S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");

extern int ud_lcd_init(void);
extern int ud_lcd_setcolor(unsigned char , unsigned char, unsigned char);
extern int ud_lcd_blank(int);
extern void ud_lcd_fillrect(const struct fb_fillrect *);
extern void ud_lcd_copyarea(const struct fb_copyarea *);
extern void ud_lcd_imageblit(const struct fb_image *);
extern void ud_lcd_rotate(int);
extern void ud_lcd_rotate_check(int *, int *);
extern void ud_lcd_refresh(void);

struct glcd_dev * x_p_glcd_devices;

static void __exit ud_glcd_module_exit (void);
static int __init ud_glcd_module_init (void);


int ud_glcd_open (struct inode * x_p_inode, struct file * x_p_file)
{
    struct glcd_dev * x_p_devices;
    x_p_devices = container_of(x_p_inode->i_cdev, struct glcd_dev, x_cdev);
    x_p_file->private_data = x_p_devices;
    return (0);
}

int ud_glcd_release (struct inode * x_p_inode, struct file * x_p_file)
{
    return (0);
}

ssize_t ud_glcd_read (struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}

ssize_t ud_glcd_write (struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    return (0);
}


long ud_glcd_ioctl (struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg)
{
    long i32_result = 0;
//    unsigned long u32_flags;
//    struct glcd_dev * x_p_devices;
//    struct glcd_struct * x_p_glcd;
//
//    x_p_devices = (struct glcd_dev *) x_p_file->private_data;
//    spin_lock_irqsave(&x_p_devices->x_spinlock, u32_flags);
//
//    x_p_glcd = (struct glcd_struct *) kmalloc(sizeof(struct glcd_struct), GFP_KERNEL);
//    if (!x_p_glcd)
//    {
//        printd("out of memory \n");
//        i32_result = -ENOMEM;
//        goto fail1;
//    }
//
//    if (0 != copy_from_user(x_p_glcd, (struct glcd_struct*) u32_arg, sizeof(struct glcd_struct)))
//    {
//        printd("copy error \n");
//        i32_result = -EPERM;
//        goto fail0;
//    }
//
//    switch (u32_cmd)
//    {
//    default :
//        printd("cmd error \n");
//        i32_result = -EINVAL;
//        goto fail0;
//    }
//
//    fail0 : kfree(x_p_glcd);
//    fail1 : spin_unlock_irqrestore(&x_p_devices->x_spinlock, u32_flags);
    return (i32_result);
}

struct file_operations glcd_fops =
{
    .owner = THIS_MODULE,
    .read = ud_glcd_read,
    .write = ud_glcd_write,
    .unlocked_ioctl = ud_glcd_ioctl,
    .open = ud_glcd_open,
    .release = ud_glcd_release,
};

static int __init ud_glcd_module_init (void)
{
    int i32_result, i32_err;
    dev_t x_dev = 0;
    int i;

    if (major)
    {
        x_dev = MKDEV(major, minor);
        i32_result = register_chrdev_region(x_dev, max_devs, "ud_glcd");
    }
    else
    {
        i32_result = alloc_chrdev_region(&x_dev, minor, max_devs, "ud_glcd");
        major = MAJOR(x_dev);
        printd("dev major is %d\n", major);
    }

    if (i32_result < 0)
    {
        printd("can't get major \n");
        return (i32_result);
    }

    x_p_glcd_devices = kmalloc(max_devs * sizeof(struct glcd_dev), GFP_KERNEL);
    if (!x_p_glcd_devices)
    {
        printd("out of memory \n");
        i32_result = -ENOMEM;
        goto fail;
    }

    memset(x_p_glcd_devices, 0, max_devs * sizeof(struct glcd_dev));

    for (i = 0; i < max_devs; i++)
    {
        spin_lock_init(&x_p_glcd_devices[i].x_spinlock);

        x_dev = MKDEV(major, minor + i);
        cdev_init(&x_p_glcd_devices[i].x_cdev, &glcd_fops);
        x_p_glcd_devices[i].x_cdev.owner = THIS_MODULE;
        x_p_glcd_devices[i].x_cdev.ops = &glcd_fops;
        i32_err = cdev_add(&x_p_glcd_devices[i].x_cdev, x_dev, 1);
        if (i32_err)
        {
            printd("error %d adding cdev %d", i32_err, i);
            i32_result = -ENOSPC;
            goto fail;
        }
    }

    printd("insmod successfully\n");
    return (0);

    fail : ud_glcd_module_exit();
    return (i32_result);
}

static void __exit ud_glcd_module_exit (void)
{
    dev_t x_dev = MKDEV(major, minor);
    int i;

    if (x_p_glcd_devices)
    {
        for (i = 0; i < max_devs; i++)
        {
            cdev_del(&x_p_glcd_devices[i].x_cdev);
        }
        kfree(x_p_glcd_devices);
    }

    unregister_chrdev_region(x_dev, max_devs);

    printd("rmmod successfully\n");
}

module_init(ud_glcd_module_init);
module_exit(ud_glcd_module_exit);
