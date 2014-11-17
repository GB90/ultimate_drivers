obj-m += ud_device_bus_emulated.o

KDIR :=/home/work/linux-at91-linux-2.6.39-at91
PWD :=$(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE=arm-linux- modules
clean:
	rm -f *.o *.ko *.symvers *.order *.cmd .*.cmd *.mod.c
