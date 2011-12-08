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
    GLdouble backInTime = -dTime *2;
    Sphere* currentSphere;
    
    
    //the spheres
    //check all spheres against all other spheres
    for (GLuint i = 0; i<spheres.size(); i++) {
        currentSphere = spheres[i];
        if(wallsOrBalls){
            doWalls(currentSphere, dTime);
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
    
    //the player
    //check player against all spheres
    doWalls(player, dTime);
    
    for (GLuint a = 0; a < spheres.size(); a++) {
        currentSphere = spheres[a];
        if (player->checkCollision(spheres[a])) {
            player->updateState(backInTime);
            currentSphere->updateState(backInTime);
            player->bounceSphere(currentSphere);
        }
    }
    player->updateState(dTime);
    
    
    //bullets
    //check all bullets against all spheres
    for (GLuint i = 0; i<bullets.size(); i++) {
        Sphere* currentBullet = bullets[i];
        doWalls(currentBullet, dTime);
        for (GLuint n = 0; n<spheres.size(); n++) {
            if (currentBullet->checkCollision(spheres[n])) {
                currentBullet->die(true);
                spheres[n]->die(true);
//                currentBullet->updateState(backInTime);
//                spheres[n]->updateState(backInTime);
//                currentBullet->bounceSphere(spheres[n]);
                
            }
        }
        currentBullet->updateState(dTime);
    }
    
    
    
    
}

void Arena::doWalls(Sphere *object, GLdouble dTime){
    GLdouble backInTime = -dTime *2;
    GLdouble x,y,w,h,r;
    w = xOffset;
    h = yOffset;
    
    x = object->getXPosition();
    y = object->getYPosition();
    r = object->getSize();
    
    if (x+r > h) {
        object->updateState(backInTime);
        object->bounceSide();
        
    }else
        if (x-r < -h) {
            object->updateState(backInTime);
            object->bounceSide();
        }
    
    if (y+r > w) {
        object->updateState(backInTime);
        object->bounceTopOrBottom();
    }else
        if (y-r < -w) {
            object->updateState(backInTime);
            object->bounceTopOrBottom();
        }
}

//draws all objects, with their current position
void Arena::draw(){
    //draw spheres
    for (GLuint i = 0; i<spheres.size(); i++) {
        Sphere* currentSphere = spheres[i];
        glPushMatrix();
        instance->setMaterial(currentSphere->getMaterial());
        glTranslated(currentSphere->getXPosition(), 1, currentSphere->getYPosition());
        glCallList(currentSphere->getDisplayList());
        glPopMatrix();
    }
    
    //draw player
    glPushMatrix();
		instance->setMaterial(player->getMaterial());
		glTranslated(player->getXPosition(), 1, player->getYPosition());
	    glCallList(player->getDisplayList());
		//Maybe, uh, perhaps get this to fucking work cause this is bullshit?
		//glCallList(player->getMeshDL());
		glPushMatrix();
		  glScalef(10, 10, 10);
		  player->drawPlayerMesh();
		glPopMatrix();
    glPopMatrix();
    
    //draw bullets
    for (GLuint i = 0; i<bullets.size(); i++) {
        Sphere* currentBullet = bullets[i];
        instance->setMaterial(bullets[i]->getMaterial());
        glPushMatrix();
        glTranslated(currentBullet->getXPosition(), 1, currentBullet->getYPosition());
        glCallList(currentBullet->getDisplayList());
        glPopMatrix();
    }
    
    instance->setMaterial(surface->getMat());
    glCallList(surface->getDisplayList());
	glCallList(surface->getDisplayList2());
}

void Arena::playerShoot(GLdouble angle){ 
    GLdouble maxBullets = 20;
    GLdouble bXPos, bYPos, bXVel, bYVel;
    GLdouble bulletSpeed = 20;
    
    bXPos = player->getXPosition();
    bYPos = player->getYPosition();
    
    bYVel = bulletSpeed*cos(angle);
    bXVel = bulletSpeed*sin(angle);
    
    
    
    bullets.push_back(new Sphere(bXPos,bYPos,bXVel,bYVel,.5,MAT_RED));
    if (bullets.size() > maxBullets) {
        for (GLuint i = bullets.size()-maxBullets; i>0; i--) {
            bullets[i]->die(false);
        }
    }
}

//constructor
//makes a new surface to play on
//adds spheres to be drawn
Arena::Arena(Player* thePlayer){
    player = thePlayer;
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
}

//nothing
Arena::~Arena(){
    
}