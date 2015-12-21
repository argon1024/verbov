TARGET = cp1
CFLAGS = -O2 -Wall -Wno-parentheses $(INC)
OBJ = $(ASRC:.asm=.o) $(SRC:.c=.o)

all: $(TARGET)

build: $(OBJ)
	gcc -std=gnu99 $(CFLAGS) $^ -o $@
cat:
	cat /var/log/syslog | tail -n 10
ps:
	ps -A | grep $(TARGET)
kill:
	killall $(TARGET)
sig1:
	killall -s 10 $(TARGET)
sig2:
	killall -s 12 $(TARGET)
nc:
	nc 127.0.0.1 15000
clean:
	rm -f *.o *.so $(TARGET)
