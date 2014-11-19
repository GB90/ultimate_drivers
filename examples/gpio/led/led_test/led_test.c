/*
 ============================================================================
 Name        : led_test.c
 Author      : chlachof
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "../../../../include/ud_driver_gpio.h"

int main(void)
{
    int i32_fd;
    int i32_result = EXIT_SUCCESS;
    struct gpio_struct x_gpio;

    x_gpio.x_port   = UD_GPIO_PORT_A;
    x_gpio.x_pin    = UD_GPIO_PIN_3;
    x_gpio.x_dir    = UD_GPIO_DIR_OUTPUT;
    x_gpio.x_value  = UD_GPIO_VALUE_LOW;

    i32_fd = open("/dev/ud_gpio", O_RDWR);
    if(i32_fd < 0)
    {
        printf("open gpio fail\n");
        i32_result = -1;
    }

    ioctl(i32_fd, UD_GPIO_CMD_SET_DIR, &x_gpio);
    sleep(1);
    x_gpio.x_value = UD_GPIO_VALUE_HIGH;
    ioctl(i32_fd, UD_GPIO_CMD_SET_VALUE, (unsigned long)&x_gpio);
    sleep(1);
    x_gpio.x_value = UD_GPIO_VALUE_LOW;
    ioctl(i32_fd, UD_GPIO_CMD_SET_VALUE, (unsigned long)&x_gpio);

    close(i32_fd);

	return (i32_result);
}
