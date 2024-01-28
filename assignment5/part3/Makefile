INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
CC = mpicc
CXX = mpicxx

CDEFS=
CFLAGS= -g -Wall -fopenmp $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=matrix_mult omp_matrix_mult

HFILES=
CFILES= matrix_mult omp_matrix_mult

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

matrix_mult:	matrix_mult
	$(CC) $(CFLAGS) -o $@ matrix_mult.c $(LIB_DIRS)
omp_matrix_mult:	omp_matrix_mult
	$(CC) $(CFLAGS) -o $@ omp_matrix_mult.c $(LIB_DIRS)

