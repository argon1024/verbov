TARGET = tietie
#TARGET = pipe_readers 
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = $(TARGET).c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc $(CFLAGS) $^ -o $@ 

run: tietie
	ls | ./tietie a out.txt && echo result=`cat out.txt`

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 

