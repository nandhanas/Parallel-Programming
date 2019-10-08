/*

Naive and Coalesced Transpose of a matrix using CUDA

*/


#include <stdio.h>
#include <stdlib.h>
#define N 2048
#define BLOCK_DIM 64

void print_matrix(int *mat){
 for(int row=0; row<N; row++) {
  for(int col=0; col<N; col++)
    printf("%d", mat[row*N+col]);
  printf("\n");
 }
};

int compare(int *mat1, int *mat2){
 for(int row=0; row<N; row++) {
  for(int col=0; col<N; col++) {
    if(mat1[row*N+col] != mat2[row*N+col]){
       return 0;
    }
  }
 }
 return 1;
}

__global__ void naive_transpose(int *d_in,int *d_out){
   int ix = blockIdx.x * BLOCK_DIM + threadIdx.x;
   int iy = blockIdx.y * BLOCK_DIM + threadIdx.y;
   if(ix<N && iy<N) {
      d_out[iy+ix*N] = d_in[ix+iy*N];
   }
};

__global__ void transpose_coalesced(int *d_in, int *d_out){
   int ix = blockIdx.x * BLOCK_DIM;
   int iy = blockIdx.y * BLOCK_DIM;
   int ox = blockIdx.y * BLOCK_DIM;
   int oy = blockIdx.x * BLOCK_DIM;
   int x = threadIdx.x, y = threadIdx.y;

   __shared__ int tile[BLOCK_DIM][BLOCK_DIM];

   tile[y][x] = d_in[(ix+x)+(iy+y)*N];

   __syncthreads();

   d_out[(ox+x)+(oy+y)*N] = tile[x][y];
};

int main()
{
 int num_bytes =N*N*sizeof(int);
 int *d_out, *d_in, *h_in, *h_out1,*h_out2;
 float time;
 cudaEvent_t start, stop;

 h_in = (int *)malloc(num_bytes);
 h_out1 = (int *)malloc(num_bytes);
 h_out2 = (int *)malloc(num_bytes);

 cudaMalloc((void**)&d_in,num_bytes);
 cudaMalloc((void**)&d_out,num_bytes);

 cudaEventCreate(&start);
 cudaEventCreate(&stop);

 for(int row=0; row<N; row++) {
  for(int col=0; col<N; col++)
    h_in[row*N+col] = col;
 }

 cudaMemcpy(d_in,h_in,num_bytes,cudaMemcpyHostToDevice);

 dim3 blocks(N/BLOCK_DIM,N/BLOCK_DIM);
 dim3 threads(BLOCK_DIM,BLOCK_DIM);

 cudaEventRecord(start);
 naive_transpose<<<blocks,threads>>>(d_in,d_out);
 cudaEventRecord(stop);

 cudaMemcpy(h_out1,d_out,num_bytes,cudaMemcpyDeviceToHost);
 cudaEventElapsedTime(&time, start, stop);

 printf ("Naive Transpose:\n");
 printf("\n");
 printf ("Time Taken: %f milliseconds\n", time);
 printf("Bandwidth: %f Gb/sec\n", (N*N*4*2*1e-6)/time);
 printf("\n");

 cudaEventRecord(start);
 transpose_coalesced<<<blocks,threads>>>(d_in,d_out);
 cudaEventRecord(stop);

 cudaMemcpy(h_out2,d_out,num_bytes,cudaMemcpyDeviceToHost);
 cudaEventElapsedTime(&time, start, stop);

 printf ("Coalesced Transpose:\n");
 printf("\n");
 printf ("Time Taken: %f milliseconds\n", time);
 printf("Bandwidth: %f Gb/sec\n", (N*N*4*2*1e-6)/time);
 printf("\n");

 printf("Matrix Comparison: %s\n",compare(h_out1,h_out2) ? "Successful" : "Unsuccessful");
 printf("\n");

 /*
 printf("Matrix Transpose:\n");
 printf("\n");
 print_matrix(h_out1);
 */

 free(h_in);
 free(h_out1);
 free(h_out2);

 cudaFree(d_in);
 cudaFree(d_out);

 return 0;
}
