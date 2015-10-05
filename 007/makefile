
TARGET = integral
CXXFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = integral.c
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(CXXFLAGS) $^ -o $@ 

clean:
	rm -f *.o *~

clean-all:
	rm -f *.o *.so $(TARGET) 
