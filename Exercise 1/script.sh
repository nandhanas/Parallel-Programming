#!/bin/bash
for n in 1 2 4 8 16 20
do
  set OMP_NUM_THREADS = $n
  ./parallel
done
