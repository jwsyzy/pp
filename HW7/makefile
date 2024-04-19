OBJS=test1.o
CXX=g++
OPTIONS=-O3
CPPFLAGS=-I/home/jwsyzy/software/openmp/include
ifdef __MPI
	CXX=mpicxx
	OPTIONS+=-D__MPI
endif

test1.exe: $(OBJS)
	$(CXX)  $(OPTIONS)  $(OBJS) $(CPPFLAGS) -o test1.exe

clean:
	rm $(OBJS) test1.exe