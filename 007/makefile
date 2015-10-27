
TARGET = integral
SRC = integral.c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	gcc -std=gnu99 -g3 -Wall -Wno-parentheses $(INC) $^ -lm -lpthread -o $@ 

debug:	$(OBJ)
	gcc -g3 $(CXXFLAGS) $^ -lm -lpthread -o $(TARGET) 

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 
