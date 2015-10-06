#
all: thread

thread: main.o
	g++ main.o -o -lpthread

main.o: main.c
	g++ -fPIC -c main.c

clean:
	rm -rf *.o
	rm thread
