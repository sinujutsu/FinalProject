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

class Player : public Sphere{
public:
    void updateVelocity(GLdouble xVelocity, GLdouble yVelocity);
    
    
    
    
private:
    GLdouble xVel;
    GLdouble yVel;
    
    
    
    
    
}


#endif
