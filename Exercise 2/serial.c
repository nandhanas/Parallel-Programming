/*

Serial program to visualize loop scheduling

*/


#include <stdlib.h>
#include <stdio.h>

void print_usage( int * a, int N, int nthreads ) {

  int tid, i;
  for( tid = 0; tid < nthreads; ++tid ) {

    fprintf( stdout, "%d: ", tid );

    for( i = 0; i < N; ++i ) {

      if( a[ i ] == tid) fprintf( stdout, "*" );
      else fprintf( stdout, " ");
    }
    printf("\n");
  }
}

int main( int argc, char * argv[] ) {

   const int N = 250;
   int a[N],i;
   int thread_id = 0;
   int nthreads = 1;
   for( i = 0; i < N; ++i) {
     a[i] = thread_id;
   }
   print_usage(a, N, nthreads);
 }
