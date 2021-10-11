## Using CUDA library from OpenMP code

The provided code [pi.c](pi.c) calculates approximate value for
pi by generating random numbers within a square and calculating how
many of them falls within a unit circle.

The code uses `curand` library for generating random numbers. Add appropriate
OpenMP constructs according the TODOs in the code. You can compile the code
in Mahti with the provided Makefile by typing `make`. 
