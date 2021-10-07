---
title:  "Declaring GPU functions"
author: CSC - IT Center for Science
date:   2021
lang:   en
---


# Function calls in compute regions

- Often it can be useful to call functions within loops to improve
  readability and modularisation
- By default OpenMP does not create accelerated regions for loops
  calling functions
- One has to instruct the compiler to compile a device version of the
  function


# `declare target` directive

- Define a function to be compiled for an accelerator as well as the host
- In C/C++ the one puts `declare target` and `end declare target`
  around function declarations
- In Fortran one uses `!$declare target (name)` form
- The functions will now be compiled both for host and device execution



# `declare target` directive example

<div class="column">
## C/C++
```c
#pragma omp declare target
void foo(float* v, int i, int n) {
    for ( int j=0; j<n; ++j) {
        v[i*n+j] = 1.0f/(i*j);
    }
}
#pragma omp end declare target

#pragma omp target teams loop
for (int i=0; i<n; ++i) {
    foo(v,i);  // executed on the device
}
```
</div>

<div class="column">
TODO check how it goes with Fortran!!!
## Fortran
```fortran
subroutine foo(v, i, n)
  !$acc routine vector
  real :: v(:,:)
  integer :: i, n
  !$acc loop vector
  do j=1,n
     v(i,j) = 1.0/(i*j)
  enddo
end subroutine

!$acc parallel loop
do i=1,n
  call foo(v,i,n)
enddo
!$acc end parallel loop
```
</div>


# Summary

- Declare target directive
    - Enables one to write device functions that can be called within
      parallel loops
