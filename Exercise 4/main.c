/*

Initializing Identity Matrix using MPI blocking and non-blocking communication 

*/


#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc, char *argv[])
{
   int numprocs, rank, n,r,I,i,j,k,N,choice;
   if(argv[1])
   {
      N = atoi(argv[1]);
   }
   else
   {
      return 0;
   }
   if(argv[2]){
    choice = atoi(argv[2]);
   }
   FILE *fp;
   fp = fopen("distributed_matrix.bin","wb");

   MPI_Init(&argc,&argv);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
   MPI_Request request;
   MPI_Status status;

   if(choice && (rank ==0)){
    printf("Blocking Communication\n");
   }
   else if(rank == 0){
     printf("Non-blocking Communication\n");
   }

   n=N/numprocs;
   r=N%numprocs;

   if(rank<r)
     n++;

   int *mat = (int *) malloc (n*N*sizeof(int));

   I = n*rank;
   if(rank >= r)
     I +=r;

     for(i=0; i<n; i++)
       {
         for(j=0; j<N; j++)
         {
           if(j==I)
            *(mat+ i*N +j) = 1;
           else
            *(mat+ i*N +j) = 0;
          }
          I++;
        }
        if (rank == 0)
        {
             for(i=0; i<n; i++)
             {
                for(j=0;j<N;j++)
                {
                   if(N<=10)
                       printf("%d", *(mat+ i*N + j));
                   else
                       fprintf(fp,"%d", *(mat+ i*N+j));
                }
                if(N<=10)
                     printf("\n");
                else
                    fprintf(fp,"\n");
             }
            for(k=1; k< numprocs; k++)
             {
                if(k==r)
                {
                   n=n-1;
                }
                if(choice == 1) {
                  MPI_Recv(mat, n*N, MPI_INT, k, 101, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
                else {
                   MPI_Irecv(mat, n*N, MPI_INT, k, 101, MPI_COMM_WORLD,&request);
                   MPI_Wait(&request, &status);
                }
                for(i=0;i<n;i++)
                {
                     for(j=0;j<N;j++)
                     {
                       if(N<=10)
                         printf("%d", *(mat+ i*N+j));
                       else
                         fprintf(fp, "%d", *(mat+i*N+j));
                     }
                     if(N<=10)
                        printf("\n");
                     else
                        fprintf(fp, "\n");
                }
             }
         }
         else
         {
              if(choice == 1)
              {
               MPI_Send(mat, n*N, MPI_INT,0,101,MPI_COMM_WORLD);
              }
              else {
               MPI_Isend(mat, n*N, MPI_INT,0,101,MPI_COMM_WORLD,&request);
              }
         }
      free(mat);
      MPI_Finalize();
      fclose(fp);
}
