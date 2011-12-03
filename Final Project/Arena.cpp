//
//  Arena.cpp
//  Final Project
//
//  Created by Nick Burns and Ian Earle and Jacob Fuhrman yeah! on 11/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Arena.h"
#include "OpenGLContainer.h"
#include "Rectangular.h"
#include "RigidBody.h"
#include "cs315.h"

#include <vector>
#include <math.h>
using namespace std;


//method responsible for updating the position/state of each object, based on elapsed time
void Arena::update(GLdouble dTime){
    GLdouble x;
    GLdouble y;
    GLdouble w;
    GLdouble h;
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        Sphere* currentBody = rigidBodies[i];
        RigidBody* rigid = currentBody;
        currentBody->updateState(dTime);
        x = rigid->getXPosition();
        y = rigid->getYPosition();
        w = surface->getWidth()/2.0;
        h = surface->getWidth()/2.0;
        if (x >= h || x <= -h) {
            currentBody->bounceSide();
        }
        if (y >= w || y <= -h) {
            currentBody->bounceTopOrBottom();
        }
        
    }
    
}

//draws all objects, with their current position
void Arena::draw(){
    instance->setMaterial(surface->getMat());
    glCallList(surface->getDisplayList());
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        RigidBody* currentBody = rigidBodies[i];
        glPushMatrix();
        instance->setMaterial(currentBody->getMaterial());
        glTranslated(currentBody->getXPosition(), 0, currentBody->getYPosition());
        glCallList(currentBody->getDisplayList());
        glPopMatrix();
    }
    
}

//constructor
//makes a new surface to play on
//adds spheres to be drawn
Arena::Arena(GLuint numSpheres){
    surface = new Rectangular(80,52,MAT_GRAY);

    
    rigidBodies.reserve(numSpheres);
    for (GLuint i = 0; i<numSpheres; i++) {
        rigidBodies.push_back(new Sphere(0,0,10,15,1,MAT_BLUE));
        rigidBodies.push_back(new Sphere(2,2,5,2,1,MAT_RED));
        rigidBodies.push_back(new Sphere(3,3,7,8.68,.75,MAT_GREEN));
        rigidBodies.push_back(new Sphere(0,0,rand() % 20,rand() % 20,1,MAT_YELLOW));
        rigidBodies.push_back(new Sphere(rand() % 20,rand() % 20,rand() % 20,2,1,MAT_RED));
        rigidBodies.push_back(new Sphere(rand() % 20,rand() % 20,7,8.68,.75,MAT_GREEN));
    }
}

//nothing
Arena::~Arena(){
    
}