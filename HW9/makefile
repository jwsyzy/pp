
OBJS1=matrix_class.o timer.o main.o
OBJS2=matrix_class.o timer.o main_complex.o 

CXX=g++
OPTIONS=-O3
LDFLAGS=-llapack -llapacke -lopenblas
CPPFLAGS=-I/home/jwsyzy/software/openmp/include

ifdef __MPI
    CXX=mpicxx
    OPTIONS+=-D__MPI
endif
# " make __MPI=1 " to compile with MPI

# matrix_add.exe: $(OBJS1)
# 	$(CXX)  $(OPTIONS)  $(OBJS1) $(LDFLAGS) $(CPPFLAGS)  -o matrix_add.exe

complex_matrix_add.exe: $(OBJS2)
	$(CXX)  $(OPTIONS)  $(OBJS2) $(LDFLAGS) $(CPPFLAGS)  -o complex_matrix_add.exe

%.o: %.cpp 
	$(CXX)  $(OPTIONS) $(CPPFLAGS)   -c $< -o $@
# no need to add %.h, because %.o depends on %.cpp, and %.cpp includes %.h

clean:
	rm $(OBJS2) matrix_add.exe


