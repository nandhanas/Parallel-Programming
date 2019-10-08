/*

PI approximation program using the rectangle method in OpenMp

*/


#include<stdio.h>
#include<math.h>
#include<omp.h>
#define N 100000000

int main(int argc, char *argv[]) {
  int i,choice,chunk =1000;
  if(argv[1])
         choice = atoi(argv[1]);
  double x,fx,pi_approx;
  double h = 1/(double)N;
  double start = omp_get_wtime();
  #pragma omp parallel private(x,fx)
  {
       #pragma omp for reduction(+:pi_approx) schedule(dynamic,chunk) nowait
        for(i=0; i<N; i++) {
                x = (i-0.5)*h;
                fx = 1/(1+(x*x));
                if(argv[1]) {
                        if (choice == 1){
                          printf("Critical"\n");
                          #pragma omp critical
                          pi_approx += (fx*4);
                         }
                         else if (choice == 2)
                        {
                          printf("Atomic"\n");
                          #pragma omp atomic
                          pi_approx += (fx*4);
                        }
                 }
                else {
                   printf("Reduction"\n");
                   pi_approx += (fx*4);
                }
         }
  }
  pi_approx = h * pi_approx;
  double end = omp_get_wtime();
  printf("PI = %f\n", pi_approx);
  printf("Time taken = %f\n seconds", end-start);
  return 0;
}
