/*
 * modify-2014.11.28 ultimate_drivers/ud_device_lcd/ud_device_lcd_hg160160/ud_device_lcd_hg160160.c
 * 大致构想是做一个简单的frame_buffer用以支持QT，直接使用系统内的FB驱动难度略高，主要是不能支持模块，
 * 不利于今后的维护，相当于修改了内核，故选择仿制内核FB驱动，让QT通过这个伪frame_buffer驱动液晶，
 * 该层不具备对设备的接口，只提供EXPORT_SYMBOL，接口在ud_device_lcd中
 * 适用范围：特殊(hg160160，ud_device_bus_emulated)
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
#include <linux/mutex.h>
#include <linux/mm.h>

#include <asm/uaccess.h>

#include <linux/fb.h>
#include "../../include/ud_device_lcd.h"
#include "../../include/ud_device_bus_emulated.h"
#include "../../include/common.h"

MODULE_LICENSE("Dual BSD/GPL");

//extern const unsigned long u32_ud_lcd_creaway_logo[];
extern int ud_bus_export_set_data (struct bus_struct *);
extern int ud_bus_export_get_data (struct bus_struct *);

#define LCD_REG_CMD (0)
#define LCD_REG_DAT (1)
#define LCD_REG_OTH (4)

//初始化液晶
int ud_lcd_export_init(void);
//显示空白
int ud_lcd_export_blank(void);
//刷新
void ud_lcd_export_refresh(void);

int ud_lcd_export_set_info(struct fb_info * x_info);

static int __init ud_lcd160160_module_init (void);
static void __exit ud_lcd160160_module_exit (void);


#define X_MAX       (160)
#define Y_MAX       (160)

struct lcd_dev
{
    struct mutex        x_lock;
    unsigned char *     u8_p_color;
    unsigned char *     u8_p_lcd_dram;
    unsigned char *     u8_p_lcd_dram_area;
    struct cdev         x_cdev;
};
struct lcd_dev * x_p_lcd_devices;

//主设备号
int major = UD_LCD_MAJOR;
//次设备号
int minor = 0;
//设备数量
int max_devs = UD_LCD_MAX_DEVS;

int bwb = 380;

module_param(major, int ,S_IRUGO);
module_param(bwb, int ,S_IRUGO);


void ud_lcd_reset_backlight(int i32_rst, int i32_blon)
{
    unsigned char u8_tmp = 0;
    struct bus_struct x_bus;
    int i;

    x_bus.u32_bus_addr = LCD_REG_OTH;

    if(i32_rst)
    {
        x_bus.u32_bus_data = 0;
        ud_bus_export_set_data(&x_bus);
        for(i=0;i<10000;i++);
    }

    if(i32_blon)
    {
        u8_tmp |= 1<<2;
    }

    u8_tmp |= 1<<3;
    x_bus.u32_bus_data = u8_tmp;
    ud_bus_export_set_data(&x_bus);
    for(i=0;i<10000;i++);
}

int ud_lcd_export_init(void)
{
    struct bus_struct x_bus;

    ud_lcd_reset_backlight(1,1);
    memset(x_p_lcd_devices->u8_p_lcd_dram, 0xff, Y_MAX*X_MAX/8);

    x_bus.u32_bus_addr = LCD_REG_CMD;

    x_bus.u32_bus_data = 0xe2;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xae;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x26;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x2b;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xeb;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x81;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x73;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x89;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xc4;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x84;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xde;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xc8;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x18;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xa3;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xd6;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xd1;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0x84;
    ud_bus_export_set_data(&x_bus);
    x_bus.u32_bus_data = 0xad;
    ud_bus_export_set_data(&x_bus);

    return (0);
}

int ud_lcd_export_blank(void)
{
    ud_lcd_export_init();

    return (0);
}

void ud_lcd_export_refresh(void)
{
    unsigned int u32_x;
    unsigned int u32_y;
    struct bus_struct x_bus;
    unsigned short u16_data = 0;

    for(u32_y = 0; u32_y < Y_MAX; u32_y++)
    {
        x_bus.u32_bus_addr = LCD_REG_CMD;
        x_bus.u32_bus_data = (0x60 |  (u32_y & 0x0f));
        ud_bus_export_set_data(&x_bus);
        x_bus.u32_bus_data = (0x70 | ((u32_y & 0xf0)>>4));
        ud_bus_export_set_data(&x_bus);
        x_bus.u32_bus_data = (0x05);
        ud_bus_export_set_data(&x_bus);
        x_bus.u32_bus_data = (0x12);
        ud_bus_export_set_data(&x_bus);
        for(u32_x = 0; u32_x < X_MAX; u32_x++)
        {
            if(u32_x%3 == 0)
            {
                u16_data = 0;
                x_p_lcd_devices->u8_p_color = x_p_lcd_devices->u8_p_lcd_dram + u32_y*X_MAX/8 + u32_x/8;
                if(((*x_p_lcd_devices->u8_p_color) & (1<<(7-u32_x%8))) == 0)
                {
                    u16_data |= 0xf800;
                }
            }
            if(u32_x%3 == 1)
            {
                x_p_lcd_devices->u8_p_color = x_p_lcd_devices->u8_p_lcd_dram + u32_y*X_MAX/8 + u32_x/8;
                if(((*x_p_lcd_devices->u8_p_color) & (1<<(7-u32_x%8))) == 0)
                {
                    u16_data |= 0x07e0;
                }
            }
            if(u32_x%3 == 2)
            {
                x_p_lcd_devices->u8_p_color = x_p_lcd_devices->u8_p_lcd_dram + u32_y*X_MAX/8 + u32_x/8;
                if(((*x_p_lcd_devices->u8_p_color) & (1<<(7-u32_x%8))) == 0)
                {
                    u16_data |= 0x001f;
                }
                x_bus.u32_bus_addr = LCD_REG_DAT;
                x_bus.u32_bus_data = ((u16_data & 0xff00) >> 8);
                ud_bus_export_set_data(&x_bus);
                x_bus.u32_bus_data = (u16_data & 0x00ff);
                ud_bus_export_set_data(&x_bus);
            }
        }
        x_bus.u32_bus_data = ((u16_data & 0xff00) >> 8);
        ud_bus_export_set_data(&x_bus);
        x_bus.u32_bus_data = (u16_data & 0x00ff);
        ud_bus_export_set_data(&x_bus);
    }
}

int ud_lcd_export_set_info(struct fb_info * x_info)
{
    memcpy(x_info->fix.id, "hg160160", 8);
    x_info->fix.smem_start = (unsigned long)((x_p_lcd_devices->u8_p_lcd_dram));
    x_info->fix.smem_len = Y_MAX*X_MAX/8;
    x_info->fix.type = FB_TYPE_PACKED_PIXELS;
    x_info->fix.visual = FB_VISUAL_MONO10;
    x_info->fix.accel = FB_ACCEL_NONE;
    x_info->fix.line_length = X_MAX/8;
    x_info->fix.mmio_start = (unsigned long)((x_p_lcd_devices->u8_p_lcd_dram_area));
    x_info->fix.mmio_len = x_info->fix.smem_len;

    x_info->var.xres = X_MAX;
    x_info->var.yres = Y_MAX;
    x_info->var.xres_virtual = x_info->var.xres;
    x_info->var.yres_virtual = x_info->var.yres;
    x_info->var.bits_per_pixel = 1;

    x_info->screen_size = x_info->fix.smem_len;
    x_info->screen_base = (char __iomem *)(x_info->fix.smem_start);

    return (0);
}

int ud_lcd_open (struct inode * x_p_inode, struct file * x_p_file)
{
    struct lcd_dev * x_p_devices;
    x_p_devices = container_of(x_p_inode->i_cdev, struct lcd_dev, x_cdev);
    x_p_file->private_data = x_p_devices;
    return (0);
}

int ud_lcd_release (struct inode * x_p_inode, struct file * x_p_file)
{
    return (0);
}

long ud_lcd_ioctl (struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg)
{
    struct lcd_dev * x_p_devices = (struct lcd_dev *)x_p_file->private_data;

    switch (u32_cmd)
    {
    case UD_LCD_CMD_REFRESH :
        mutex_lock(&x_p_devices->x_lock);
        ud_lcd_export_refresh();
        mutex_unlock(&x_p_devices->x_lock);
        break;
    }

    return (0);
}

struct file_operations lcd_fops =
{
    .owner = THIS_MODULE,
    .unlocked_ioctl = ud_lcd_ioctl,
    .open = ud_lcd_open,
    .release = ud_lcd_release,
};

static int __init ud_lcd160160_module_init (void)
{
    int i32_result, i32_err;
    dev_t x_dev = 0;
    int i;
    unsigned long u32_virt_addr;

    if (major)
    {
        x_dev = MKDEV(major, minor);
        i32_result = register_chrdev_region(x_dev, max_devs, "ud_lcd");
    }
    else
    {
        i32_result = alloc_chrdev_region(&x_dev, minor, max_devs, "ud_lcd");
        major = MAJOR(x_dev);
        printd("dev major is %d\n", major);
    }

    if (i32_result < 0)
    {
        printd("can't get major \n");
        return (i32_result);
    }

    x_p_lcd_devices = kmalloc(max_devs * sizeof(struct lcd_dev), GFP_KERNEL);
    if (!x_p_lcd_devices)
    {
        printd("out of memory \n");
        i32_result = -ENOMEM;
        goto fail;
    }

    memset(x_p_lcd_devices, 0, max_devs * sizeof(struct lcd_dev));

    for (i = 0; i < max_devs; i++)
    {
        mutex_init(&x_p_lcd_devices[i].x_lock);
        printd("ready\n");
        
        x_p_lcd_devices[i].u8_p_lcd_dram = kmalloc(Y_MAX*X_MAX/8, GFP_KERNEL);
        printd("mmap = %p\n", x_p_lcd_devices[i].u8_p_lcd_dram);
        x_p_lcd_devices[i].u8_p_lcd_dram_area = (char *)(((unsigned long)x_p_lcd_devices[i].u8_p_lcd_dram + PAGE_SIZE -1) & PAGE_MASK);
        
        for (u32_virt_addr = (unsigned long)x_p_lcd_devices[i].u8_p_lcd_dram_area; 
             u32_virt_addr < (unsigned long)x_p_lcd_devices[i].u8_p_lcd_dram_area + Y_MAX*X_MAX/8;
             u32_virt_addr += PAGE_SIZE)
        {
		        /* reserve all pages to make them remapable */
		        //将页配置为保留，防止映射到用户空间的页面被swap out出去；
		        SetPageReserved(virt_to_page(u32_virt_addr));
        }
        
        ud_lcd_export_init();
        ud_lcd_export_init();

        //memcpy(x_p_lcd_devices[i].u8_p_lcd_dram, u32_ud_lcd_creaway_logo, Y_MAX*X_MAX*4);
        //ud_lcd_export_refresh();

        x_dev = MKDEV(major, minor + i);
        cdev_init(&x_p_lcd_devices[i].x_cdev, &lcd_fops);
        x_p_lcd_devices[i].x_cdev.owner = THIS_MODULE;
        x_p_lcd_devices[i].x_cdev.ops = &lcd_fops;
        i32_err = cdev_add(&x_p_lcd_devices[i].x_cdev, x_dev, 1);
        if (i32_err)
        {
            printd("error %d adding cdev %d", i32_err, i);
            i32_result = -ENOSPC;
            goto fail;
        }
    }

    printd("insmod successfully\n");
    return (0);

    fail : ud_lcd160160_module_exit();
    return (i32_result);

}

