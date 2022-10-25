obj-m += unkillable.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod unkillable.ko

uninstall:
	sudo rmmod unkillable

mknod:
	sudo mknod /dev/unkillable c 117 0
	sudo chmod 666 /dev/unkillable
