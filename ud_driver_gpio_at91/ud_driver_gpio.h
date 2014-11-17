#ifndef __UD_DRIVER_GPIO__
#define __UD_DRIVER_GPIO__

#include <linux/ioctl.h>
#include <linux/spinlock.h>

#ifndef __UD_PRINT__
#define __UD_PRINT__
#define UD_DEBUG
#ifdef UD_DEBUG
#define printd(arg,x...)    printk(KERN_ALERT"UD debug:"arg,##x)
#else
#define printd(arg,x...)
#endif
#endif

#ifndef UD_GPIO_MAJOR
#define UD_GPIO_MAJOR       (0)
#endif

#ifndef UD_GPIO_MAX_DEVS
#define UD_GPIO_MAX_DEVS    (1)
#endif

#define UD_GPIO_IOC_MAGIC  'g'
#define UD_GPIO_CMD_SET_DIR    _IO(UD_GPIO_IOC_MAGIC, 0)
#define UD_GPIO_CMD_SET_VALUE  _IO(UD_GPIO_IOC_MAGIC, 1)
#define UD_GPIO_CMD_GET_VALUE  _IO(UD_GPIO_IOC_MAGIC, 2)

enum gpio_enum_port
{
    UD_GPIO_PORT_A = 0,
    UD_GPIO_PORT_B = 1,
    UD_GPIO_PORT_C = 2,
    UD_GPIO_PORT_D = 3,
    UD_GPIO_PORT_E = 4,
};

enum gpio_enum_pin
{
    UD_GPIO_PIN_0  = 0,
    UD_GPIO_PIN_1  = 1,
    UD_GPIO_PIN_2  = 2,
    UD_GPIO_PIN_3  = 3,
    UD_GPIO_PIN_4  = 4,
    UD_GPIO_PIN_5  = 5,
    UD_GPIO_PIN_6  = 6,
    UD_GPIO_PIN_7  = 7,
    UD_GPIO_PIN_8  = 8,
    UD_GPIO_PIN_9  = 9,
    UD_GPIO_PIN_10 = 10,
    UD_GPIO_PIN_11 = 11,
    UD_GPIO_PIN_12 = 12,
    UD_GPIO_PIN_13 = 13,
    UD_GPIO_PIN_14 = 14,
    UD_GPIO_PIN_15 = 15,
    UD_GPIO_PIN_16 = 16,
    UD_GPIO_PIN_17 = 17,
    UD_GPIO_PIN_18 = 18,
    UD_GPIO_PIN_19 = 19,
    UD_GPIO_PIN_20 = 20,
    UD_GPIO_PIN_21 = 21,
    UD_GPIO_PIN_22 = 22,
    UD_GPIO_PIN_23 = 23,
    UD_GPIO_PIN_24 = 24,
    UD_GPIO_PIN_25 = 25,
    UD_GPIO_PIN_26 = 26,
    UD_GPIO_PIN_27 = 27,
    UD_GPIO_PIN_28 = 28,
    UD_GPIO_PIN_29 = 29,
    UD_GPIO_PIN_30 = 30,
    UD_GPIO_PIN_31 = 31,
};

enum gpio_enum_dir
{
    UD_GPIO_DIR_INPUT  = 0,
    UD_GPIO_DIR_OUTPUT = 1,
};

enum gpio_enum_pullup
{
    UD_GPIO_PULLUP_OFF = 0,
    UD_GPIO_PULLUP_ON  = 1,
};

enum gpio_enum_value
{
    UD_GPIO_VALUE_LOW  = 0,
    UD_GPIO_VALUE_HIGH = 1,
};

struct gpio_struct
{
    enum gpio_enum_port     x_port;
    enum gpio_enum_pin      x_pin;
    enum gpio_enum_dir      x_dir;
    enum gpio_enum_pullup   x_pullup;
    enum gpio_enum_value    x_value;
};

struct gpio_dev
{
    spinlock_t x_spinlock;
    struct cdev x_cdev;
};

int ud_gpio_open(struct inode * x_p_inode, struct file * x_p_file);
int ud_gpio_release(struct inode * x_p_inode, struct file * x_p_file);
ssize_t ud_gpio_read(struct file * x_p_file, char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);
ssize_t ud_gpio_write(struct file * x_p_file, const char __user * i8_p_buf, size_t x_count, loff_t * x_p_pos);
long ud_gpio_ioctl(struct file * x_p_file, unsigned int u32_cmd, unsigned long u32_arg);

#endif
