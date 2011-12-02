//
//  RigidBody.h


#include "Sphere.h"

#include <iostream>

using namespace std;

void Sphere::printState(){
    cout << "Position (" << xPos << ","<< yPos << ")   Velcoity (" << xVel << "," << yVel << ")"<<endl;
}
void Sphere::updateState(GLdouble dTime){
    xPos = xPos + xVel*1000000 / dTime;
    yPos = yPos + yVel*1000000 / dTime;
}
void Sphere::setMaterial(MaterialInfo mat){
    material = mat;
}

void Sphere::newVelocity(GLdouble newX, GLdouble newY){
    xVel = newX;
    yVel = newY;
}

GLdouble Sphere::getRadius(){
    return size;
}

GLdouble Sphere::getXVelocity(){
    return xVel;
}
GLdouble Sphere::getYVelocity(){
    return yVel;
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