/*
Pi calculation by using Gauss-Legendre quadrature numerical integration.
Miquel Bernat Laporta i Granados
Mathematics UAB
miquelbernat.laporta@e-campus.uab.cat
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define EPSILON 0.01 //Bisection method tolerance
#define TOL 1.e-8 //Newton method tolerance
#define KMAX 100 //Max iterations allowed in Newton method

//Legendre polynomials avaluation

double legendre(double x, int n){

double T0=1;
double T1=x;
double Tn;
int i;

for(i=2; i<=n; i++){

       Tn=((2*i-1)*x*T1-(i-1)*T0)/(i);
       T0=T1;
       T1=Tn;
}
return T1;
}
//Derivative calculation
double derive(double x, int n){

int i;
double Tn1;

for(i=2; i<=n; i++){
   Tn1=(-i*x*legendre(x,i)+i*legendre(x,i-1))/(1-x*x);
}

   return Tn1;

}

//Newton method implementation
double Newton(double x, int n){
  int k=0;
  double d, fx, dfx;
  do{
       fx=legendre(x,n);
       dfx=derive(x,n);
       d = fx / dfx;
       x -= d;
       k++;
}
  while(k <= KMAX && (fabs (d) >= TOL));
  if(k > KMAX){
  printf("Convergence not archieved...\n");
  printf("No convergence archieved in %d iterations with tolerance %f \n", KMAX, TOL);
}
return x;
}

//Bisection method implementation
double bisection(double a, double b, int n){

  double c = a;
  while ((b-a) >= EPSILON){
  c = (a+b)/2;
  if (legendre(c,n) == 0.0)
     break;
  else if (legendre(c,n)*legendre(a,n) < 0)
          b = c;
  else
          a = c;
}
return c;
}
//Integrated function to obtain pi
double f(double x){

        return 4/(1+x*x);
}

int main(){

int n,i,k;
double temp;
double integral;
double *v;

printf("Introduce the number of nodes n=2,4,6,8:\n");
scanf("%d",&n);
v = (double*)malloc(n*sizeof(double));
double *a;
a = (double*)malloc(n*sizeof(double));

clock_t begin = clock();
switch(n){

  case 2 :
  v[0]=Newton(bisection(-0.65,-0.5,n),n);
  v[1]=Newton(bisection(0.5,0.65,n),n);
  break;

  case 4 :
  v[0]=Newton(bisection(-1,-0.8,n),n);
  v[1]=Newton(bisection(-0.5,-0.2,n),n);
  v[2]=Newton(bisection(0.2,0.5,n),n);
  v[3]=Newton(bisection(0.8,1,n),n);
  break;

  case 6 :
  v[0]=Newton(bisection(-1,-0.85,n),n);
  v[1]=Newton(bisection(-0.8,-0.6,n),n);
  v[2]=Newton(bisection(-0.5,-0.1,n),n);
  v[3]=Newton(bisection(0.1,0.5,n),n);
  v[4]=Newton(bisection(0.6,0.8,n),n);
  v[5]=Newton(bisection(0.85,1,n),n);
  break;

  case 8 :
  v[0]=Newton(bisection(-1,-0.9,n),n);
  v[1]=Newton(bisection(-0.85,-0.6,n),n);
  v[2]=Newton(bisection(-0.6,-0.4,n),n);
  v[3]=Newton(bisection(-0.3,-0.1,n),n);
  v[4]=Newton(bisection(0.1,0.3,n),n);
  v[5]=Newton(bisection(0.3,0.6,n),n);
  v[6]=Newton(bisection(0.7,0.8,n),n);
  v[7]=Newton(bisection(0.9,1,n),n);
  break;

  default :
  printf("Wrong n introduced...");
  break;
}
  for(k=0; k<n; k++){
     a[k]=2/((1-v[k]*v[k])*derive(v[k],n)*derive(v[k],n));
}
  for(i=0; i<n; i++){
     temp += a[i]*f(0.5*v[i]+0.5);
}
  integral = 0.5*temp;
  printf("Pi value is %.16G\n",integral);
  clock_t end = clock();
  double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
  printf("Total execution time: %.15G sec\n", time_spent);
  return 0;
}
