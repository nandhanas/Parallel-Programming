## Exercise 1 : OpenMP PI Approximation

* serial.c : Serial execution of PI Approximation

  * gcc -o serial serial.c
  * ./serial

* parallel.c : OpenMP execution of PI Approximation

  * gcc -fopenmp -o parallel parallel.c
  * Reduction section : ./parallel
  * Critical section :  ./parallel 1
  * Atomic section :  ./parallel 2

* script.sh should be changed accordingly
