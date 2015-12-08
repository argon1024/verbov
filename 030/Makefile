obj-m +=  chardriver.o

build:
	make -C ~/my_kernel/linux-4.3/ M=`pwd` modules
load:	build
	sudo insmod chardriver.ko
unload:	
	sudo rmmod chardriver.ko
mknod:
	sudo mknod -m 666 /dev/lohoped_dev c 800 0 
ls:
	dmesg | tail -n 10
test:	
	echo "123" > /dev/lohoped_dev
clean:
	find . -type f ! -name '*.c' ! -name '*.h' ! -name 'Makefile' | xargs rm -rf
help:
	echo "load\nunload\nls\ntest\nclean\nhelp"
