//
//  RigidBody.h


#include "Sphere.h"

#include <iostream>

using namespace std;

void Sphere::printState(){
    cout << "Position (" << xPos << ","<< yPos << ")   Velcoity (" << xVel << "," << yVel << ")"<<endl;
}

void Sphere::updateState(GLdouble dTime){
    xPos += xVel * dTime;
    yPos += yVel * dTime;
}

void Sphere::setMaterial(MaterialInfo mat){
    material = mat;
}

void Sphere::bounceSide(){
    //xPos -= xVel*UNSTICK_TIME;
    xVel = -xVel;
    

    
}

void Sphere::bounceTopOrBottom(){
    //yPos -= yVel*UNSTICK_TIME;
    yVel = -yVel;


    
}

// U - velocity before
// V - velocity after
// X - x component of velocity vector
// Y - y component of velocity vector(actually z on screen, y used only for ease)
// M - "mass" caluclated from volume of a sphere given the radius
// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
// Calculates new velocity for each component
void Sphere::bounceSphere(Sphere* otherSphere){
    GLdouble thisVX, thisVY, thisUX, thisUY;
    GLdouble otherVX, otherVY, otherUX, otherUY;
    GLdouble thisM, otherM, totM, thisMdiff, otherMdiff;
    
    thisUX = this->xVel;
    thisUY = this->yVel;
    otherUX = otherSphere->xVel;
    otherUY = otherSphere->yVel;
    thisM = (this->size)*(this->size)*(this->size)*VOLUME_FACTOR;
    otherM = (otherSphere->size)*(otherSphere->size)*(otherSphere->size)*VOLUME_FACTOR;
    
    totM = thisM + otherM;
    thisMdiff = thisM - otherM;
    otherMdiff = otherM - thisM;
    
    thisVX = (thisUX*thisMdiff+2*otherM*otherUX)/(totM);
    thisVY = (thisUY*thisMdiff+2*otherM*otherUY)/(totM);
    
    otherVX = (otherUX*otherMdiff+2*thisM*thisUX)/(totM);
    otherVY = (otherUY*otherMdiff+2*thisM*thisUY)/(totM);
    
    this->xVel = thisVX;
    this->yVel = thisVY;
    
    otherSphere->xVel = otherVX;
    otherSphere->yVel = otherVY;
    
//    this->xPos += thisUX * UNSTICK_TIME;
//    this->yPos += thisUY * UNSTICK_TIME;
//    otherSphere->xPos += otherUX * UNSTICK_TIME;
//    otherSphere->yPos += otherUY * UNSTICK_TIME;
;
    
}

GLboolean Sphere::checkCollision(Sphere* otherSphere){
    GLdouble thisXPos = this->xPos;
    GLdouble thisYPos = this->yPos;
    GLdouble otherXPos = otherSphere->xPos;
    GLdouble otherYpos = otherSphere->yPos;
    GLdouble distance = (thisXPos-otherXPos)*(thisXPos-otherXPos) + (thisYPos-otherYpos)*(thisYPos-otherYpos);
    GLdouble minAllowedDistance = (this->size)*(this->size) + (otherSphere->size)*(otherSphere->size);
    if ( (distance <  minAllowedDistance) ) {
        return true;
    } else 
        return false;
}

GLdouble Sphere::getSize(){
    return size;
}


Sphere::Sphere(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat){
    xPos = xPositionInit;
    yPos = yPositionInit;
    xVel = xVelocity;
    yVel = yVelocity;
    size = radius;
    material = mat;
    
    shape = glGenLists(1);
    glNewList(shape,GL_COMPILE);
    setMaterial(material);
    glutWireSphere(size, 4, 5);
    glEndList();
    
}

Sphere::~Sphere(){
    glDeleteLists(shape, 1);
}