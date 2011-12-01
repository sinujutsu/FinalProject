// cs315.cpp
// 
// CS315 2010 Support Code
// This file implements utility code for CS315 like the getTime() function.
//

#include "cs315.h"

#include <time.h>


// Uninitialized random numbers
int CS315::bRandInit = 0;


// Get the global time with at least millisecond resolution.
double 
CS315::getTime(void) {
#ifdef WIN32
    struct _timeb tbuf;
    _ftime(&tbuf);
    return ((double)tbuf.time + 0.001 * (double)(tbuf.millitm)); 
#else
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((double)time.tv_sec + 0.000001 * (double)time.tv_usec); 
#endif
}


// Specify seed for random number generator
void 
CS315::RandSeed(int s) {
    srand((unsigned)s);
}


// Get random number between 0 and n - 1 (inclusive)
int 
CS315::RandInt(int n) {
    if (!bRandInit) {
        srand((unsigned)time(NULL));
        bRandInit = 1;
    }
    
    // For large numbers (> 10K) this will get less random
    return rand() % n;
}


// Get floating point random numbers between 0.0 and 1.0
double 
CS315::RandDouble(void) {
    if (!bRandInit) {
        srand((unsigned)time(NULL));
        bRandInit = 1;
    }
    
    return (double)rand() / (double)RAND_MAX; 
}
