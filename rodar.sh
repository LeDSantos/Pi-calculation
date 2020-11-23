#!/bin/bash
echo "Calculando pi de 3 formas diferentes"
make clean
make all

#numero de interacoes
N=100000000

export OMP_NUM_THREADS=1
echo -en "\n$OMP_NUM_THREADS threads: SERIAL----------------\n"
echo -en "\nSIMPSON\n"
./pi_simpson $N

echo -en "\nMONTECARLO\n"
./pi_montecarlo $N

echo -en "\nINTEGRAL\n"
./pi_integral $N

#export OMP_NUM_THREADS=3
NPROC=$(nproc --all)
export OMP_NUM_THREADS=$NPROC

echo -en "\n$OMP_NUM_THREADS threads: PARALELO--------------\n"

echo -en "\nMONTECARLO\n"
./pi_montecarlo $N

echo -en "\nINTEGRAL\n"
./pi_integral $N