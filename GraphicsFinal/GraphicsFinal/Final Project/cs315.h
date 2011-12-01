// cs315.h
// 
// CS315 2010 Support Include
// This file includes the needed files to support OpenGL in Visual C++, Linux, and OS X.
// It also declares utility code for CS315 like the getTime() function.
//
#ifndef CS_315
#define CS_315

#ifdef WIN32
# include <windows.h>
# include <sys/timeb.h>
#else
# include <sys/time.h>
#endif

#ifdef __APPLE__  // detect OS X
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class RGBColor {
public:
    float r,g,b;
    
    // A default constructor, makes the color white 
    RGBColor() {
        r = g = b = 1.0; 
    }
    RGBColor(const float& r, const float& g, const float& b) {
        this->r = r; this->g = g; this->b = b;
    }
};


// CS315 class (to encapsulate utility functions)
class CS315 {
public:
    // Get the global time in seconds with at least millisecond resolution.
    static double getTime(void);
    
    // Specify seed for random number generator
    static void RandSeed(int s);
    
    // Get random number between 0 and n - 1 (inclusive)
    static int RandInt(int n = RAND_MAX + 1);
    
    // Get floating point random numbers between 0.0 and 1.0
    static float RandFloat(void) { return (float)RandDouble(); }
    static double RandDouble(void);
    
private:
    // Random number initialization
    static int bRandInit;
};

#endif
