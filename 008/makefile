TARGET = thread_list
#TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

threads:
	gcc threads.c -o threads -pthread

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) threads 

