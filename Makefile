CC=cc
CFLAGS=-g -Wall -pthread
DEPS=sockets-example.h
OBJ=main.o send.o recv.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sockets-example: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f sockets-example *.o
