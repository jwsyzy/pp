OBJS=matrix_blas.o matrix_class.o timer.o
OBJS2=matrix_diag.o matrix_class.o timer.o

CXX=g++
OPTIONS=-O3


# matrix_blas.exe: $(OBJS)
# 	$(CXX)  -o matrix_blas.exe $(OBJS) -L/home/jwsyzy/software/lapack-3.10.1 -lcblas -lrefblas -lm -lgfortran
matrix_diag.exe: $(OBJS2)
	$(CXX)  -o matrix_diag.exe $(OBJS2)  -llapack -llapacke -lopenblas
#-L/home/jwsyzy/software/OpenBLAS_develop -L/home/jwsyzy/software/lapack-3.10.1
%.o: %.cpp %.h
	$(CXX)  -c $< -o $@

clean:
	rm $(OBJS) matrix_blas.exe