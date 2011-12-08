//
//  Player.cpp
//  XcodeCloneAttempt
//
//  Created by Nick Burns on 12/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "Player.h"
#include <iostream>





GLboolean Player::checkCollision(Sphere* otherSphere){
    GLboolean hit = otherSphere->checkCollision(this);
    if (hit) {
        health -= 1;
    }
    if (health <=0) {
        this->die(true);
    }
    return hit;
}

Player::Player(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat): Sphere(xPositionInit,  yPositionInit,  xVelocity,  yVelocity,  radius,  mat){
    health = 5;
    
}