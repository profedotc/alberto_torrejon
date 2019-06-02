.PHONY: all ejecutar clean

all: Exe

Exe: main.o GoL.o
	gcc main.o GoL.o -o Exe

main.o: main.c GoL.h
	gcc -c -Wall main.c

GoL.o: GoL.c GoL.h
	gcc -c -Wall GoL.c

ejecutar: Exe
	./Exe

clean:
	rm *.o
	rm Exe 