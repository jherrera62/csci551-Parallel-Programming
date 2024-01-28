//original code is from https://rosettacode.org/wiki/Roots_of_a_function#C++ 
#include <iostream>
#include <math.h>
int thread_count=4;
double f(double x)
{
	return (cos(x*x));
}

int main()
{
	double step = 0.001; // Smaller step values produce more accurate and precise results
	double start = -100;//Refactored to start from -10
	double stop = 100;//Refactored to end at 10
	double value = f(start);
	double sign = (value > 0);
    int count=0;
	
	// Check for root at start
	if ( 0 == value )
		std::cout << "Root found at " << start << std::endl;

	for(double x = start + step;x <= stop;x += step)
	{
		value = f(x);
		
		if ( ( value > 0 ) != sign )
        {
            count++;//Keeps count of the roots
			// We passed a root
			// std::cout << "Root "<<count<<" found near " << x << std::endl;
        }
		else if ( 0 == value )
        {
            count++;//Keeps count of the roots
			// We hit a root
			// std::cout << "Root "<<count<<" found near " << x << std::endl;
        }
		// Update our sign
		sign = ( value > 0 );
	}
}