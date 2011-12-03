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
    surface = new Rectangular(10,10,MAT_WHITE);

    
    rigidBodies.reserve(numSpheres);
    for (GLuint i = 0; i<numSpheres; i++) {
        rigidBodies.push_back(new Sphere(0,0,100,0,1,MAT_BLUE));
        rigidBodies.push_back(new Sphere(2,2,5,2,1,MAT_RED));
    }
}

//nothing
Arena::~Arena(){
    
}