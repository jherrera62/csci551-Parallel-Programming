INCLUDE_DIRS = 
LIB_DIRS = 
CC=g++

CDEFS=
CFLAGS= -O0 -fopenmp $(INCLUDE_DIRS) $(CDEFS) -lm
#CFLAGS= -O0 -g -pg $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= rotation omp_rotation
SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: rotation omp_rotation

clean:
	-rm -f *.o *.d
	-rm -f rotation omp_rotation

distclean:
	-rm -f *.o *.d
	-rm -f rotation omp_rotation

rotation: rotation.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o -lstdc++fs
omp_rotation: omp_rotation.o
	g++ -fopenmp omp_rotation.cpp -o omp_rotation -lm -lstdc++fs



depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
