/*

Ring communication of process id using MPI non-blocking communication 

*/

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[]) {

  int i,myrank,numprocs,sum = 0,final;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Request request;
  MPI_Status status;
  int next = (myrank+1)%numprocs;
  int prev = (myrank-1)%numprocs;

  MPI_Isend(&myrank, 1, MPI_INT, next, 101, MPI_COMM_WORLD, &request);
  MPI_Irecv(&sum,1,MPI_INT, prev, 101, MPI_COMM_WORLD, &request);
  MPI_Wait(&request, &status);
  MPI_Reduce(&sum, &final, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
  MPI_Bcast(&final, 1, MPI_INT,0, MPI_COMM_WORLD);

  printf("id:%d -> %d\n",myrank,final);
  MPI_Finalize();

}
