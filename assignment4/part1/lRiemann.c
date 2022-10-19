#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ex4.h"
//#include <mpi.h>

double funct_to_integrate(double x) 
{
    return sin(x);
}
double ex4_accel(double time)
{
    // computation of time scale for 1800 seconds
    static double tscale=1800.0/(2.0*M_PI);
    // determined such that acceleration will peak to result in translation of 122,000.0 meters
    static double ascale=0.2365893166123;

    return (sin(time/tscale)*ascale);
}
// determined based on known anti-derivative of ex4_accel function
double ex4_vel(double time)
{
    // computation of time scale for 1800 seconds
    static double tscale=1800.0/(2.0*M_PI);
    // determined such that velocity will peak to result in translation of 122,000.0 meters
    static double vscale=0.2365893166123*1800.0/(2.0*M_PI);

    return ((-cos(time/tscale)+1)*vscale);
}
double ex4_pos(float time)
{
   // computation of time scale for 1800 seconds
   static float tscale = 1800.0 / (2.0 * M_PI);
   // determined such that velocity will peak to result in translation of 122,000.0 meters
   static float pscale = 0.2365893166123 * pow((1800.0 / (2.0 * M_PI)), 2);

   return ((-sin(time / tscale) + (time / tscale)) * pscale);
}
double LeftRiemann(double left_endpt, double right_endpt, int rect_count, double base_len, double dt, double *accelarr, double *velarr, double *posarr) 
{
   double time;
   double left_value, x, area=0.0; 
   double cur_accel, cur_vel, cur_pos;
   int i;
   accelarr[0]=0.0;
   velarr[0]=0.0;
   posarr[0]=0.0;

   // estimate of function on left side to forward integrate
   left_value = funct_to_integrate(left_endpt);
   x = left_endpt;

   for (i = 1; i <= rect_count-1; i++) 
   {
      time = (double)i * dt;
      cur_accel = ex4_accel(time);
      cur_vel = ex4_vel(time);
      cur_pos = ex4_pos(time);
      accelarr[i]=cur_accel;
      velarr[i]=cur_vel;
      posarr[i]=cur_pos;
      area += left_value * base_len;

      // new values to add to area
      x += base_len;
      left_value = funct_to_integrate(x);
   }

   return area;

}
int main()
{
   int size = (int)(sizeof(DefaultProfile) / sizeof(double));
   int my_rank, comm_sz, n, local_n;   
   double a, b, step_size, local_a, local_b, dt;
   double local_int_area;
   dt=0.01;
   double accelarr[(int)(size/dt)];double velarr[(int)(size/dt)];double posarr[(int)(size/dt)];
   a=0;
   b=3.14159;
   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   n=size/dt;
   step_size = (b-a)/n;  /* step is the same for all processes */
   local_n = n/comm_sz;  /* So is the number of quadratures  */

   /* Length of each process' interval of
    * integration = local_n*step_size.  So my interval
    * starts at: */
   local_a = a + my_rank*local_n*h;
   local_b = local_a + local_n*step_size;

   local_int_area = LeftRiemann(local_a, local_b, local_n, step_size, dt, accelarr, velarr, posarr);
   /* Print the result */
   printf("With n = %d quadratures, our estimate\n", n);
   printf("of the integral from %f to %f = %15.14lf\n",a, b, local_int_area/*total_int_area*/);
   MPI_Finalize();
   FILE *fout;
   fout = fopen("values.csv", "w");

   fprintf(fout, "Time, Acceleration, Velocity, Position\n");
   int i = 0;
   for (i; i <= n; i++)
   {
      fprintf(fout, "%u, %15.14lf, %15.14lf, %15.14lf\n", i, accelarr[i], velarr[i], posarr[i]);
   }
   return 0;
}