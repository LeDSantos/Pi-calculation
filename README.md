# Pi - diferentes implementações

**chmod 777 rodar.sh e ./rodar.sh para executar tudo**

Pi calculation implementations

The following programs implement known numerical methods for calculating pi.
Simpson.c uses the well known Newton-Côtes style algortihm.
Gauss.c uses Legendre-Gaussian quadrature method. Legendre's roots are calculated using bisection and Newton for node approximation.
Both try to approximate the numerical integral of 4/(1+x^2) between 0 and 1.

Im interested with montecarlo performance. If you want to contribute, e-mail me please
at mlaportaigranados@gmail.com with total execution time(calculated inside program), CPUspecs and OS environment.
If you would like to receive a more detailed mathematical paper on this subject(on Catalan only) e-mail me.

Compilation:
Tried using gcc version 7.3.0 (Ubuntu 7.3.0-27ubuntu1~18.04)
Compile with
gcc -Wall "...".c -lm
Use -fopenmp for montecarlo code.  
