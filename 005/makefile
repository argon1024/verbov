
TARGET = shell 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = *.c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 
