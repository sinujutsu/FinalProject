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
    GLdouble x,y,w,h,r;
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        Sphere* currentBody = rigidBodies[i];
        RigidBody* rigid = currentBody;
        currentBody->updateState(dTime);
        x = rigid->getXPosition();
        y = rigid->getYPosition();
        r = currentBody->getSize();
        w = surface->getWidth()/2.0;
        h = surface->getWidth()/2.0;
        if (x+r >= h || x-r <= -h) {
            currentBody->bounceSide();
        }
        if (y+r >= w || y-r <= -h) {
            currentBody->bounceTopOrBottom();
        }
        
    }
    
}

//draws all objects, with their current position
void Arena::draw(){
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        RigidBody* currentBody = rigidBodies[i];
        glPushMatrix();
        instance->setMaterial(currentBody->getMaterial());
        glTranslated(currentBody->getXPosition()+xOffset, 1, currentBody->getYPosition()-yOffset);
        glCallList(currentBody->getDisplayList());
        glPopMatrix();
    }
    glPushMatrix();
    glTranslated(xOffset, 0, -yOffset);
    instance->setMaterial(surface->getMat());
    glCallList(surface->getDisplayList());
    glPopMatrix();
    
}

//constructor
//makes a new surface to play on
//adds spheres to be drawn
Arena::Arena(){
    surface = new Rectangular(10,10,MAT_GRAY);
    xOffset = surface->getWidth()/2;
    yOffset = surface->getHeight()/2;
    
    rigidBodies.push_back(new Sphere(1,0,10,15,1,MAT_BLUE));
    rigidBodies.push_back(new Sphere(0,0,5,2,1,MAT_RED));
    rigidBodies.push_back(new Sphere(0,0,7,8.68,1,MAT_GREEN));
    rigidBodies.push_back(new Sphere(0,0,15,30,1,MAT_YELLOW));
    rigidBodies.push_back(new Sphere(0,0,60,2,1,MAT_RED));
    rigidBodies.push_back(new Sphere(0,0,30,8.68,1,MAT_GREEN));
    
}

//nothing
Arena::~Arena(){
    
}