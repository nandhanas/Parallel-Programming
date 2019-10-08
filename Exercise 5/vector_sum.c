/*

Ring communication of Large sets of data using MPI non-blocking communication 

*/


#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[]) {

  int i,myrank,numprocs,sum = 0,final,N;
  N = atoi(argv[1]);
  int vector[N],data[N];

  for(i=0; i< N; i++)
    vector[i] = i;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
  MPI_Request request;
  MPI_Status status;
  int next = (myrank+1)%numprocs;
  int prev = (myrank-1)%numprocs;

  MPI_Isend(vector, N, MPI_INT, next, 101, MPI_COMM_WORLD, &request);
  MPI_Irecv(data,N,MPI_INT, prev, 101, MPI_COMM_WORLD, &request);
  MPI_Wait(&request, &status);

  for(i=0;i<N;i++)
    sum+=vector[i];

  MPI_Reduce(&sum, &final, 1, MPI_INT, MPI_SUM,0, MPI_COMM_WORLD);
  MPI_Bcast(&final, 1, MPI_INT,0, MPI_COMM_WORLD);

  printf("id:%d -> %d\n",myrank,final);
  MPI_Finalize();

}
