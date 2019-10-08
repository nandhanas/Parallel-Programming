/*

PI approximation using MPI blocking communication 

*/


#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]) {

  int i,myrank,numprocs,N=100000000,chunk,start,end;
  double x,fx,pi_approx,pi,h;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

  double starttime = MPI_Wtime();

  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

  chunk = N/numprocs;
  start = chunk*myrank;
  end = start+chunk;
  h = 1/(double)N;
  pi_approx = 0.0;

  for(i=start; i<end; i++) {
        x =((double)i-0.5)*h;
        fx = 1/(1+(x*x));
        pi_approx += 4*fx;
  }

  pi_approx = h * pi_approx;

  MPI_Reduce(&pi_approx,&pi,1,MPI_DOUBLE,MPI_SUM,(numprocs-1),MPI_COMM_WORLD);

  double endtime = MPI_Wtime();

  if(myrank == 0) {
        MPI_Recv(&pi,1,MPI_DOUBLE,(numprocs-1),101,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("PI = %f\n", pi);
        printf("Time taken = %f\n seconds", endtime-starttime);
  }
  if(myrank == (numprocs-1)) {
        MPI_Send(&pi,1,MPI_DOUBLE,0,101,MPI_COMM_WORLD);
  }

  MPI_Finalize();

}
