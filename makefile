#Hellow World makefile
# require to run => export LD_LIBRARY_PATH=`pwd`

ALL:
	gcc -shared -fpic hello_lib.c -o libHello.so
	gcc hello.c -L. -lHello -o hello

hello_ld_lib:
	gcc -c -fpic -fPIC -shared hello_ld_lib.c -o hello_ld_lib.o
	gcc -shared -o libhello.so hello_ld_lib.o
	gcc hello_ld_lib.c -o hello -ldl
	

clean:
	rm -f *.so hello
