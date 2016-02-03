a.out: logLib.o main.o
	gcc -g logLib.o main.o

logLib.o: logLib.c
	gcc -g -c logLib.c log.h

main.o: main.c
	gcc -g -c main.c log.h
