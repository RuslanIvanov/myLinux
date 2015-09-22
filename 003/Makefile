# This is makefile for my first project

all: hello

hello: main.o
	gcc -fPIC main.o -ldl -o hello

libHello.so: hello.cpp
	gcc -fPIC -shared hello.cpp -o libHello.so

main.o: main.cpp libHello.so
	gcc -fPIC  main.cpp -c -o main.o



clean:
	rm -rf *.o
	rm libHello.so
	rm hello
run:
	export LD_LIBRARY_PATH=`pwd`
	./hello
