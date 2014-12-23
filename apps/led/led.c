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
#include <sys/mman.h>
#include <linux/fb.h>

#include <ud_device_bus_emulated.h>
#include <ud_device_lcd.h>

int main(void)
{
    int i32_fd_bus, i32_fd_lcd, i32_fd_glcd, i;
    int i32_result = EXIT_SUCCESS;
    struct bus_struct x_bus;

    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    char *frameBuffer = 0;
    char *vfb = 0;

    i32_fd_bus = open("/dev/ud_bus", O_RDWR);
    if(i32_fd_bus < 0)
    {
        printf("open bus fail\n");
        i32_result = -1;
        close(i32_fd_bus);
        return (i32_result);
    }

    i32_fd_lcd = open("/dev/ud_lcd", O_RDWR);
    if(i32_fd_lcd < 0)
    {
        printf("open lcd fail\n");
        i32_result = -1;
        close(i32_fd_bus);
        close(i32_fd_lcd);
        return (i32_result);
    }

    i32_fd_glcd = open("/dev/ud_glcd", O_RDWR);
    if(i32_fd_glcd < 0)
    {
        printf("open glcd fail\n");
        i32_result = -1;
        close(i32_fd_bus);
        close(i32_fd_lcd);
        close(i32_fd_glcd);
        return (i32_result);
    }

    i = 65535;

    ioctl(i32_fd_glcd, FBIOGET_FSCREENINFO, &finfo);
    ioctl(i32_fd_glcd, FBIOGET_VSCREENINFO, &vinfo);
    frameBuffer = (char *)mmap(0, finfo.smem_len,
                                  PROT_READ | PROT_WRITE, MAP_SHARED,
                                  i32_fd_glcd, 0);
    if (frameBuffer == MAP_FAILED) {
        perror("Error: Failed to map framebuffer device to memory");
        munmap(frameBuffer, finfo.smem_len);
        close(i32_fd_bus);
        close(i32_fd_lcd);
        close(i32_fd_glcd);

        return (i32_result);
    }
    ioctl(i32_fd_glcd, FBIOBLANK, NULL);

    vfb = frameBuffer;

    while(i--)
    {
        *vfb++ = 0;
        x_bus.u32_bus_addr = 0x02;
        x_bus.u32_bus_data = (1<<(i%8))&0xff;
        ioctl(i32_fd_bus, UD_BUS_CMD_SET_DATA, &x_bus);
        ioctl(i32_fd_lcd, UD_LCD_CMD_REFRESH, NULL);
        sleep(1);
    }

    munmap(frameBuffer, finfo.smem_len);
    close(i32_fd_bus);
    close(i32_fd_lcd);
    close(i32_fd_glcd);

	return (i32_result);
}
