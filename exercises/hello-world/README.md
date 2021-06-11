# Hello world with OpenMP offloading

Compile and run a simple OpenACC test program, provided as `hello(.c|.F90)`.

In order to compile the program on Puhti, you'll need to first load the ...

On Grenoble node:

export PATH=/opt/rocm-4.1.0/llvm/bin:$PATH

clang++ -O3 -std=c++11 hello.c -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx908  
