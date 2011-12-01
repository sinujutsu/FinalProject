//
//  RigidBody.cpp
//  Final Project
//
//  Created by Nick Burns on 11/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "RigidBody.h"
#include "cs315.h"

#include <iostream>

RigidBody::RigidBody(){
    
}
RigidBody::~RigidBody(){
    
}

GLdouble RigidBody::getXPosition(){
    return xPos;
}
GLdouble RigidBody::getYPosition(){
    return yPos;
}

GLuint RigidBody::getDisplayList(){
    return shape;
}

void RigidBody::printState(){
    
}
void RigidBody::updateState(GLdouble dTime){
    
}
void RigidBody::setMaterial(){
    
}