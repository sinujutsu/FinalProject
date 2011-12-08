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
#include "Player.h"

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
    
    
    //the spheres
    for (GLuint i = 0; i<spheres.size(); i++) {
        Sphere* currentSphere = spheres[i];
        
        x = currentSphere->getXPosition();
        y = currentSphere->getYPosition();
        r = currentSphere->getSize();
        
        if(wallsOrBalls){
            if (x > h) {
                currentSphere->updateState(backInTime);
                currentSphere->bounceSide();
                
            }else
                if (x < -h) {
                    currentSphere->updateState(backInTime);
                    currentSphere->bounceSide();
                }
            
            if (y > w) {
                currentSphere->updateState(backInTime);
                currentSphere->bounceTopOrBottom();
            }else
                if (y < -w) {
                    currentSphere->updateState(backInTime);
                    currentSphere->bounceTopOrBottom();
                }
            wallsOrBalls = false;
        }
        
        if(!wallsOrBalls){
            for(GLuint n = 0; n<spheres.size(); n++){
                if (n != i) {
                    if(currentSphere->checkCollision(spheres[n])){
                        currentSphere->updateState(backInTime);
                        spheres[n]->updateState(backInTime);
                        currentSphere->bounceSphere(spheres[n]);

                    }
                }
            }
            wallsOrBalls = true;
        }
        
        currentSphere->updateState(dTime);
        
    }
    
}

//draws all objects, with their current position
void Arena::draw(){
    for (GLuint i = 0; i<spheres.size(); i++) {
        Sphere* currentSphere = spheres[i];
        glPushMatrix();
        instance->setMaterial(currentSphere->getMaterial());
        glTranslated(currentSphere->getXPosition(), 1, currentSphere->getYPosition());
        glCallList(currentSphere->getDisplayList());
        glPopMatrix();
    }
    
    instance->setMaterial(surface->getMat());
    glCallList(surface->getDisplayList());
}

void Arena::playerShoot(GLdouble angle){ 
    
}

//constructor
//makes a new surface to play on
//adds spheres to be drawn
Arena::Arena(){
    wallsOrBalls = true;
    surface = new Rectangular(100,100,MAT_GRAY);
    xOffset = surface->getWidth()/2;
    yOffset = surface->getHeight()/2;
    
    GLuint numBalls = 18;
    GLdouble ballPD = -5;
    GLdouble dBallPD = 3;
    for (GLuint i = 0; i<numBalls; i++) {
        spheres.push_back(new Sphere(ballPD,ballPD,5,10,1,MAT_BLUE));
        ballPD += dBallPD;
    }
    spheres.push_back(new Player(-20,-20,-11,-10,3,MAT_GREEN));
    
}

//nothing
Arena::~Arena(){
    
}