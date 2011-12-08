//
//  Player.h
//  XcodeCloneAttempt
//
//  Created by Nick Burns on 12/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef XcodeCloneAttempt_Player_h
#define XcodeCloneAttempt_Player_h
#include "cs315.h"
#include "MaterialInfo.h"
#include "Sphere.h"

class Player : public Sphere {
public:
    void shoot(GLdouble angle);
    void die();
    
    GLboolean checkCollision(Sphere* otherSphere);
    
    Player(GLdouble xPosition, GLdouble yPosition, GLdouble radius, GLdouble xVelocity, GLdouble yVelocity);
private:
    void updateAngle();
    
    GLdouble xVel;
    GLdouble yVel;
    GLdouble xPos;
    GLdouble yPos;
    GLdouble size;
    
    GLuint shape;
    
    MaterialInfo material;
    
    
    
    
};


#endif
