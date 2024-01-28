INCLUDE_DIRS = -I/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/include/
LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/debug -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
#LIB_DIRS = -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib/release -L/opt/intel/compilers_and_libraries_2020.0.166/linux/mpi/intel64/lib
CC = mpicc
CXX = mpicxx

CDEFS=
CFLAGS= -g -Wall -fopenmp $(INCLUDE_DIRS) $(CDEFS)
LIBS=

PRODUCT=piseriesreduce mpipiseriesreduce

HFILES=
CFILES= piseriesreduce.c mpipiseriesreduce.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~
	-rm -f ${PRODUCT} ${DERIVED} ${GARBAGE}

piseriesreduce:	piseriesreduce.c
	$(CC) $(CFLAGS) -o $@ piseriesreduce.c $(LIB_DIRS)
mpipiseriesreduce:	mpipiseriesreduce.c
	$(CC) $(CFLAGS) -o $@ mpipiseriesreduce.c $(LIB_DIRS)

