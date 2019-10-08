#!/bin/bash
for n in 1 2 4 8 16 20
do
  mpirun -np $n main
done
