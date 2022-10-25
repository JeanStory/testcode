obj-m += nf_test.o

all:
	make -C /lib/modules/3.10.0-1160.11.1.el7.x86_64/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install:
	sudo insmod nf_test.ko

uninstall:
	sudo rmmod nf_test

mknod:
	sudo mknod /dev/nf_test c 117 0
	sudo chmod 666 /dev/nf_test
