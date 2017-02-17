//*********************************************************************
// File:big_primes.cc
// Author: David W. Juedes
// Date: January 19, 2017
// Purpose: Reads as input a number n (from the standard input) and outputs
// the nth prime number.
//*************************************************************************
#include <iostream>
//#include <omp.h>
#include <cmath>
using namespace std;
#pragma omp parallel
int p_num = omp_get_num_thread();
//*************************************************************
//Function: IsPrime
//Purpose: Determines whether x is a prime number by examining all
//integers i < sqrt(x).
//******************************************************************
//calculate how many primes are in some range
//take all threads and have them try some numbers
//each one wll count how many prime numbers they found then add them all up
//split up the work
bool IsPrime(long long x) {
    long long count = 0;
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
// Function: Count(prime)
// Purpose: Counts the number of prime numbers in a range.
//************************************************************************
//how many primes to the lower bound to find the xth prime in the small region
long long Count(long long prime) {
    long count = 0;
#pragma omp parallel for
    for(int i = 2; i < prime; ++i)
    {
        if(IsPrime(i))
        {
            count++;
        }
    }
    return count;
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
    long long count = 0;
    long long n;
    cin >> n;
    long long next_p = 2;
    long long get_prime_num = 0;
#pragma omp parallel for
    for (long long j=1;j<n;j++) {
        next_p = NextPrime(next_p);
        count = Count(next_p);
        cout<<"There are "<< count << " primes in the range from 0 to "<< next_p<<endl;
        
    }
    
    cout << "The " << n << "th prime " << " is " << next_p << endl;
    // cout << "Notice that this is less than " << n*(log(n))+n*(log(log(n)))+2*n << endl;
}
