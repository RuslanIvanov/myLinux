# This is makefile for my first project

all: my_pwd

my_pwd: main_pwd.o
	gcc main_pwd.o -o main_pwd

main_pwd.o: main_pwd.cpp
	gcc -fPIC main_pwd.cpp -c -o main_pwd.o

clean:
	rm -rf *.o
	rm -rf my_pwd

#run:
#	./main_pwd
