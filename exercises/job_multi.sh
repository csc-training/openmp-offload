#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=gpusmall
#SBATCH --reservation=openmp_offload
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --gres=gpu:a100:2

srun my_exe
