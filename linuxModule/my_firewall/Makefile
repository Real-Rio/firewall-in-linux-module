KERN_DIR = /usr/src/linux-headers-5.4.0-89-generic
# KERN_DIR = /lib/modules/$(shell uname -r)/build
myfw-objs := linux_module.o dya_firewall.o dya_utils.o nl_kernel.o 

obj-m += myfw.o

all:mod app

mod:
	make -C $(KERN_DIR) M=$(shell pwd) modules   
app:
	gcc -o nl_client nl_client.c
clean:                                  
	make -C $(KERN_DIR) M=$(shell pwd) modules clean
	rm -rf modules.order
	rm -f *.symvers 
