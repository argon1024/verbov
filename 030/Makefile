obj-m +=  chardriver.o

build:
	make -C ~/my_kernel/linux-4.3/ M=`pwd` modules
load:	build
	sudo insmod chardriver.ko
unload:	build
	sudo rmmod chardriver.ko
mknod:
	sudo mknod /dev/lohoped_dev c 800 0 && sudo chmod 777 /dev/lohoped_dev
ls:
	dmesg | tail -n 10
test:
	echo "123" > /dev/lohoped_dev
clean:
#	ls -A | find . \(-iname *.o -iname *.cmd \) | xargs rm

