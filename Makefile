CC = gcc $(CFLAGS)
CFLAGS = -Wall -Wextra -std=c99

.PHONY: all debug release test mem_test ejecutar clean

all: debug

release : CFLAGS += -O3
release : gol

debug : CFLAGS += -g -O0
debug : gol

ejecutar: gol
	./gol

gol: main.o gol.o config.o
	$(CC) main.o gol.o config.o -o gol

main.o: main.c gol.h
	$(CC) -c main.c

gol.o: gol.c gol.h
	$(CC) -c gol.c

config.o: config.c config.h
	gcc -c config.c config.h

test : CFLAGS += -O3
test : mem_test
	valgrind --leak-check=full ./mem_test

mem_test: mem_test.o gol.o
	$(CC) mem_test.o gol.o -o mem_test

mem_test.o: mem_test.c
	$(CC) -c mem_test.c

clean:
	rm *.o
	rm gol
	rm *.gch
