TARGET = my_tracert
#TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run: udp_echo
	(terminator -e "./udp_echo 10000 40000"&) && (terminator -e "./udp_echo 40000 10000" &)

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 

