# this
all: my_pipe

my_pipe: main.o
	g++ main.o -o my_pipe

main.o: main.c
	g++ -fPIC -c main.c

clean:
	rm -rf *.o
	rm my_pipe
