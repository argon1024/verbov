TARGET = select
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
	(terminator -e "./select pipein pipeout" &) && (terminator -e "./select pipeout pipein" &)

clean:
	rm -f *.o *.so $(TARGET) pipein pipeout

