.PHONY: all ejecutar

all: Exe

Exe: main.o GoL.o
	gcc main.o GoL.o -o Exe && ./Exe

main.o: main.c
	gcc -c -Wall main.c

GoL.o: GoL.c
	gcc -c -Wall GoL.c

ejecutar: Exe
	./Exe

clean:
	rm *.o
	rm Exe 