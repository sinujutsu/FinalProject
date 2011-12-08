 //
//  Sphere.h


// What the hell do these ifs do? Why won't my PlayerObject class
// work without them, exactly? --Jake
#ifndef Final_Project_Sphere_h
#define Final_Project_Sphere_h

#include "cs315.h"
#include "MaterialInfo.h"


//a specfic example of a rigidbody, extends rigidbody
//can have its state updated
//can be given a new velocity vector
class Sphere{
protected:
    GLdouble xVel;
    GLdouble yVel;
    GLdouble xPos;
    GLdouble yPos;
    GLdouble size;
    GLuint shape;
    MaterialInfo material;
public:
    GLboolean toDelete;
    void printState();
    virtual void die(GLboolean showDeath);
    virtual void updateState(GLdouble dTime); 
    virtual void bounceTopOrBottom();
    virtual void bounceSide();
    virtual void bounceSphere(Sphere* otherSphere);
    virtual GLboolean checkCollision(Sphere* otherSphere);
    
    virtual GLdouble getSize();
    virtual GLdouble getXPosition();
    virtual GLdouble getYPosition();
    virtual GLuint getDisplayList();
    virtual MaterialInfo getMaterial();
    
    Sphere(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat);
    virtual ~Sphere();
};
static const GLdouble VOLUME_FACTOR = (4.00/3.00) * 3.141593;
#endif


