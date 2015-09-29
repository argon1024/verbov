#Hellow World makefile
# require to run => export LD_LIBRARY_PATH=`pwd`

ALL:
	gcc -c -fpic -fPIC -shared hello_ld_lib.c -o hello_ld_lib.o
	gcc -shared -o libhello.so -fPIC hello_lib.c
	gcc hello_ld_lib.c -o hello -ldl

clean:
	rm -f *.so hello a.out  libhello.so

run:
	export LD_LIBRARY_PATH=`pwd`
	./hello

