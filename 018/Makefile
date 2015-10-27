# this is my shell
all:demon 

demon: main.o
	gcc main.o -o demon

main.o: main.c
	gcc -fPIC -c main.c

clean:
	rm -rf *.o
	rm demon
