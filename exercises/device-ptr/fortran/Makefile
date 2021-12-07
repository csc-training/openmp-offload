CURAND_DIR=/appl/spack/v016/install-tree/gcc-4.8.5/nvhpc-21.2-l6xyb4/Linux_x86_64/21.2/math_libs/
FCFLAGS=-mp=gpu -gpu=cc80 -cuda
FC=nvfortran

pi: pi.F90 curand.F90
	$(FC) -o $@ curand.F90 pi.F90 $(FCFLAGS) -L$(CURAND_DIR)/lib64 -rpath=$(CURAND_DIR)/lib64 -lcurand 

clean:
	rm -f pi *.o *.mod
