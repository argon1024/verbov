TARGET = pipe_chat
#TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run: pipe_chat
	(terminator -e "./pipe_chat pipein pipeout"&) && (terminator -e "./pipe_chat pipeout pipein" &)

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 

