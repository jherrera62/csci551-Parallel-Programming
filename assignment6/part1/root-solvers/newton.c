// https://www.codewithc.com/c-program-for-newton-raphson-method/
//
// Refactored to improve variable names and commenting
//
// Sam Siewert, 4/26/2022
//
// For theory overview, start with Wikipedia - https://en.wikipedia.org/wiki/Newton's_method
//
// Draw some examples and convince yourself that the slope of the tangent (derviative of the function) at x, 
// helps with the search for the ZERO crossing, which is a root of the function.
//
#include<stdio.h>
#include<math.h>
#include <time.h>

// model a function with desmos for example to "see" roots
// 
// https://www.desmos.com/calculator
double f(double x)
{
    return (0-pow(x,3)+(9.7*pow(x,2))-1.2*x-105.7);
}

double df (double x)
{
    return(0-3*pow(x,2)+19.4*x-1.3);
}

int main(void)
{
    int itr, maxmitr;
    double h, x0, x1, allerr, x0sav;
    struct timespec start, end;
    double fstart = 0.0, fend = 0.0;

    printf("\nEnter x0, allowed error and maximum iterations\n");
    scanf("%lf %lf %d", &x0, &allerr, &maxmitr);
    x0sav = x0;
    printf("x0=%lf, err=%lf, max iter=%d\n", x0, allerr, maxmitr);
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (itr=1; itr<=maxmitr; itr++)
    {
        // Taking the slope at current guess of x0, we look for a step, h, where f(x1)=0
        //
        // Since SLOPE at x0, or df(x0) = [f(x0) - f(x1)] / [x0 - x1] or rise/run and f(x1)=0, where
        // the TANGENT SLOPE INTERSECTS the X axis, we know
        //
        // df(x0) = [f(x0) - 0] / [x0 - x1]
        //
        // df(x0) * [x0 - x1] = f(x0)
        //
        // Note that h is x0 - x1, the step
        //
        // So, h = f(x0) / df(x0)
        //
        h=f(x0)/df(x0);

        // Compute next guess based on x0 based on h = x0 - x1
        x1=x0-h;

        printf(" At Iteration no. %3d, x = %9.6f\n", itr, x1);

        // Error is simply the absolut difference between x0 and x1 and with convergence, x0 and x1 eventually
        // become the same within our tolerance and we quit.
        if (fabs(h) < allerr)
        {
            clock_gettime(CLOCK_MONOTONIC, &end);
            fstart = start.tv_sec + (start.tv_nsec / 1000000000.0);
            fend = end.tv_sec + (end.tv_nsec / 1000000000.0);
            printf("After %3d iterations, root = %20.15f\n", itr, x1);

            // Quit when we find a root that meets error tolerance
            printf("\n Total time: %lf seconds\n", (fend - fstart));
            return 0;
        }

        x0=x1;

    }

    // If we did not achieve our error tolerance before max iterations, indicate potential failure
    printf("x0=%lf, err=%lf, max iter=%d\n", x0sav, allerr, maxmitr);
    printf(" The required solution does not converge or iterations are insufficient\n");
    return 1;
}
