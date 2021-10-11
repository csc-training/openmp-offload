# GPU programming with OpenMP offloading

This repository containes the exercises and other course material used in
CSC's *GPU Programming with OpenMP offloading* courses. 

## Exercises

[General instructions](exercise-instructions.md)

### Introduction to parallel programming

- [Heat equation solver](exercises/heat-cpu/)

### Getting started with OpenMP offloading

- [Hello world](exercises/hello-world/)
- [Vector addition](exercises/vector-sum/)
- [Simple offloading for Laplace equation](exercises/jacobi/)

### Controlling data movement

- [Dot product](exercises/dot-product/)
- [Sum and dot product](exercises/sum-dot/)
- [Offloading the heat equation](heat-equation/README-simple.md)

### Unstructured data and device functions

- [Device functions](exercises/gpu-functions/)
- [Unstructured data in heat equation](heat-equation/README-unstructured.md)

### Interoperability with libraries and asynchronous operations

- [Using CUDA library](exercises/device-ptr)

### Using multiple GPUS

- [Multi-GPU parallelization for heat equation](heat-equation/README-multi-gpu.md)

