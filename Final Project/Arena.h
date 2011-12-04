//
//  Arena.h


#ifndef Final_Project_Arena_h
#define Final_Project_Arena_h

#include "RigidBody.h"
#include "cs315.h"
#include "MaterialInfo.h"
#include "Sphere.h"
#include "Surface.h"
#include "Rectangular.h"

#include <vector>

class Arena{

private:
    Rectangular* surface;
    vector<Sphere*> rigidBodies;
    GLdouble xOffset;
    GLdouble yOffset;
    
public:
    void update(GLdouble dTime);
    void draw();
    

    
    void addRigidBody(RigidBody body);
    
    Arena();
    virtual ~Arena();
};

#endif
