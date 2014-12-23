#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <linux/seq_file.h>
#include <linux/spinlock.h>
#include <linux/compat.h>
#include <linux/types.h>
#include <linux/major.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/mman.h>
#include <linux/vt.h>
#include <linux/console.h>
#include <linux/kmod.h>
#include <linux/device.h>
#include <linux/efi.h>
#include <linux/fb.h>

#include <asm/fb.h>

#include "../include/ud_device_lcd.h"
#include "../include/common.h"

struct glcd_dev
{
    //fb_info已包含多重锁结构
    struct fb_info  x_info;
    //cdev
    struct cdev x_cdev;
};

//主设备号
int major = UD_LCD_MAJOR;
//次设备号
int minor = 0;
//设备数量
int max_devs = UD_LCD_MAX_DEVS;

module_param(major, int ,S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");

extern int ud_lcd_export_init(void);
extern int ud_lcd_export_blank(void);
extern void ud_lcd_export_refresh(void);
extern int ud_lcd_export_set_info(struct fb_info *);

struct glcd_dev * x_p_glcd_devices;

static void __exit ud_glcd_module_exit (void);
static int __init ud_glcd_module_init (void);


int ud_glcd_open (struct inode * x_p_inode, struct file * x_p_file)
{
    struct glcd_dev * x_p_devices;
    x_p_devices = container_of(x_p_inode->i_cdev, struct glcd_dev, x_cdev);
    x_p_file->private_data = x_p_devices;

    printd("open glcd\n");
    return (0);
}

int ud_glcd_release (struct inode * x_p_inode, struct file * x_p_file)
{
    return (0);
}

ssize_t ud_glcd_read (struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    struct glcd_dev * x_p_devices = (struct glcd_dev *)x_p_file->private_data;
    unsigned long u32_total_size = 0;
    unsigned long u32_pos = *x_p_pos;
    char __iomem * i8_p_src;
    char * i8_p_dest, * i8_p_buffer;
    int i32_err = 0, i32_now_count = 0, i32_total_cnt = 0;

    printd("read glcd\n");

    u32_total_size = x_p_devices->x_info.screen_size;

    if(u32_pos > u32_total_size)
    {
        return (0);
    }
    if(x_count > u32_total_size)
    {
        x_count = u32_total_size;
    }
    if(x_count + u32_pos > u32_total_size)
    {
        x_count = u32_total_size - u32_pos;
    }

    i8_p_buffer = kmalloc((x_count > UD_GLCD_PAGE_SIZE) ? UD_GLCD_PAGE_SIZE : x_count, GFP_KERNEL);
    if(!i8_p_buffer)
    {
        return (-ENOMEM);
    }

    i8_p_src = (char __iomem * )(x_p_devices->x_info.screen_base + u32_pos);

    while(x_count)
    {
        i32_now_count = (x_count > UD_GLCD_PAGE_SIZE) ? UD_GLCD_PAGE_SIZE : x_count;
        i8_p_dest = i8_p_buffer;

        memcpy(i8_p_dest, i8_p_src, i32_now_count);

        i8_p_dest += i32_now_count;
        i8_p_src += i32_now_count;

        if(copy_to_user(i8_p_buf, i8_p_buffer, i32_now_count))
        {
            i32_err = -EFAULT;
            break;
        }

        *x_p_pos += i32_now_count;
        i8_p_buf += i32_now_count;
        i32_total_cnt += i32_now_count;
        x_count -= i32_now_count;
    }
    kfree(i8_p_buffer);

    return ((i32_err) ?  i32_err : i32_total_cnt);
}

ssize_t ud_glcd_write (struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos)
{
    struct glcd_dev * x_p_devices = (struct glcd_dev *)x_p_file->private_data;
    unsigned long u32_total_size = 0;
    unsigned long u32_pos = *x_p_pos;
    char __iomem * i8_p_dest;
    char * i8_p_src, * i8_p_buffer;
    int i32_err = 0, i32_now_count = 0, i32_total_cnt = 0;

    printd("write glcd\n");

    u32_total_size = x_p_devices->x_info.screen_size;

    if(u32_pos > u32_total_size)
    {
        return (-EFBIG);
    }
    if(x_count > u32_total_size)
    {
        i32_err = -EFBIG;
        x_count = u32_total_size;
    }
    if(x_count + u32_pos > u32_total_size)
    {
        if(!i32_err)
        {
            i32_err = -ENOSPC;
        }
        x_count = u32_total_size - u32_pos;
    }

    i8_p_buffer = kmalloc((x_count > UD_GLCD_PAGE_SIZE) ? UD_GLCD_PAGE_SIZE : x_count, GFP_KERNEL);
    if(!i8_p_buffer)
    {
        return (-ENOMEM);
    }

    i8_p_dest = (char __iomem * )(x_p_devices->x_info.screen_base + u32_pos);

    while(x_count)
    {
        i32_now_count = (x_count > UD_GLCD_PAGE_SIZE) ? UD_GLCD_PAGE_SIZE : x_count;
        i8_p_src = i8_p_buffer;

        if(copy_from_user(i8_p_src, i8_p_buf, i32_now_count))
        {
            i32_err = -EFAULT;
            break;
        }

        memcpy(i8_p_dest, i8_p_src, i32_now_count);

        i8_p_dest += i32_now_count;
        i8_p_src += i32_now_count;
        *x_p_pos += i32_now_count;
        i8_p_buf += i32_now_count;
        i32_total_cnt += i32_now_count;
        x_count -= i32_now_count;
    }
    kfree(i8_p_buffer);

    return ((i32_total_cnt) ? i32_total_cnt : i32_err);
}


long ud_glcd_ioctl (struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg)
{
    struct glcd_dev * x_p_devices = (struct glcd_dev *)x_p_file->private_data;
    long i32_result = 0;
    struct fb_var_screeninfo x_var;
    struct fb_fix_screeninfo x_fix;
    void __user * v_p_arg = (void __user *)u32_arg;

    printd("ok cmd : 0x%x\n", u32_cmd);

    switch (u32_cmd)
    {
    case FBIOGET_VSCREENINFO:
    case FBIOPUT_VSCREENINFO:
        mutex_lock(&x_p_devices->x_info.lock);
        x_var = x_p_devices->x_info.var;
        mutex_unlock(&x_p_devices->x_info.lock);
        i32_result = copy_to_user(v_p_arg, &x_var, sizeof(x_var)) ? -EFAULT : 0;
        break;
    case FBIOGET_FSCREENINFO:
        mutex_lock(&x_p_devices->x_info.lock);
        x_fix = x_p_devices->x_info.fix;
        mutex_unlock(&x_p_devices->x_info.lock);
        i32_result = copy_to_user(v_p_arg, &x_fix, sizeof(x_fix)) ? -EFAULT : 0;
        break;
    case FBIOBLANK:
        mutex_lock(&x_p_devices->x_info.lock);
        ud_lcd_export_blank();
        mutex_unlock(&x_p_devices->x_info.lock);
        break;
    default :
        printd("cmd : 0x%x\n", u32_cmd);
        i32_result = -ENODEV;
    }

    return (i32_result);
}

static int ud_glcd_mmap(struct file * x_p_file, struct vm_area_struct * x_p_vma)
{
    struct glcd_dev * x_p_devices = (struct glcd_dev *)x_p_file->private_data;
    unsigned long u32_off;
    unsigned long u32_start;
    unsigned long u32_len;


    if (!x_p_devices->x_info)
    {
        return -ENODEV;
    }
    if (x_p_vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
    {
        return -EINVAL;
    }
    u32_off = x_p_vma->vm_pgoff << PAGE_SHIFT;

    mutex_lock(&x_p_devices->x_info.mm_lock);

    /* frame buffer memory */
    u32_start = x_p_devices->x_info.fix.smem_start;
    u32_len = PAGE_ALIGN((u32_start & ~PAGE_MASK) + x_p_devices->x_info.fix.smem_len);
    if (u32_off >= u32_len) {
        /* memory mapped io */
        u32_off -= u32_len;
        if (x_p_devices->x_info.var.accel_flags) {
            mutex_unlock(&x_p_devices->x_info.mm_lock);
            return -EINVAL;
        }
        u32_start = x_p_devices->x_info.fix.mmio_start;
        u32_len = PAGE_ALIGN((u32_start & ~PAGE_MASK) + x_p_devices->x_info.fix.mmio_len);
    }
    mutex_unlock(&x_p_devices->x_info.mm_lock);
    u32_start &= PAGE_MASK;
    if ((x_p_vma->vm_end - x_p_vma->vm_start + u32_off) > u32_len)
        return -EINVAL;
    u32_off += u32_start;
    x_p_vma->vm_pgoff = u32_off >> PAGE_SHIFT;
    /* This is an IO map - tell maydump to skip this VMA */
    x_p_vma->vm_flags |= VM_IO | VM_RESERVED;
    x_p_vma->vm_page_prot = vm_get_page_prot(x_p_vma->vm_flags);
    fb_pgprotect(x_p_file, x_p_vma, u32_off);
    if (io_remap_pfn_range(x_p_vma, x_p_vma->vm_start, u32_off >> PAGE_SHIFT,
                 x_p_vma->vm_end - x_p_vma->vm_start, x_p_vma->vm_page_prot))
        return -EAGAIN;

    printfd("io: 0x%x", x_p_devices->x_info.fix.mmio_start);

    return 0;
}

struct file_operations glcd_fops =
{
    .owner = THIS_MODULE,
    .read = ud_glcd_read,
    .write = ud_glcd_write,
    .unlocked_ioctl = ud_glcd_ioctl,
    .open = ud_glcd_open,
    .release = ud_glcd_release,
    .mmap = ud_glcd_mmap,
    .llseek = default_llseek,
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
        mutex_init(&x_p_glcd_devices[i].x_info.lock);
        mutex_init(&x_p_glcd_devices[i].x_info.mm_lock);

        ud_lcd_export_set_info(&x_p_glcd_devices[i].x_info);

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
