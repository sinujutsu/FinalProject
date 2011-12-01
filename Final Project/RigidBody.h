//
//  RigidBody.h


#ifndef Final_Project_RigidBody_h
#define Final_Project_RigidBody_h

#include "cs315.h"
#include "MaterialInfo.h"

#include <iostream>

using namespace std;


// A rigidbody is just an object, it has a state which can be updated
//(ex. position changing over time by velocity)
class RigidBody {
    
protected:
    GLdouble xPos;
    GLdouble yPos;
    GLdouble size;
    GLuint shape;
    MaterialInfo material;
    
public:
    void printState();
    void updateState(GLdouble dTime);
    void setMaterial();
    
    
    GLdouble getXPosition();
    GLdouble getYPosition();
    GLdouble getSize();
    GLuint getDisplayList();
    
    RigidBody();
    virtual ~RigidBody();
};
#endif