static void __exit ud_lcd160160_module_exit (void)
{
    dev_t x_dev = MKDEV(major, minor);
    int i;
    unsigned long u32_virt_addr;

    if (x_p_lcd_devices)
    {
        for (i = 0; i < max_devs; i++)
        {
        	  if (x_p_lcd_devices[i].u8_p_lcd_dram)
            {
            	  for (u32_virt_addr = (unsigned long)x_p_lcd_devices[i].u8_p_lcd_dram_area; 
                     u32_virt_addr < (unsigned long)x_p_lcd_devices[i].u8_p_lcd_dram_area + Y_MAX*X_MAX/8;
                     u32_virt_addr += PAGE_SIZE)
				        {
						        /* clear all pages*/
						        ClearPageReserved(virt_to_page(u32_virt_addr));
				        }
                kfree(x_p_lcd_devices[i].u8_p_lcd_dram);
            }
            cdev_del(&x_p_lcd_devices[i].x_cdev);
        }
        kfree(x_p_lcd_devices);
    }
    
    unregister_chrdev_region(x_dev, max_devs);
    printd("rmmod successfully\n");
}

EXPORT_SYMBOL(ud_lcd_export_init);
EXPORT_SYMBOL(ud_lcd_export_blank);
EXPORT_SYMBOL(ud_lcd_export_refresh);
EXPORT_SYMBOL(ud_lcd_export_set_info);

module_init(ud_lcd160160_module_init);
module_exit(ud_lcd160160_module_exit);
