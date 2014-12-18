#ifndef __UD_DEVICE_GLCD__
#define __UD_DEVICE_GLCD__

#include <linux/ioctl.h>

#ifndef UD_GLCD_MAJOR
#define UD_GLCD_MAJOR       (0)
#endif

#ifndef UD_LCD_MAJOR
#define UD_LCD_MAJOR        (0)
#endif

#ifndef UD_GLCD_MAX_DEVS
#define UD_GLCD_MAX_DEVS    (1)
#endif

#ifndef UD_LCD_MAX_DEVS
#define UD_LCD_MAX_DEVS     (1)
#endif

#ifndef UD_GLCD_PAGE_SIZE
#define UD_GLCD_PAGE_SIZE   (8*1024)
#endif

#define UD_GLCD_IOC_MAGIC  'l'

#define UD_LCD_IOC_MAGIC   'd'
#define UD_LCD_CMD_REFRESH     _IO(UD_LCD_IOC_MAGIC, 0)


#endif
