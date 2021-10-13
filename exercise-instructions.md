# General exercise instructions

For most of the exercises, skeleton codes are provided both for
Fortran and C/C++ in the corresponding subdirectory. Some exercise
skeletons have sections marked with “TODO” for completing the
exercises. In addition, all of the 
exercises have exemplary full codes (that can be compiled and run) in the
`solutions` folder. Note that these are seldom the only or even the best way to
solve the problem.

The exercise material can be downloaded with the command

```
git clone https://github.com/csc-training/openmp-offload.git
```

If you have a GitHub account you can also **Fork** this repository and clone then your fork.

## Computing servers

Exercises can be carried out using the CSC's Mahti supercomputer. 
See [CSC User Documentation](https://docs.csc.fi/support/tutorials/mahti_quick/) for general instructions on using Mahti.


Mahti can be accessed via ssh using the
provided username (`trainingxxx`) and password:
```
ssh -Y training000@mahti.csc.fi
```


For editing program source files you can use e.g. *nano* editor: 

```
nano prog.f90 &
```
(`^` in nano's shortcuts refer to **Ctrl** key, *i.e.* in order to save file and exit editor press `Ctrl+X`)
Also other popular editors (emacs, vim, gedit) are available.

## Disk areas

All the exercises in the supercomputers should be carried out in the
**scratch** disk area. The name of the scratch directory can be
queried with the command `csc-workspaces`. As the base directory is
shared between members of the project, you should create your own
directory:
```
cd /scratch/project_2000745
mkdir -p $USER
cd $USER
```


## Compilation

Programs with OpenMP offloading can be build in Mahti with [NVIDIA HPC
Toolkit](https://docs.nvidia.com/hpc-sdk/index.html). The compiler
environment is enabled via module system:
```bash
module load nvhpc openmpi/4.0.5-cuda
```
The compiler commands (without MPI) for C, C++ and Fortran are `nvc`,
`nvc++`, and `nvfortran`, and OpenMP offload support is enabled with
`-mp=gpu -gpu=cc80` options, *i.e.*

```
nvc -o my_exe test.c -mp=gpu -gpu=cc80
```
or
```
nvc++ -o my_exe test.cpp -mp=gpu -gpu=cc80
```
or
```
nvfortran -o my_exe test.f90 -mp=gpu -gpu=cc80
```


For MPI codes, use the wrapper commands `mpicc`, `mpic++`, or `mpif90`

## Running in Mahti

In Mahti, programs need to be executed via the batch job system. The
number of nodes is specified with `--nodes` (for most of the exercises
you should use only a single node), number of MPI tasks **per node**
with `--ntasks-per-node` (for exercises with single GPU this should be
one), and the number of GPUs per node with `--gres=gpu:a100:n`. If
program uses OpenMP with CPUs
number of cores reserved for threading is set with `--cpus-per-task`. The
actual number of threads is specified with `OMP_NUM_THREADS`
environment variable. Simple job running with single GPU can be
submitted with the following batch job script: 
```
#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=gpusmall
#SBATCH --reservation=openmp_offload
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --gres=gpu:a100:1

srun my_exe
```

Save the script *e.g.* as `job.sh` and submit it with `sbatch job.sh`. The [exercises](exercises) 
directory contains additional job script templates (`job_xxx.sh`).
The output of job will be in file `slurm-xxxxx.out`. You can check the status of your jobs with `squeue -u $USER` and kill possible hanging applications with
`scancel JOBID`.

The reservation `openmp_offload` is available during the course days and it
is accessible only with the training user accounts.

## Profiling with NVIDIA Nsight Systems

[NVIDIA Nsight Systems](https://docs.nvidia.com/nsight-systems/index.html) 
can be used for profiling the code in Mahti. First, one should collect a
trace of application run with `nsys` command:
```
...
#SBATCH --gres=gpu:a100:1

srun nsys profile -t cuda,openmp ./my_exe
```

After a succesfull trace collection, data is written into file
`reportN.qdstrm`. The trace can then be analyzed with GUI.

First, `PATH` needs to be set:
```
export PATH=$PATH:/appl/spack/v016/install-tree/gcc-4.8.5/nvhpc-21.2-l6xyb4/Linux_x86_64/21.2/profilers/Nsight_Systems/bin
```

Then, one can start the GUI with the `nsys-ui` command and import the
`reportN.qdstrm` file via **File** -> **Import...** dialog.

GUI converts `reportN.qdstrm` to ``reportN.qdrep` and summary
statistics can then be investigated also from command line:

Or An alternative way is to use *QdstrmImporter* which extracts events data from .qdrsm files to qdrep for which we can then visualize using nsys cli tools. 

You can run : 
``` sh 
/appl/spack/v016/install-tree/gcc-4.8.5/nvhpc-21.2-l6xyb4/Linux_x86_64/21.2/profilers/Nsight_Systems/host-linux-x64/QdstrmImporter -i report.qdstrm -o reportN

```
> Note the above command is only applicable to CSC's mahti clusters. You may wish to locate the path of QdstrmImporter from you installation.

```
rm reportN.sqlite  # In Mahti a zero size file is generated
nsys stats reportN.qdrep
```
 



