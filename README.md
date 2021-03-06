
//*********************************************************************
// File:homework1.cpp
// Author: Gyasi Calhoun
// Date: January 26, 2017
// Purpose: Reads as input a number n (from the standard input) and outputs
// the nth prime number.
//*************************************************************************
#include <iostream>
#include <cmath>
#include <omp.h>
using namespace std;

//*************************************************************
//Function: IsPrime
//Purpose: Determines whether x is a prime number by examining all
//integers i < sqrt(x).
//******************************************************************
bool IsPrime(long long x) {
    long long i=2;
    
    while (i*i <=x) {
        if (x%i==0) {
            return false;
        }
        i++;
    }
    return true;
}
//*************************************************************************
// Function:Count(prime)
// Purpose: Counts the prime numbers
//************************************************************************
long long Count(long long prime) {
    long long next_prime;
    int n = prime;
    int count = 0;
#pragma omp parallel for reduction(+:count)
    for(int i = 2; i < n; ++i)
    {
        if(IsPrime(i))
        {
            
            count++;
        }
    }
    
    return count;
}
//*************************************************************************
// Function:NextPrime(prev)
// Purpose: Returns the next prime number larger than prev.
//************************************************************************
long long NextPrime(long long prev) {
    
    long long i;
    i=prev+1;
    while (!IsPrime(i)) {
        i++;
    }
    return i;
}
//*************************************************************************
//Function: main()
//Purpose: reads in "n", and outputs the nth prime number.
//Note: By the Rosser's theorem, the nth prime number is less than
// n log n + n log log n + 2n.
// Here, log n is natural log function.
//
//*****************************************************************************
int main() {
    long long n;
    cin >> n;
    int counter;
    long long next_p;
    long long lower_bound = (n * log(n) + (n * log(log(n))));
    lower_bound -=4*n;
    if(n <=55)
    {
        long long next_p = 2;
        for (long long j=1;j<n;j++) {
            next_p = NextPrime(next_p);
        }
        cout << "The " << n << "th prime " << " is " << next_p << endl;
    }else{
        counter = Count(lower_bound);//use to be n
        next_p = lower_bound;
        for (long long j=counter;j<n;j++) {
            next_p = NextPrime(next_p);
        }
        cout << "The " << n << "th prime " << " is " << next_p << endl;
    }
}
