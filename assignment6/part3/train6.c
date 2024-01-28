#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ex6nonlin.h"
#include "ex6lin.h"
#include <string.h>
#include <time.h>
double nonlin_accel(double time)
{
    return(NonlinProfile[(int)time]+((NonlinProfile[((int)time)+1]-NonlinProfile[(int)time])*(time-(double)((int)time))));
}
double lin_accel(double time)
{
    return(LinProfile[(int)time]+((LinProfile[((int)time)+1]-LinProfile[(int)time])*(time-(double)((int)time))));
}


int main()
{
   int size = (int)(sizeof(NonlinProfile) / sizeof(double))-1;
   int n;   
   double dt;
   dt=0.1;
   double accelarr[(int)(size/dt)];double velarr[(int)(size/dt)];double posarr[(int)(size/dt)];
   double posintersect[(int)(size/dt)];
   n=(int)size/dt;
    struct timespec start, end;
    double fstart = 0.0, fend = 0.0;

   double time;
   double cur_vel=0, cur_pos=0, cur_accel=0, max_accel, max_vel, max_pos;
   int i;
   accelarr[0]=0.0;
   velarr[0]=0.0;
   posarr[0]=0.0;
   //--------------------------TRAPEZOIDAL FOR NON LINEAR TRAIN---------------------------------//
   clock_gettime(CLOCK_MONOTONIC, &start);
   for (i = 0; i < n; i++) 
   {
      time = (double)i * dt;
      cur_accel = nonlin_accel(time);
      cur_vel = cur_vel+(cur_accel*dt);
      cur_pos = cur_pos+(cur_vel*dt);
      if(time<=n)
      {
         accelarr[i]=cur_accel;
         velarr[i]=cur_vel;
         posarr[i]=cur_pos;
         // printf("%f ",accelarr[i]);
      }
   }

    FILE *fout;
    fout = fopen("nonlinvalues.csv", "w");
    fprintf(fout, "Time, Acceleration, Velocity, Position\n");
    for (i=0; i <= n; i++)
    {
        // printf("%f ",accelarr[i]);
        fprintf(fout, "%u, %15.14f, %15.14lf, %15.14lf\n", i, accelarr[i], velarr[i], posarr[i]);
    }
    //--------------------------TRAPEZOIDAL FOR LINEAR TRAIN---------------------------------//
    cur_vel=0, cur_pos=0, cur_accel=0;
   for (;;) 
   {
        time = (double)i * dt;
        cur_accel = lin_accel(time);
        cur_vel = cur_vel+(cur_accel*dt);
        cur_pos = cur_pos+(cur_vel*dt);
        if(time<=n)
        {
            accelarr[i]=cur_accel;
            velarr[i]=cur_vel;
            if(fabs(posarr[i]-cur_pos)<10)
            {
                posintersect[i]=posarr[i];
            }
            posarr[i]=cur_pos;
            // printf("%f ",accelarr[i]);
        }
   }
    clock_gettime(CLOCK_MONOTONIC, &end);
    fstart = start.tv_sec + (start.tv_nsec / 1000000000.0);
    fend = end.tv_sec + (end.tv_nsec / 1000000000.0);
    printf("Trapezoidal sequential time = %lf\n", (fend-fstart));
    FILE *lfout;
    lfout = fopen("linvalues.csv", "w");
    fprintf(lfout, "Time, Acceleration, Velocity, Position\n");
    for (i=0; i <= n; i++)
    {
        // printf("%f ",accelarr[i]);
        fprintf(lfout, "%u, %15.14f, %15.14lf, %15.14lf\n", i, accelarr[i], velarr[i], posarr[i]);
    }
    FILE *ifout;
    ifout = fopen("posintersect.csv", "w");
    fprintf(ifout, "Time, Acceleration, Velocity, Position\n");
    for (i=0; i <= n; i++)
    {
        // printf("%f ",accelarr[i]);
        if(posintersect[i]!=0)
        {
            fprintf(ifout, "%u, %15.14lf\n", i, posintersect[i]);

        }
    }
   return 0;
}