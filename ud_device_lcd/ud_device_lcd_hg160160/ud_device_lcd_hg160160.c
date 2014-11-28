/*
 * modify-2014.11.28 ultimate_drivers/ud_device_lcd/ud_device_lcd_hg160160/ud_device_lcd_hg160160.c
 * 大致构想是做一个简单的frame_buffer用以支持QT，直接使用系统内的FB驱动难度略高，主要是不能支持模块，
 * 不利于今后的维护，相当于修改了内核，故选择仿制内核FB驱动，让QT通过这个伪frame_buffer驱动液晶，
 * 该层不具备对设备的接口，只提供EXPORT_SYMBOL，接口在ud_device_lcd中
 * 适用范围：特殊(hg160160，ud_device_bus_emulated)
 */

#include <linux/fb.h>
#include "../../include/ud_device_lcd.h"
#include "../../include/ud_device_bus_emulated.h"
#include "../../include/common.h"

extern int ud_bus_export_set_data (struct bus_struct *);
extern int ud_bus_export_get_data (struct bus_struct *);

#define LCD_REG_CMD (0)
#define LCD_REG_DAT (1)
#define LCD_REG_OTH (4)

//初始化液晶
int ud_lcd_init(void);
//检测可变参数，并调整到支持的值
int ud_lcd_check_var(struct fb_var_screeninfo *var, struct fb_info *info);
//设置视频模式
int ud_lcd_set_par(struct fb_info *info);
//设置色彩寄存器
int ud_lcd_setcolreg(unsigned regno, unsigned red, unsigned green,
                unsigned blue, unsigned transp, struct fb_info *info);
//显示空白
int ud_lcd_blank(int blank, struct fb_info *info);
//显示一个实心矩形
void ud_lcd_fillrect(struct fb_info *info, const struct fb_fillrect *rect);
//区域拷贝
void ud_lcd_copyarea(struct fb_info *info, const struct fb_copyarea *region);
//显示图像
void ud_lcd_imageblit(struct fb_info *info, const struct fb_image *image);
//旋转坐标系
void ud_lcd_rotate(struct fb_info *info, int angle);

#define LCD_BACK    (0)
#define LCD_FRONT   (1)

static unsigned char u8_lcd_dram[2][160*160] = {0};

void ud_lcd_reset_backlight(int i32_rst, int i32_blon)
{
    unsigned char u8_tmp = 0;
    struct bus_struct x_bus;
    int i = 1000;

    x_bus.u32_bus_addr = LCD_REG_OTH;

    if(i32_rst)
    {
        u8_tmp |= 1<<4;
        x_bus.u32_bus_data = u8_tmp;
        ud_bus_export_set_data(&x_bus);
        u8_tmp = 0;
        x_bus.u32_bus_data = u8_tmp;
        while(i--);
    }

    if(i32_blon)
    {
        u8_tmp |= 1<<3;
        x_bus.u32_bus_data = u8_tmp;
    }
    ud_bus_export_set_data(&x_bus);
}

int ud_lcd_init(void)
{
    struct bus_struct x_bus;

    ud_lcd_reset_backlight(1,1);
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

int ud_lcd_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
    return (0);
}


EXPORT_SYMBOL(ud_lcd_check_var);
EXPORT_SYMBOL(ud_lcd_set_par);
EXPORT_SYMBOL(ud_lcd_setcolreg);
EXPORT_SYMBOL(ud_lcd_blank);
EXPORT_SYMBOL(ud_lcd_fillrect);
EXPORT_SYMBOL(ud_lcd_copyarea);
EXPORT_SYMBOL(ud_lcd_imageblit);
EXPORT_SYMBOL(ud_lcd_rotate);
