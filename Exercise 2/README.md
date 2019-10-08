## Exercise 2 : OpenMP Loop Scheduling

* serial.c : Serial execution of Loop Scheduling

  * gcc -o serial serial.c
  * ./serial

* parallel.c : OpenMP execution of PI Approximation

  * gcc -fopenmp -o parallel parallel.c
  * Static scheduling (without chunk) : ./parallel static
  * Static scheduling (with chunk) : ./parallel static 10
  * Dynamic scheduling (without chunk) : ./parallel dynamic
  * Dynamic scheduling (with chunk) : ./parallel dynamic 10
