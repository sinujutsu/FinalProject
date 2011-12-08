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
#include "mesh.h"

class Player : public Sphere {
public:
    
    GLboolean checkCollision(Sphere* otherSphere);
    Player(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat);

private:
    void updateAngle();	
	void loadPlayerMesh(const char *filename);
	void drawPlayerMesh();
    
    GLuint health;
    
    GLdouble xVel;
    GLdouble yVel;
    GLdouble xPos;
    GLdouble yPos;
    GLdouble size;
    
    
    GLuint shape;
    
    MaterialInfo material;
	Mesh m;
    
    
    
    
};


#endif
