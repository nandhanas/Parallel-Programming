/*

PI approximation program using the rectangle method 

*/


#include<stdio.h>
#include<math.h>
#define N 100000000

int main() {
  int i;
  double x,fx,pi_approx = 0.0;
  double h = 1/(double)N;
  for(i=0; i<N; i++) {
    x = ((double)i-0.5)*h;
    fx = 1/(1+(x*x));
    pi_approx += fx*4;
  }
  pi_approx=h*pi_approx;
  printf("PI = %f\n", pi_approx);
}
