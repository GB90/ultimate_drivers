#ifndef __UD_DRIVER_GPIO__
#define __UD_DRIVER_GPIO__

#include <linux/ioctl.h>

#ifndef UD_GPIO_MAJOR
#define UD_GPIO_MAJOR       (0)
#endif

#ifndef UD_GPIO_MAX_DEVS
#define UD_GPIO_MAX_DEVS    (1)
#endif

#define UD_GPIO_IOC_MAGIC  'g'
#define UD_GPIO_CMD_SET_DIR     _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_GPIO_CMD_SET_VALUE   _IO(UD_GPIO_IOC_MAGIC, 1)
#define UD_GPIO_CMD_GET_VALUE   _IO(UD_GPIO_IOC_MAGIC, 2)
#define UD_GPIO_CMD_TRIGGER     _IO(UD_GPIO_IOC_MAGIC, 3)

#define UD_PIN_BASE 32

enum gpio_enum_pin
{
    UD_PIN_PA0 = (UD_PIN_BASE + 0x00 + 0),
    UD_PIN_PA1 = (UD_PIN_BASE + 0x00 + 1),
    UD_PIN_PA2 = (UD_PIN_BASE + 0x00 + 2),
    UD_PIN_PA3 = (UD_PIN_BASE + 0x00 + 3),
    UD_PIN_PA4 = (UD_PIN_BASE + 0x00 + 4),
    UD_PIN_PA5 = (UD_PIN_BASE + 0x00 + 5),
    UD_PIN_PA6 = (UD_PIN_BASE + 0x00 + 6),
    UD_PIN_PA7 = (UD_PIN_BASE + 0x00 + 7),
    UD_PIN_PA8 = (UD_PIN_BASE + 0x00 + 8),
    UD_PIN_PA9 = (UD_PIN_BASE + 0x00 + 9),
    UD_PIN_PA10 = (UD_PIN_BASE + 0x00 + 10),
    UD_PIN_PA11 = (UD_PIN_BASE + 0x00 + 11),
    UD_PIN_PA12 = (UD_PIN_BASE + 0x00 + 12),
    UD_PIN_PA13 = (UD_PIN_BASE + 0x00 + 13),
    UD_PIN_PA14 = (UD_PIN_BASE + 0x00 + 14),
    UD_PIN_PA15 = (UD_PIN_BASE + 0x00 + 15),
    UD_PIN_PA16 = (UD_PIN_BASE + 0x00 + 16),
    UD_PIN_PA17 = (UD_PIN_BASE + 0x00 + 17),
    UD_PIN_PA18 = (UD_PIN_BASE + 0x00 + 18),
    UD_PIN_PA19 = (UD_PIN_BASE + 0x00 + 19),
    UD_PIN_PA20 = (UD_PIN_BASE + 0x00 + 20),
    UD_PIN_PA21 = (UD_PIN_BASE + 0x00 + 21),
    UD_PIN_PA22 = (UD_PIN_BASE + 0x00 + 22),
    UD_PIN_PA23 = (UD_PIN_BASE + 0x00 + 23),
    UD_PIN_PA24 = (UD_PIN_BASE + 0x00 + 24),
    UD_PIN_PA25 = (UD_PIN_BASE + 0x00 + 25),
    UD_PIN_PA26 = (UD_PIN_BASE + 0x00 + 26),
    UD_PIN_PA27 = (UD_PIN_BASE + 0x00 + 27),
    UD_PIN_PA28 = (UD_PIN_BASE + 0x00 + 28),
    UD_PIN_PA29 = (UD_PIN_BASE + 0x00 + 29),
    UD_PIN_PA30 = (UD_PIN_BASE + 0x00 + 30),
    UD_PIN_PA31 = (UD_PIN_BASE + 0x00 + 31),

