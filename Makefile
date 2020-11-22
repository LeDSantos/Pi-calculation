CC=gcc
CFLAGS=-Wall -fopenmp

all: gauss montecarlo simpson

gauss: gauss.c
	$(CC) $(CFLAGS) gauss.c -o pi_gauss

montecarlo: montecarlo_pi.c
	$(CC) $(CFLAGS) montecarlo_pi.c -o pi_montecarlo

simpson: simpson.c
	$(CC) $(CFLAGS) simpson.c -o pi_simpson

clean:
	rm pi_*
