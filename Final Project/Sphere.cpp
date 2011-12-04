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


void Sphere::bounceSide(GLdouble correctPosition){
    xVel = -xVel;
    xPos = correctPosition;
}

void Sphere::bounceTopOrBottom(GLdouble correctPosition){
    yVel = -yVel;
    yPos = correctPosition;
}

void Sphere::bounceSphere(Sphere& otherSphere){
    
}

void Sphere::checkCollision(Sphere &otherSphere){

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
    glutSolidSphere(size, 80, 80);
    glEndList();
    
}
Sphere::~Sphere(){
    glDeleteLists(shape, 1);
}