    UD_PIN_PB0 = (UD_PIN_BASE + 0x20 + 0),
    UD_PIN_PB1 = (UD_PIN_BASE + 0x20 + 1),
    UD_PIN_PB2 = (UD_PIN_BASE + 0x20 + 2),
    UD_PIN_PB3 = (UD_PIN_BASE + 0x20 + 3),
    UD_PIN_PB4 = (UD_PIN_BASE + 0x20 + 4),
    UD_PIN_PB5 = (UD_PIN_BASE + 0x20 + 5),
    UD_PIN_PB6 = (UD_PIN_BASE + 0x20 + 6),
    UD_PIN_PB7 = (UD_PIN_BASE + 0x20 + 7),
    UD_PIN_PB8 = (UD_PIN_BASE + 0x20 + 8),
    UD_PIN_PB9 = (UD_PIN_BASE + 0x20 + 9),
    UD_PIN_PB10 = (UD_PIN_BASE + 0x20 + 10),
    UD_PIN_PB11 = (UD_PIN_BASE + 0x20 + 11),
    UD_PIN_PB12 = (UD_PIN_BASE + 0x20 + 12),
    UD_PIN_PB13 = (UD_PIN_BASE + 0x20 + 13),
    UD_PIN_PB14 = (UD_PIN_BASE + 0x20 + 14),
    UD_PIN_PB15 = (UD_PIN_BASE + 0x20 + 15),
    UD_PIN_PB16 = (UD_PIN_BASE + 0x20 + 16),
    UD_PIN_PB17 = (UD_PIN_BASE + 0x20 + 17),
    UD_PIN_PB18 = (UD_PIN_BASE + 0x20 + 18),
    UD_PIN_PB19 = (UD_PIN_BASE + 0x20 + 19),
    UD_PIN_PB20 = (UD_PIN_BASE + 0x20 + 20),
    UD_PIN_PB21 = (UD_PIN_BASE + 0x20 + 21),
    UD_PIN_PB22 = (UD_PIN_BASE + 0x20 + 22),
    UD_PIN_PB23 = (UD_PIN_BASE + 0x20 + 23),
    UD_PIN_PB24 = (UD_PIN_BASE + 0x20 + 24),
    UD_PIN_PB25 = (UD_PIN_BASE + 0x20 + 25),
    UD_PIN_PB26 = (UD_PIN_BASE + 0x20 + 26),
    UD_PIN_PB27 = (UD_PIN_BASE + 0x20 + 27),
    UD_PIN_PB28 = (UD_PIN_BASE + 0x20 + 28),
    UD_PIN_PB29 = (UD_PIN_BASE + 0x20 + 29),
    UD_PIN_PB30 = (UD_PIN_BASE + 0x20 + 30),
    UD_PIN_PB31 = (UD_PIN_BASE + 0x20 + 31),

    UD_PIN_PC0 = (UD_PIN_BASE + 0x40 + 0),
    UD_PIN_PC1 = (UD_PIN_BASE + 0x40 + 1),
    UD_PIN_PC2 = (UD_PIN_BASE + 0x40 + 2),
    UD_PIN_PC3 = (UD_PIN_BASE + 0x40 + 3),
    UD_PIN_PC4 = (UD_PIN_BASE + 0x40 + 4),
    UD_PIN_PC5 = (UD_PIN_BASE + 0x40 + 5),
    UD_PIN_PC6 = (UD_PIN_BASE + 0x40 + 6),
    UD_PIN_PC7 = (UD_PIN_BASE + 0x40 + 7),
    UD_PIN_PC8 = (UD_PIN_BASE + 0x40 + 8),
    UD_PIN_PC9 = (UD_PIN_BASE + 0x40 + 9),
    UD_PIN_PC10 = (UD_PIN_BASE + 0x40 + 10),
    UD_PIN_PC11 = (UD_PIN_BASE + 0x40 + 11),
    UD_PIN_PC12 = (UD_PIN_BASE + 0x40 + 12),
    UD_PIN_PC13 = (UD_PIN_BASE + 0x40 + 13),
    UD_PIN_PC14 = (UD_PIN_BASE + 0x40 + 14),
    UD_PIN_PC15 = (UD_PIN_BASE + 0x40 + 15),
    UD_PIN_PC16 = (UD_PIN_BASE + 0x40 + 16),
    UD_PIN_PC17 = (UD_PIN_BASE + 0x40 + 17),
    UD_PIN_PC18 = (UD_PIN_BASE + 0x40 + 18),
    UD_PIN_PC19 = (UD_PIN_BASE + 0x40 + 19),
    UD_PIN_PC20 = (UD_PIN_BASE + 0x40 + 20),
    UD_PIN_PC21 = (UD_PIN_BASE + 0x40 + 21),
    UD_PIN_PC22 = (UD_PIN_BASE + 0x40 + 22),
    UD_PIN_PC23 = (UD_PIN_BASE + 0x40 + 23),
    UD_PIN_PC24 = (UD_PIN_BASE + 0x40 + 24),
    UD_PIN_PC25 = (UD_PIN_BASE + 0x40 + 25),
    UD_PIN_PC26 = (UD_PIN_BASE + 0x40 + 26),
    UD_PIN_PC27 = (UD_PIN_BASE + 0x40 + 27),
    UD_PIN_PC28 = (UD_PIN_BASE + 0x40 + 28),
    UD_PIN_PC29 = (UD_PIN_BASE + 0x40 + 29),
    UD_PIN_PC30 = (UD_PIN_BASE + 0x40 + 30),
    UD_PIN_PC31 = (UD_PIN_BASE + 0x40 + 31),

