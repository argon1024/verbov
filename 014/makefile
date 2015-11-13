TARGET = broadcast
#TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o *~ $(TARGET)

clean-all:
	rm -f *.o *.so $(TARGET) 

