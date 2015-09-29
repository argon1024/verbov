
# require to run => export LD_LIBRARY_PATH=`pwd`


all:	hello.o libworld.a 
	gcc -o hello  hello.o -L. -lworld

hello.o:	hello.c
	gcc -c hello.c

libworld.a: hello_lib.o
	ar cr libworld.a hello_lib.o 

libhello.o: hello_lib.c
	gcc -c hello_lib.c

clean:
	rm -rf *.o libhello.so hello_lib.so libworld.a hello 

run:
	export LD_LIBRARY_PATH=`pwd`
	./hello
