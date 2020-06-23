install: main.o tp4.o
	gcc -Wall main.o tp4.o -o main
main.o: main.c tp4_abr.h
	gcc -Wall -c main.c
tp4.o: tp4_abr.c tp4_abr.h
	gcc -Wall -c tp4_abr.c -o tp4.o

clean:
	rm *.o main ||:
