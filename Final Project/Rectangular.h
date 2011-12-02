//  
//  Rectangluar.h
//  Final Project


#ifndef Final_Project_Rectangluar_h
#define Final_Project_Rectangluar_h
#include "Surface.h"
#include "cs315.h"

class Rectangular : public Surface{
public:
    Rectangular(GLdouble height, GLdouble width);
    virtual~Rectangular();
    
    GLdouble getHeight();
    GLdouble getWidth();
    
protected:
    GLdouble h;
    GLdouble w;
};


#endif
