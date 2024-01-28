INCLUDE_DIRS = 
LIB_DIRS = 
CC=g++

CDEFS=
CFLAGS= -O0 -fopenmp $(INCLUDE_DIRS) $(CDEFS) -lm
#CFLAGS= -O0 -g -pg $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

HFILES= 
CFILES= multi_root multi_root_omp
SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	 multi_root multi_root_omp

clean:
	-rm -f *.o *.d
	-rm -f multi_root multi_root_omp

distclean:
	-rm -f *.o *.d
	-rm -f multi_root multi_root_omp

multi_root_omp: multi_root_omp.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o
multi_root: multi_root.o
	$(CC) $(LDFLAGS) -fopenmp $(CFLAGS) -o $@ $@.o

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
