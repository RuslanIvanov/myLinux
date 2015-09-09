# This is makefile for my first project

hello: main.o
    gcc -o hello main.o

main.o: main.c
    gcc -c main.c

clean:
    rm -rf *.o