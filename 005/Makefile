# this is my shell
all: shell

shell: main.o
	gcc main.o -o shell

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm shell
