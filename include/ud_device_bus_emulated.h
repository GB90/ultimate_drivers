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
//modify-2014.11.21 优化了ioctl操作，现在不需要单独设置地址
//#define UD_BUS_CMD_SET_ADDR  _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_BUS_CMD_SET_DATA  _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_BUS_CMD_GET_DATA  _IO(UD_GPIO_IOC_MAGIC, 1)

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

#endif
