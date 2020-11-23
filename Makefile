CC=gcc
CFLAGS=-Wall -fopenmp

all: gauss montecarlo simpson integral

gauss: energia.o gauss.o
	$(CC) $(CFLAGS) gauss.o energia.o -o pi_gauss

gauss.o: gauss.c
	$(CC) $(CFLAGS) -c gauss.c

montecarlo: energia.o montecarlo_pi.o
	$(CC) $(CFLAGS) montecarlo_pi.o energia.o -o pi_montecarlo

montecarlo_pi.o: montecarlo_pi.c
	$(CC) $(CFLAGS) -c montecarlo_pi.c

simpson: energia.o simpson.o
	$(CC) $(CFLAGS) simpson.o energia.o -o pi_simpson

simpson.o: simpson.c
	$(CC) $(CFLAGS) -c simpson.c

integral: energia.o integral.o
	$(CC) $(CFLAGS) integral.o energia.o -o pi_integral

integral.o: integral.c
	$(CC) $(CFLAGS) -c integral.c

energia.o: energia.c
	$(CC) -c energia.c

clean:
	rm *.o pi_*
