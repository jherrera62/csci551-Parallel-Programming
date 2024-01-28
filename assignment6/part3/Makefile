INCLUDE_DIRS = 
LIB_DIRS = 
CC=g++

CDEFS=
CFLAGS= -O0 -fopenmp $(INCLUDE_DIRS) $(CDEFS) -lm
#CFLAGS= -O0 -g -pg $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= train6 train6_omp
SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all: train6 train6_omp

clean:
	-rm -f *.o *.d
	-rm -f train6 train6_omp

distclean:
	-rm -f *.o *.d
	-rm -f train6 train6_omp

train6: train6.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o
train6_omp: train6_omp.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o


depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
