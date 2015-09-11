#Hellow World makefile
# require to run => export LD_LIBRARY_PATH=`pwd`

ALL:
	gcc -shared -fpic hello_lib.c -o libHello.so
	gcc hello.c -L. -lHello -o hello

clean:
	rm -f *.so hello
