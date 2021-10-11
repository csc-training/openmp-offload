# Two dimensional heat equation with hybrid parallelization

This directory contains a working implementation of two dimensional
heat equation both in C++ and in Fortran. Code has been parallelized in a hybrid
fashion with MPI and OpenMP.

1. Read a short description about the theory and numerical implementation in this
   [accomppanying document](code-description.md).
2. Get yourself familiar with the code and basic ideas behind the parallelization.
3. Build the code with the provided Makefile (by typing `make`).
4. Try to run the code in Mahti with different parallelization options, and investigate the 
   performance. You may try also different input parameters.
