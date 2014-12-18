obj-m += ud_device_lcd_hg160160_logo.o
ud_device_lcd_hg160160_logo-objs += ud_device_lcd_hg160160.o
ud_device_lcd_hg160160_logo-objs += ../ud_lcd_logo_creaway.o

KDIR :=/home/work/linux-at91-linux-2.6.39-at91
PWD :=$(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux- modules
clean:
	rm -f *.o *.ko *.symvers *.order *.cmd .*.cmd *.mod.c
