TARGET = cp2.ko
obj-m +=  cp2.o

build:
	make -C ~/my_kernel/linux-4.3/ M=`pwd` modules
load:	build
	sudo insmod $(TARGET)
unload:	
	sudo rmmod $(TARGET)
mknod:
	sudo mknod -m 666 /dev/lohoped_dev c 800 0 
ls:
	dmesg | tail -n 10
test:	
	echo "123" > /dev/lohoped_dev
client:	client.c
	gcc client.c -o client
clean-client:
	rm -f client
clean:
	find . -type f ! -name '*.c' ! -name '*.h' ! -name 'Makefile' | xargs rm -rf
help:
	echo "load\nunload\nls\ntest\nclean\nhelp\nclient\n"
