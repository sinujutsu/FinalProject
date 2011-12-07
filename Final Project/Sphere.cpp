//
//  RigidBody.h


#include "Sphere.h"

#include <iostream>

using namespace std;

void Sphere::printState(){
    cout << "Position (" << xPos << ","<< yPos << ")   Velcoity (" << xVel << "," << yVel << ")"<<endl;
}

void Sphere::updateState(GLdouble dTime){
    xPos += xVel * dTime/100;
    yPos += yVel * dTime/100;
}

void Sphere::setMaterial(MaterialInfo mat){
    material = mat;
}

void Sphere::bounceSide(GLdouble correctPosition){
    xVel = -xVel;
    xPos = correctPosition;
}

void Sphere::bounceTopOrBottom(GLdouble correctPosition){
    yVel = -yVel;
    yPos = correctPosition;
}

// U - velocity before
// V - velocity after
// X - x component of velocity vector
// Y - y component of velocity vector
// M - "mass" caluclated from volume of a sphere given the radius
// http://en.wikipedia.org/wiki/Elastic_collision#One-dimensional_Newtonian
//
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
    glutWireSphere(size, 40, 40);
    glEndList();
    
}

Sphere::~Sphere(){
    glDeleteLists(shape, 1);
}