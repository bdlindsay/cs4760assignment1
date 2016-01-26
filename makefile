a.out: logLib.o main.o
	gcc logLib.o main.o

logLib.o: logLib.c
	gcc -c logLib.c

main.o: main.c
	gcc -c main.c
