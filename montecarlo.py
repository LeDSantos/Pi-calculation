import sys
import random as r
import math as m
import pyRAPL
import time

ENERGIA=1

def main(args):
    # Number of darts that land inside.
    inside = 0

    if(len(args)<2):
        # Total number of darts to throw.
        total = int(input("Introduce the number of iterations n: "))
    else:
        total=int(args[1])

    if(ENERGIA):
        pyRAPL.setup()
        report = pyRAPL.outputs.DataFrameOutput()

    print(total)

    t0 = time.time()

    # Iterate for the number of darts.
    for i in range(0, total):
        # Generate random x, y in [0, 1].
        x2 = r.random()**2
        y2 = r.random()**2
        # Increment if inside unit circle.
        if (x2 + y2) <= 1.0:
            inside += 1

    # inside / total = pi / 4
    pi = (float(inside) / total) * 4

    # It works!
    print(pi)
    if(ENERGIA):
        print("Energia consumida: ",report.data.head())

    t_final=time.time()
    print("tempo final:", t_final-t0)

if __name__ == '__main__':
    DEBUG=0
    sys.exit(main(sys.argv)) 