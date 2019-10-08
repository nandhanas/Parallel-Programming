## Exercise 6 : CUDA Matrix Transpose

* main.c :

  * qsub -q reserved2 -l walltime=10:00:00,nodes=1:ppn=20 -I
  * module load cudatoolkit/10.0
  * nvcc -o main main.c
  * ./main
