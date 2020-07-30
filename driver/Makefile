obj-m += clementDriver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	sudo insmod clementDriver.ko
	sudo chmod ugo+rw /dev/cdnull

clean:
	sudo rmmod clementDriver.ko
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
