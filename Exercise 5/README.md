## Exercise 5 : MPI Ring Communication

* main.c : Ring Communication using Process Id

  * module load openmpi
  * mpicc -o main main.c
  * mpirun -np 4 main

  * vector_sum.c : Ring Communication using Matrix of Size N

    * module load openmpi
    * mpicc -o vector_sum vector_sum.c
    * mpirun -np 4 vector_sum N
