/*

OpenMp program to visualize loop scheduling

*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#define THREADS 5

void print_usage( int * a, int N) {
  int tid, i;
  for( tid = 0; tid < THREADS; ++tid ) {
    fprintf( stdout, "%d: ", tid );
    for( i = 0; i < N; ++i ) {
        if( a[ i ] == tid) fprintf( stdout, "*" );
        else fprintf( stdout, " ");
    }
     printf("\n");
   }
};

void static_scheduling(int *a, int N, int chunk){
 int i;
 #pragma omp parallel for schedule(static,chunk)
     for(i = 0; i < N; ++i)
        {
            a[i] = omp_get_thread_num();
        }
   printf("Static:\n");
   print_usage(a, N);
};

void static_nochunk(int *a, int N){
 int i;
 #pragma omp parallel for schedule(static)
     for(i = 0; i < N; ++i)
        {
            a[i] = omp_get_thread_num();
        }
   printf("Static:\n");
   print_usage(a, N);
};

void dynamic_scheduling(int *a, int N, int chunk){
  int i;
  #pragma omp parallel for schedule(dynamic,chunk)
     for(i = 0; i < N; ++i)
        {
            a[i] = omp_get_thread_num();
        }
    printf("Dynamic:\n");
    print_usage(a, N);
};

void dynamic_nochunk(int *a, int N){
  int i;
  #pragma omp parallel for schedule(dynamic)
     for(i = 0; i < N; ++i)
        {
            a[i] = omp_get_thread_num();
        }
    printf("Dynamic:\n");
    print_usage(a, N);
};

int main( int argc, char * argv[] ) {

   const int N = 250;
   int a[N],choice,i,chunk;
   int isStatic,isDynamic;
   if(argv[1]) {
      isStatic = !(strcmp(argv[1],"static"));
      isDynamic = !(strcmp(argv[1],"dynamic"));
      if(!(isStatic) || !(isDynamic))
      {
        printf("Enter a valid scheduling type\n");
        return 0;
      }
   }
   else
   {
      printf("Enter a valid scheduling type\n");
      return 0;
   }
   if(argv[2]) {
       chunk = atoi(argv[2]);
       if(chunk <= 0){
          printf("Enter a valid chunk size\n");
          return 0;
       }
       if(isStatic){
         static_scheduling(a,N,chunk);
       }
       if(isDynamic){
         dynamic_scheduling(a,N,chunk);
       }
    }
    else {
       if(isStatic){
         static_nochunk(a,N);
       }
       if(isDynamic){
         dynamic_nochunk(a,N);
       }
    }
}
