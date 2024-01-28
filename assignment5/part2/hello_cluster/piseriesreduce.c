#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sched.h>
#include <omp.h>
#include <time.h>
// The 2 series used for computation of pi are documented well by Wikipedia
//
// https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80
//
// The first series is simply 1 - 1/3 + 1/5 - 1/7 + 1/9 - ... = pi/4
//
// The second series is the summation of 2 / ((4n+1)(4n+3)) for n=0 to infinity
//

int main(int argc, char** argv)
{
  int idx, thread_count ;
  double euler_local_sum=0.0, euler_g_sum=0.0;
  double local_sum=0.0, g_sum=0.0, local_num=1.0;
  unsigned int length;
  unsigned int sub_length;
  struct timespec start, end;
  double fstart = 0.0, fend = 0.0;

  if(argc < 2)
  {
    printf("usage: piseriesreduce <series n> <thread_count>\n");
    exit(-1);
  }
  else
  {
    sscanf(argv[1], "%u", &length);
    sscanf(argv[2], "%i", &thread_count);
  }

  sub_length = length/thread_count;


  printf("thread_count=%d, length=%u, sub_length=%u\n", thread_count, length, sub_length);
  clock_gettime(CLOCK_MONOTONIC, &start);
  // sum the sub-series for the rank for Leibniz's formula for pi/4
#pragma omp parallel for num_threads(thread_count) private(idx) shared(length)
  for(idx=0; idx<length; idx++)
  {
    local_sum += local_num / ((2.0 * (double)idx) + 1.0);
    local_num = -local_num;
  } 


  // sum the sub-series for the rank for Euler improved convergence of the Madhava-Leibniz's formula for pi/4
#pragma omp parallel for num_threads(thread_count) private(idx) shared(length)
  for(idx =0; idx<length; idx++)
  {
    euler_local_sum += 2.0 / (((4.0 * (double)idx) + 1.0) * (4.0 * (double)idx + 3.0));
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  fstart = start.tv_sec + (start.tv_nsec / 1000000000.0);
  fend = end.tv_sec + (end.tv_nsec / 1000000000.0);

  // collective comm broadcast the rank 0 g_sum to all other ranks
  //MPI_Bcast(&g_sum, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  printf("Parallel Portion of Code: %lf\n", (fend - fstart));
  printf("C math library pi  =%15.14lf\n", M_PI);
  printf("Madhava-Leibniz pi =%15.14lf, ppb error=%15.14lf\n", (4.0*local_sum), 1000000000.0*(M_PI - (4.0*g_sum)));
  printf("Euler modified pi  =%15.14lf, ppb error=%15.14lf\n", (4.0*euler_local_sum), 1000000000.0*(M_PI - (4.0*euler_g_sum)));


  return 0;
}
