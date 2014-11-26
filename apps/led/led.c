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
    int i32_fd, i, j;
    int i32_result = EXIT_SUCCESS;
    struct bus_struct x_bus = {
        .x_io.u32_bus_io_delay = 2,
        .x_io.x_bus_io_cs = UD_PIN_PA29,
        .x_io.x_bus_io_oe = UD_PIN_PA31,
        .x_io.x_bus_io_we = UD_PIN_PA25,
        .x_io.x_p_bus_io_addr[0] = UD_PIN_PA28,
        .x_io.x_p_bus_io_addr[1] = UD_PIN_PA26,
        .x_io.x_p_bus_io_addr[2] = UD_PIN_PA22,
        .x_io.x_p_bus_io_data[0] = UD_PIN_PD14,
        .x_io.x_p_bus_io_data[1] = UD_PIN_PD15,
        .x_io.x_p_bus_io_data[2] = UD_PIN_PD16,
        .x_io.x_p_bus_io_data[3] = UD_PIN_PD17,
        .x_io.x_p_bus_io_data[4] = UD_PIN_PD18,
        .x_io.x_p_bus_io_data[5] = UD_PIN_PD19,
        .x_io.x_p_bus_io_data[6] = UD_PIN_PD20,
        .x_io.x_p_bus_io_data[7] = UD_PIN_PD21,
    };

    i32_fd = open("/dev/ud_bus", O_RDWR);
    if(i32_fd < 0)
    {
        printf("open bus fail\n");
        i32_result = -1;
        close(i32_fd);
        return (i32_result);
    }

    ioctl(i32_fd, UD_BUS_CMD_INIT, &x_bus);
    j = 1;
    i = 32;
    while(i --)
    {
        x_bus.u32_bus_addr = 0x02;
        x_bus.u32_bus_data = (j<<(i%8))&0xff;
        ioctl(i32_fd, UD_BUS_CMD_SET_DATA, &x_bus);
        sleep(1);
    }

    i = 65535;
    while(i --)
    {
        x_bus.u32_bus_addr = 0x02;
        ioctl(i32_fd, UD_BUS_CMD_GET_DATA, &x_bus);
        printf("io 0x%x\n", x_bus.u32_bus_data);
//        if(x_bus.u32_bus_data != 0xff)
//        {
//            x_bus.u32_bus_addr = 0x04;
//            x_bus.u32_bus_data = 0x83;
//            ioctl(i32_fd, UD_BUS_CMD_SET_DATA, &x_bus);
//        }
//        else
//        {
//            x_bus.u32_bus_addr = 0x04;
//            x_bus.u32_bus_data = 0x80;
//            ioctl(i32_fd, UD_BUS_CMD_SET_DATA, &x_bus);
//        }

        sleep(1);
    }

    close(i32_fd);

	return (i32_result);
}