    UD_PIN_PD0 = (UD_PIN_BASE + 0x60 + 0),
    UD_PIN_PD1 = (UD_PIN_BASE + 0x60 + 1),
    UD_PIN_PD2 = (UD_PIN_BASE + 0x60 + 2),
    UD_PIN_PD3 = (UD_PIN_BASE + 0x60 + 3),
    UD_PIN_PD4 = (UD_PIN_BASE + 0x60 + 4),
    UD_PIN_PD5 = (UD_PIN_BASE + 0x60 + 5),
    UD_PIN_PD6 = (UD_PIN_BASE + 0x60 + 6),
    UD_PIN_PD7 = (UD_PIN_BASE + 0x60 + 7),
    UD_PIN_PD8 = (UD_PIN_BASE + 0x60 + 8),
    UD_PIN_PD9 = (UD_PIN_BASE + 0x60 + 9),
    UD_PIN_PD10 = (UD_PIN_BASE + 0x60 + 10),
    UD_PIN_PD11 = (UD_PIN_BASE + 0x60 + 11),
    UD_PIN_PD12 = (UD_PIN_BASE + 0x60 + 12),
    UD_PIN_PD13 = (UD_PIN_BASE + 0x60 + 13),
    UD_PIN_PD14 = (UD_PIN_BASE + 0x60 + 14),
    UD_PIN_PD15 = (UD_PIN_BASE + 0x60 + 15),
    UD_PIN_PD16 = (UD_PIN_BASE + 0x60 + 16),
    UD_PIN_PD17 = (UD_PIN_BASE + 0x60 + 17),
    UD_PIN_PD18 = (UD_PIN_BASE + 0x60 + 18),
    UD_PIN_PD19 = (UD_PIN_BASE + 0x60 + 19),
    UD_PIN_PD20 = (UD_PIN_BASE + 0x60 + 20),
    UD_PIN_PD21 = (UD_PIN_BASE + 0x60 + 21),
    UD_PIN_PD22 = (UD_PIN_BASE + 0x60 + 22),
    UD_PIN_PD23 = (UD_PIN_BASE + 0x60 + 23),
    UD_PIN_PD24 = (UD_PIN_BASE + 0x60 + 24),
    UD_PIN_PD25 = (UD_PIN_BASE + 0x60 + 25),
    UD_PIN_PD26 = (UD_PIN_BASE + 0x60 + 26),
    UD_PIN_PD27 = (UD_PIN_BASE + 0x60 + 27),
    UD_PIN_PD28 = (UD_PIN_BASE + 0x60 + 28),
    UD_PIN_PD29 = (UD_PIN_BASE + 0x60 + 29),
    UD_PIN_PD30 = (UD_PIN_BASE + 0x60 + 30),
    UD_PIN_PD31 = (UD_PIN_BASE + 0x60 + 31),

