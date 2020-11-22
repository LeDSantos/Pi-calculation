CC=gcc-9
CFLAGS=-fopenmp -O3

default: main.c
	$(CC) $(CFLAGS) main.c -o pi

make run: pi
	./pi

clean:
	rm pi