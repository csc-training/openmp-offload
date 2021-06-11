#include <stdio.h>

#ifdef _OPENMP
#include <omp.h>
#endif

/*
• Device Runtime Support:
•  To query the target environment
omp_get_default_device
omp_get_initial_device
omp_get_num_devices
omp_get_num_teams
omp_get_team_num
omp_is_initial_device
omp_set_default_device
•  To manage device memory
omp_target_alloc
omp_target_associate_ptr
omp_target_disassociate_ptr
omp_target_free
omp_target_is_present
omp_target_memcpy

printf("%d %d %d %d %d. There are %d devices.  %d %d \n", omp_get_num_teams(), omp_get_team_num(), omp_is_initial_device(), omp_get_num_threads(), omp_get_num_devices(), omp_get_default_device(), omp_get_device_num());
*/

int main(void) {
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

  return 0;
}
