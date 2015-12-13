TARGET = cp1
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

build: $(OBJ)
	gcc $(CFLAGS) $^ -o $@
cat:
	cat /var/log/syslog | tail -n 10
clean:
	rm -f *.o *.so $(TARGET)
