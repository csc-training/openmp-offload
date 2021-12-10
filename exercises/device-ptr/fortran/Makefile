CURAND_DIR=/appl/spack/v016/install-tree/gcc-4.8.5/nvhpc-21.2-l6xyb4/Linux_x86_64/21.2/math_libs/
FCFLAGS=-mp=gpu -gpu=cc80
FC=nvfortran

OBJS=pi.o curand.o
pi: $(OBJS)
	$(FC) -o $@ $(OBJS) $(FCFLAGS) -L$(CURAND_DIR)/lib64 -rpath=$(CURAND_DIR)/lib64 -lcurand 

%.o: %.F90
	$(FC) $(FCFLAGS) -c $< -o $@
clean:
	rm -f pi *.o *.mod
