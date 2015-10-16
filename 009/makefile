
TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = pipe_readers.c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run:
	./pipe_readers -c ls

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 
