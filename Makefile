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

test : CFLAGS += -O3
test : mem_test
	valgrind --leak-check=full ./mem_test

gol: main.o gol.o
	$(CC) main.o gol.o -o gol

mem_test: mem_test.o gol.o
	$(CC) mem_test.o gol.o -o mem_test

main.o: main.c gol.h
	$(CC) -c main.c

gol.o: gol.c gol.h
	$(CC) -c gol.c

mem_test.o: mem_test.c
	$(CC) -c mem_test.c

clean:
	rm *.o
	rm gol
