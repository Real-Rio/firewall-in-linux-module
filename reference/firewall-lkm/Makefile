# KERN_DIR = /usr/src/linux-headers-5.4.0-89-generic
KERN_DIR = /lib/modules/$(shell uname -r)/build
myfw-objs := netfltrHooks.o procfsHelper.o utils.o firewall-lkm.o
obj-m += myfw.o

all:
	make -C $(KERN_DIR) M=$(shell pwd) modules   
clean:                                  
	make -C $(KERN_DIR) M=$(shell pwd) modules clean
	rm -rf modules.order
	rm -f *.symvers
