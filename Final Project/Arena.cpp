//
//  Arena.cpp
//  Final Project
//
//  Created by Nick Burns on 11/15/11.
//  Copyright 2011 My Company Name. All rights reserved.
//

#include "Arena.h"
#include "OpenGLContainer.h"
#include "Rectangular.h"
#include "cs315.h"

#include <vector>
#include <math.h>
#include <iostream>
using namespace std;


//method responsible for updating the position/state of each object, based on elapsed time
void Arena::update(GLdouble dTime){
    GLdouble backInTime = -dTime *4;
    GLdouble x,y,w,h,r;
    w = xOffset;
    h = yOffset;
    
    
    
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        Sphere* currentBody = rigidBodies[i];
        
        x = currentBody->getXPosition();
        y = currentBody->getYPosition();
        r = currentBody->getSize();
        
        if(wallsOrBalls){
            if (x > h) {
                currentBody->updateState(backInTime);
                currentBody->bounceSide();
                
            }else
                if (x < -h) {
                    currentBody->updateState(backInTime);
                    currentBody->bounceSide();
                }
            
            if (y > w) {
                currentBody->updateState(backInTime);
                currentBody->bounceTopOrBottom();
            }else
                if (y < -w) {
                    currentBody->updateState(backInTime);
                    currentBody->bounceTopOrBottom();
                }
            wallsOrBalls = false;
        }
        
        if(!wallsOrBalls){
            for(GLuint n = 0; n<rigidBodies.size(); n++){
                if (n != i) {
                    if(currentBody->checkCollision(rigidBodies[n])){
                        currentBody->updateState(backInTime);
                        rigidBodies[n]->updateState(backInTime);
                        currentBody->bounceSphere(rigidBodies[n]);

                    }
                }
            }
            wallsOrBalls = true;
        }
        
        currentBody->updateState(dTime);
        
    }
    
}

//draws all objects, with their current position
void Arena::draw(){
    for (GLuint i = 0; i<rigidBodies.size(); i++) {
        Sphere* currentBody = rigidBodies[i];
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
    wallsOrBalls = true;
    surface = new Rectangular(100,100,MAT_GRAY);
    xOffset = surface->getWidth()/2;
    yOffset = surface->getHeight()/2;
    
    GLuint numBalls = 20;
    GLdouble ballPD = 0;
    GLdouble dBallPD = 2;
    for (GLuint i = 0; i<numBalls; i++) {
        rigidBodies.push_back(new Sphere(ballPD,ballPD,5,10,1,MAT_BLUE));
        ballPD += dBallPD;
    }
    rigidBodies.push_back(new Sphere(0,0,1,1,1,MAT_RED));
    rigidBodies.push_back(new Sphere(4,4,-3,5,1,MAT_BLUE));
    rigidBodies.push_back(new Sphere(0,-4,2,8,1,MAT_YELLOW));
    rigidBodies.push_back(new Sphere(-4,0,6,3,1,MAT_GREEN));
    
}

//nothing
Arena::~Arena(){
    
}