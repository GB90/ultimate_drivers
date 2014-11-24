/*
 ============================================================================
 Name        : led.c
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

#include <ud_device_bus_emulated.h>

int main(void)
{
    int i32_fd;
    int i32_result = EXIT_SUCCESS;
    struct bus_struct x_bus;

    i32_fd = open("/dev/ud_bus", O_RDWR);
    if(i32_fd < 0)
    {
        printf("open bus fail\n");
        i32_result = -1;
    }

    x_bus.u32_bus_addr = 0x02;
    x_bus.u32_bus_data = 0xf0;
    ioctl(i32_fd, UD_BUS_CMD_SET_DATA, &x_bus);
    printf("0xf0\n");
    sleep(15);

    x_bus.u32_bus_addr = 0x02;
    x_bus.u32_bus_data = 0x0f;
    ioctl(i32_fd, UD_BUS_CMD_SET_DATA, &x_bus);
    printf("0x0f\n");
    sleep(15);

    close(i32_fd);

	return (i32_result);
}
