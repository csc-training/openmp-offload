# Hello world with OpenMP

On Grenoble node:

export PATH=/opt/rocm-4.1.0/llvm/bin:$PATH

clang++ -O3 -std=c++11 hello.c -fopenmp -fopenmp-targets=amdgcn-amd-amdhsa -Xopenmp-target=amdgcn-amd-amdhsa -march=gfx908  
