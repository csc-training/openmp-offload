#include <stdio.h>
#ifdef _OPENMP
#include <omp.h>
#endif


#define NX 102400

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    int i;
    int runningOnGPU = 0;

#ifdef _OPENMP
#pragma omp target device(0) map(from:runningOnGPU)
 {
   if (omp_is_initial_device() == 0)
     runningOnGPU = 1;
     if (runningOnGPU)
       {
         printf(" ### Able to use the GPU! ### \n Hello World!  \n ");
         printf("The default device is %d. There are %d devices available. Device %d is used.\n", omp_get_default_device(),  omp_get_num_devices(), omp_get_device_num());
       }
     else
       printf("### Unable to use the GPU, using CPU! ###\n");
 }
 #else
   printf("Code compiled without OpenMP\n");
 #endif

    /* Initialization of the vectors */
    #pragma omp target
    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

   #pragma omp target
    for (i = 0; i < NX; i++) {
        vecC[i] = vecA[i] * vecB[i];
    }

    sum = 0.0;
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    printf("Reduction sum: %18.16f\n", sum);

    return 0;
}
