
TARGET = myps
CXXFLAGS = -O2 -Wall -Wno-parentheses $(INC)
SRC = myps.cpp
LIBS =
INC =
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	g++ $(CXXFLAGS) $^ -o $@ 

clean:
	rm -f *.o *~

clean_all:
	rm -f *.o *.so $(TARGET) 
