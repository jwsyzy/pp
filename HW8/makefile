#OBJS=matrix_blas.o matrix_class.o timer.o
OBJS2=matrix_class.o timer.o matrix_diag.o 

CXX=g++
OPTIONS=-O3
LDFLAGS=-llapack -llapacke -lopenblas
CPPFLAGS=-I/home/jwsyzy/software/openmp/include

ifdef __MPI
    CXX=mpicxx
    OPTIONS+=-D__MPI
endif
# " make __MPI=1 " to compile with MPI

matrix_diag.exe: $(OBJS2)
	$(CXX)  $(OPTIONS)  $(OBJS2) $(LDFLAGS) $(CPPFLAGS) $(CFLAGS) -o matrix_diag.exe

%.o: %.cpp 
	$(CXX)  $(OPTIONS) $(CPPFLAGS) $(CFLAGS)  -c $< -o $@
# no need to add %.h, because %.o depends on %.cpp, and %.cpp includes %.h

clean:
	rm $(OBJS2) matrix_diag.exe

# matrix_blas.exe: $(OBJS)
# 	$(CXX)  -o matrix_blas.exe $(OBJS) -L/home/jwsyzy/software/lapack-3.10.1 -lcblas -lrefblas -lm -lgfortran
# matrix_diag.exe: $(OBJS2)
# 	$(CXX)  -o matrix_diag.exe $(OBJS2)  -llapack -llapacke -lopenblas
#-L/home/jwsyzy/software/OpenBLAS_develop -L/home/jwsyzy/software/lapack-3.10.1

# matrix_diag.exe: $(OBJS2)
# 	$(CXX)  -o matrix_diag.exe $(OBJS2)  -llapack -llapacke -lopenblas


