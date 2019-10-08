## Exercise 4 : MPI Identity Matrix

* main.c :

  * module load openmpi
  * mpicc -o main main.c
  * Non-Blocking Communication (Matrix size N): mpirun -np 4 main N
  * Blocking Communication (Matrix size N): mpirun -np 4 main N 1
