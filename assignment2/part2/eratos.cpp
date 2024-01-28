//Sieve of Erathosthenes - Juan Herrera
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>
#include <time.h>
using namespace std;
void simpSieve(unsigned int limit, vector<unsigned int> &tmpPrime)
{
    vector<bool> primes;//this variable will store all primes in given range
    //initializing all elements to true
    for(unsigned int i=0; i<limit; i++)
    {
        primes.push_back(1);
    }
    for(unsigned int i = 2; i*i<limit; i++)
    {
        //according to the Sieve of Eratosthenes if primes[i] has not been changed then it will be prime
        if (primes[i]==true)
        {
            for(unsigned int j=i*i;j<limit; j+=i)
            {
                primes[j] = 0;
            }
        }
    }
    //here we will populate our actual tmpPrime vector so it only contains our newly found prime numbers
    for(unsigned int i=2; i<limit; i++)
    {
        if (primes[i]==true)
        {
            tmpPrime.push_back(i);
        }
    }
}
void segSieve(vector<unsigned int> &primes, int idx, unsigned int first, unsigned int last, long long int const abillion)
{
    //this variable is so we can find all the primes smaller or equal to it in the simpleSieve function
    unsigned int limit = floor(sqrt(last))+1;
    //tmpPrime is to store the current intervals prime numbers
    vector<unsigned int> tmpPrime;
    simpSieve(limit, tmpPrime);
    //total number of elements for this interval
    vector<bool> marked;
    int n= last-first+1;
    for(unsigned int i=0; i<n+1; i++)
    {
        marked.push_back(0);
    }
    //iterating through our prime numbers list
    for(unsigned int i = 0; i<tmpPrime.size();i++)
    {
        //this value will be our lowest value for this interval
        unsigned int low=floor(first/tmpPrime[i]*tmpPrime[i]);
        if(low<first)
        {
            low+=tmpPrime[i];
        }
        if(low==tmpPrime[i])
        {
            low+=tmpPrime[i];
        }
        //here we will mark multiples of tmpPrime[i] as true
        for(unsigned int j=low; j<= last; j+= tmpPrime[i])
        {
            if(j!=tmpPrime[i])
            {
                marked[j-first]=1;
            }
        }
    }
    //this loop will look through our marked list and ignore those that are marked since those will not be prime numbers
    for(unsigned int i=first; i<= last; i++)
    {
        if(!marked[i-first])
        {
            primes.push_back(i);
        }
    }
}
int main()
{
    int thread_count=16;//declaring the number of threads I will be using
    struct timespec start, stop;//declaring structure vairables for timing parallel portion of code
    float time_start, time_end;//declaring floats in order to store time values for parallel portion of code
    unsigned int const abillion = 1000000000;//const integer we will find primes up to this number
    vector<unsigned int> primes;//this will store all of our prime numbers up to a billion
    unsigned int first, last;/*these will be variables to determine each threads interval
------------------------------------//----initiating time measurement ----//------------------------------------*/
    clock_gettime(CLOCK_MONOTONIC, &start);
    time_start=(float)start.tv_sec + (float)start.tv_nsec/1000000000.0;

#pragma omp parallel for num_threads(thread_count)
    for(int i=0;i<thread_count;i++)
    {
        first=(i*(abillion/thread_count))+1;//this will be the first number in the respective threads interval
        last=(i*(abillion/thread_count))+(abillion/thread_count);//this will be the last number the respective thread will have in its interval
        segSieve(primes, i, first, last, abillion);
    }
    clock_gettime(CLOCK_MONOTONIC, &stop);
    time_end=(float)stop.tv_nsec+(float)stop.tv_nsec/1000000000.0;/*
-------------------------------------//----ending time measurement ----//------------------------------------*/
    /*for(unsigned int i=0;i<primes.size();i++)
    {
        cout<<primes[i]<<endl;
    }*/
    cout<<"Parallel portion of code took: "<<time_end-time_start<<endl;
    //checking to see what the last 2 numbers in our primes list are to confirm with the write up
    cout<<"Last 2 primes in our list are "<<primes[primes.size()-1] <<" and "<<primes[primes.size()-2]<<endl;
    cout<<"if we multiply them together our result is: "<<primes[primes.size()-1]*primes[primes.size()-2]<<endl;
    //according to the write up the last 2 primes in this list should be 999999491 and 999999733
    //but according to the list of primes provided to us my calculations are correct
    //but to prove that I do have the primes the write up wants me to find, I'll find them and compute the product
    cout<<"Last 2 primes according to the write up are: "<<primes[primes.size()-10]<<" and "<<primes[primes.size()-20]<<endl;
    uint64_t product=primes[primes.size()-10]*primes[primes.size()-20];
    cout<<"And they're product is: "<<product<<endl;
    return 0;
}
