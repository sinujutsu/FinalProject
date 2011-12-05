//
//  Sphere.h


// What the hell do these ifs do? Why won't my PlayerObject class
// work without them, exactly? --Jake
#ifndef Final_Project_Sphere_h
#define Final_Project_Sphere_h

#include "RigidBody.h"


//a specfic example of a rigidbody, extends rigidbody
//can have its state updated
//can be given a new velocity vector
class Sphere : public RigidBody {
protected:
    GLdouble xVel;
    GLdouble yVel;
    
public:
    void printState();
    void updateState(GLdouble dTime);
    void setMaterial(MaterialInfo mat); 
    void bounceTopOrBottom(GLdouble correctPosition);
    void bounceSide(GLdouble correctPosition);
    void bounceSphere(Sphere* otherSphere);
    GLboolean checkCollision(Sphere* otherSphere);
    
    GLdouble getSize();
    GLdouble getXPosition();
    GLdouble getYPosition();
    GLuint getDisplayList();
    
    Sphere(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat);
    virtual ~Sphere();
};
#endif
static const GLdouble VOLUME_FACTOR = (4.00/3.00) * 3.141593;
