//
//  Surface.h
//  Final Project


#ifndef Final_Project_Surface_h
#define Final_Project_Surface_h

#include "cs315.h"
#include "MaterialInfo.h"

class Surface {
    
public:
    
    Surface();
    virtual ~Surface();
    MaterialInfo material;
    
    GLuint getDisplayList();
    GLuint getDisplayList2();
	//GLdouble getBoundries();
    
    GLuint fieldd;
    GLuint back;
    
    
    
private:

    
};

#endif
