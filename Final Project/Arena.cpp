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
#include <iostream>
using namespace std;


//method responsible for updating the position/state of each object, based on elapsed time
void Arena::update(GLdouble dTime){
    GLdouble x,y,w,h,r;
    w = xOffset;
    h = yOffset;
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        Sphere* currentBody = rigidBodies[i];
        RigidBody* rigid = currentBody;
        
        x = rigid->getXPosition();
        y = rigid->getYPosition();
        r = currentBody->getSize();
        //check walls
        if (x > h) {
            currentBody->bounceSide(h);
        }else
        if (x < -h) {
            currentBody->bounceSide(-h);
        }

        if (y > w) {
            currentBody->bounceTopOrBottom(w);
        }else
        if (y < -h) {
            currentBody->bounceTopOrBottom(-w);
        }
        
        //check balls
        for(GLuint n = 0; n<rigidBodies.size(); n++){
            if (n != i) {
                if(currentBody->checkCollision(rigidBodies[n])){
                    cout<< "Collision detected!"<< endl;
                    currentBody->bounceSphere(rigidBodies[n]);
                }
            }
        }
        cout<< " x: " << x << " y: " << y<< endl;
        currentBody->updateState(dTime);
        
        
    }
    
}

//draws all objects, with their current position
void Arena::draw(){
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        RigidBody* currentBody = rigidBodies[i];
        glPushMatrix();
        instance->setMaterial(currentBody->getMaterial());
        glTranslated(currentBody->getXPosition(), 1, currentBody->getYPosition());
        glCallList(currentBody->getDisplayList());
        glPopMatrix();
    }

    instance->setMaterial(surface->getMat());
    glCallList(surface->getDisplayList());
}

//constructor
//makes a new surface to play on
//adds spheres to be drawn
Arena::Arena(){
    surface = new Rectangular(10,10,MAT_GRAY);
    xOffset = surface->getWidth()/2;
    yOffset = surface->getHeight()/2;
    
    rigidBodies.push_back(new Sphere(0,0,15,15,1,MAT_BLUE));
    rigidBodies.push_back(new Sphere(3,1,-4,10,1,MAT_RED));
    rigidBodies.push_back(new Sphere(4,2,-2,17,1,MAT_GREEN));
    rigidBodies.push_back(new Sphere(1,3,6,13,1,MAT_YELLOW));
}

//nothing
Arena::~Arena(){
    
}