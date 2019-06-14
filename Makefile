KERN_DIR = /home/fengyuwuzu/myir/MYiR-iMX-Linux
CROSS_COMPILER ?= /home/fengyuwuzu/myir/gcc-linaro-4.9-2014.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
ARCH ?= arm

all: 
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILER) modules 

clean:
	make -C $(KERN_DIR) M=`pwd` ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILER) modules clean
	rm -rf modules.order

obj-m	+= myloadavg.o
