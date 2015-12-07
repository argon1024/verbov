TARGET = poll
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run: $(TARGET)
	(terminator -e "./$(TARGET) pipein pipeout" &) && (terminator -e "./$(TARGET) pipeout pipein" &)

clean:
	rm -f *.o *.so $(TARGET) pipein pipeout

