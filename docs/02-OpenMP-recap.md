---
title:  "Recap: OpenMP"
author: CSC Training
date:   2021-10
lang:   en
---

# Processes and threads

![](img/processes-threads.png)

<div class="column">

## Process

- Independent execution units
- Have their own state information and *own memory* address space

</div>

<div class="column">

## Thread

- A single process may contain multiple threads
- Have their own state information, but *share* the *same memory*
  address space

</div>


# Processes and threads

![](img/processes-threads.png)

<div class="column">
  
## Process

- Long-lived: spawned when parallel program started, killed when
  program is finished
- Explicit communication between processes

</div>

<div class="column">

## Thread

- Short-lived: created when entering a parallel region, destroyed
  (joined) when region ends
- Communication through shared memory

</div>


# OpenMP walkthrough {.section}

# Three components of OpenMP

- Compiler directives and constructs
    - Expresses shared memory parallelization
    - Preceded by sentinel, can compile serial version

- Runtime library routines
    - Small number of library functions
    - Can be discarded in serial version via conditional compiling

- Environment variables
    - Specify the number of threads, etc.

# OpenMP directives

- Sentinels precede each OpenMP directive
   - C/C++: `#pragma omp`
   - Fortran free form: `!$omp`

- Compilers that support OpenMP usually require an option (flag) that
  enables the feature
    - Without an enabling flag the OpenMP sentinels are treated as
      comments and a serial version will be compiled

# Parallel construct

<div class="column">

- Defines a *parallel region*
    - Prior to it only one thread, master
    - Creates a team of threads: master+slave threads
    - At end of the block is a barrier and all shared data is synchronized

```fortran
!$omp parallel

!$omp end parallel
```

</div>

<div class="column">

![](img/omp-parallel.png)

</div>

# Example: Helloworld with OpenMP

<div class="column">
```fortran
program hello
use omp_lib

integer :: omp_rank

!$omp parallel private(omp_rank)
omp_rank = omp_get_thread_num()
print *, 'Hello world! by & thread ', omp_rank
!$omp end parallel


end program hello
```

</div>
<div class="column">
```c
#include <stdio.h>
#include <omp.h>

int main(int argc, char argv[]) {
  int omp_rank;

  #pragma omp parallel private(omp_rank)
  {
  omp_rank = omp_get_thread_num();
  printf("Hello world! by thread %d", omp_rank);
  }
}
```
</div>

# Example: Helloworld with OpenMP

<div class="column">
```console
$ ifort -qopenmp omp_hello.f90 -o omp
```
</div>
<div class="column">
```console
$ icc -qopenmp omp_hello.c -o omp
```
</div>

* For other compilers: **GNU**: -fopenmp; **PGI**: -mp; **Cray**: -h omp

```console
$ export OMP_NUM_THREADS=4
$ srun --account=yourproject --ntasks=1 --cpus-per-task=4 --partition=test ./omp


Hello world! by thread 0
Hello world! by thread 2
Hello world! by thread 1
Hello world! by thread 3
```

# How do the threads interact?

- Because of the shared address space threads can "communicate" using
  *shared* variables
- Threads often need some *private* work space together with shared
  variables   
    - For example the index variable of a loop
- Visibility of different variables is defined using *data-sharing
  clauses* in the parallel region definition
    - `private`, `firstprivate`, `lastprivate`, `shared`, `default`
    - Local variables defined in the parallel region, or functions called
      within it are private

# Work sharing

- Parallel region creates an "Single Program Multiple Data" instance where
  each thread executes the same code
- How can one split the work between the threads of a parallel region?
    - Loop construct
    - Single/Master construct
    - Sections

# Loop constructs

- Directive instructing compiler to share the work of a loop
    - Fortran: `$OMP DO`
    - C/C++: `#pragma omp for`
    - Directive must be inside a parallel region
    - Can also be combined with parallel:
        - `$OMP PARALLEL DO`
        - `#pragma omp parallel for`
- Loop index is private by default
- Work sharing can be controlled using *schedule* clause
    - `static`, `dynamic`, `guided`, or `runtime`

# Reduction clause

`reduction(operator:var_list)`
  : Performs reduction on the (scalar) variables in list (sum, max, min,
    ...)

      - Private reduction variable is created for each thread's partial
        result
      - Private reduction variable is initialized to operator's initial
        value, e.g., 0 for sum
      - After parallel region the reduction operation is applied to private
        variables and **result is aggregated to the shared variable**

# Execution controls

- Sometimes a part of parallel region should be executed only by the
  master thread or by a single thread at time
    - I/O, initializations, updating global values, etc.
    - Remember the synchronization!
- OpenMP provides clauses for controlling the execution of code blocks
    - `barrier`
    - `master` & `single`
    - `critical`


# OpenMP summary

![](img/omp-summary.png)