    UD_PIN_PE0 = (UD_PIN_BASE + 0x80 + 0),
    UD_PIN_PE1 = (UD_PIN_BASE + 0x80 + 1),
    UD_PIN_PE2 = (UD_PIN_BASE + 0x80 + 2),
    UD_PIN_PE3 = (UD_PIN_BASE + 0x80 + 3),
    UD_PIN_PE4 = (UD_PIN_BASE + 0x80 + 4),
    UD_PIN_PE5 = (UD_PIN_BASE + 0x80 + 5),
    UD_PIN_PE6 = (UD_PIN_BASE + 0x80 + 6),
    UD_PIN_PE7 = (UD_PIN_BASE + 0x80 + 7),
    UD_PIN_PE8 = (UD_PIN_BASE + 0x80 + 8),
    UD_PIN_PE9 = (UD_PIN_BASE + 0x80 + 9),
    UD_PIN_PE10 = (UD_PIN_BASE + 0x80 + 10),
    UD_PIN_PE11 = (UD_PIN_BASE + 0x80 + 11),
    UD_PIN_PE12 = (UD_PIN_BASE + 0x80 + 12),
    UD_PIN_PE13 = (UD_PIN_BASE + 0x80 + 13),
    UD_PIN_PE14 = (UD_PIN_BASE + 0x80 + 14),
    UD_PIN_PE15 = (UD_PIN_BASE + 0x80 + 15),
    UD_PIN_PE16 = (UD_PIN_BASE + 0x80 + 16),
    UD_PIN_PE17 = (UD_PIN_BASE + 0x80 + 17),
    UD_PIN_PE18 = (UD_PIN_BASE + 0x80 + 18),
    UD_PIN_PE19 = (UD_PIN_BASE + 0x80 + 19),
    UD_PIN_PE20 = (UD_PIN_BASE + 0x80 + 20),
    UD_PIN_PE21 = (UD_PIN_BASE + 0x80 + 21),
    UD_PIN_PE22 = (UD_PIN_BASE + 0x80 + 22),
    UD_PIN_PE23 = (UD_PIN_BASE + 0x80 + 23),
    UD_PIN_PE24 = (UD_PIN_BASE + 0x80 + 24),
    UD_PIN_PE25 = (UD_PIN_BASE + 0x80 + 25),
    UD_PIN_PE26 = (UD_PIN_BASE + 0x80 + 26),
    UD_PIN_PE27 = (UD_PIN_BASE + 0x80 + 27),
    UD_PIN_PE28 = (UD_PIN_BASE + 0x80 + 28),
    UD_PIN_PE29 = (UD_PIN_BASE + 0x80 + 29),
    UD_PIN_PE30 = (UD_PIN_BASE + 0x80 + 30),
    UD_PIN_PE31 = (UD_PIN_BASE + 0x80 + 31),
};
#define is_not_gpio_pin(pin) ( (pin) < UD_PIN_PA0 || (pin) > UD_PIN_PE31 )

enum gpio_enum_dir
{
    UD_GPIO_DIR_INPUT  = 0,
    UD_GPIO_DIR_OUTPUT = 1,
};
#define is_not_gpio_dir(dir) ( (dir) != UD_GPIO_DIR_INPUT && (dir) != UD_GPIO_DIR_OUTPUT )

enum gpio_enum_pullup
{
    UD_GPIO_PULLUP_OFF = 0,
    UD_GPIO_PULLUP_ON  = 1,
};
#define is_not_gpio_pullup(pullup) ( (pullup) != UD_GPIO_PULLUP_OFF && (pullup) != UD_GPIO_PULLUP_ON )

enum gpio_enum_value
{
    UD_GPIO_VALUE_LOW  = 0,
    UD_GPIO_VALUE_HIGH = 1,
};
#define is_not_gpio_value(value) ( (value) != UD_GPIO_VALUE_LOW && (value) != UD_GPIO_VALUE_HIGH )

struct gpio_struct
{
    //引脚port(ABCDE) pin(0~31)
    enum gpio_enum_pin      x_pin;
    //引脚方向(in,out)
    enum gpio_enum_dir      x_dir;
    //引脚是否上拉，输入时使用(off,on)
    enum gpio_enum_pullup   x_pullup;
    //引脚输入输出值(low,high)
    enum gpio_enum_value    x_value;
};

#endif
