#ifndef __UD_DEVICE_BUS_EMULATED__
#define __UD_DEVICE_BUS_EMULATED__

#include <linux/ioctl.h>
#include "ud_driver_gpio.h"

#ifndef UD_BUS_MAJOR
#define UD_BUS_MAJOR       (0)
#endif

#ifndef UD_BUS_MAX_DEVS
#define UD_BUS_MAX_DEVS    (1)
#endif

#define UD_BUS_IOC_MAGIC  'b'
//modify-2014.11.21 优化了ioctl操作，现在不需要单独设置地址
//#define UD_BUS_CMD_SET_ADDR  _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_BUS_CMD_SET_DATA  _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_BUS_CMD_GET_DATA  _IO(UD_GPIO_IOC_MAGIC, 1)
#define UD_BUS_CMD_INIT      _IO(UD_GPIO_IOC_MAGIC, 2)

#ifndef UD_BUS_ADDR_BIT
#define UD_BUS_ADDR_BIT    (3)
#endif

#ifndef UD_BUS_DATA_BIT
#define UD_BUS_DATA_BIT    (8)
#endif

struct bus_io
{
    //模拟总线固有延时
    unsigned int        u32_bus_io_delay;
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

struct bus_struct
{
    struct bus_io       x_io;
    //地址
    unsigned long       u32_bus_addr;
    //数据
    unsigned long       u32_bus_data;
};

#endif
