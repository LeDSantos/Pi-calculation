CC=gcc
CFLAGS=-Wall -fopenmp

all: gauss montecarlo simpson

gauss: energia.o gauss.c
	$(CC) $(CFLAGS) gauss.c energia.o -o pi_gauss

gauss.o: gauss.c
	$(CC) $(CFLAGS) -c gauss.o

montecarlo: energia.o montecarlo_pi.o
	$(CC) $(CFLAGS) montecarlo_pi.o energia.o -o pi_montecarlo

montecarlo_pi.o: montecarlo_pi.c
	$(CC) $(CFLAGS) -c montecarlo_pi.c

simpson: energia.o simpson.o
	$(CC) $(CFLAGS) simpson.c energia.o -o pi_simpson

simpson.o: simpson.c
	$(CC) $(CFLAGS) -c simpson.c

energia.o: energia.c
	$(CC) -c energia.c

clean:
	rm *.o pi_*
