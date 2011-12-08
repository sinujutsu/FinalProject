//
//  Player.h
//  XcodeCloneAttempt
//
//  Created by Nick Burns on 12/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef XcodeCloneAttempt_Player_test_h
#define XcodeCloneAttempt_Player_test_h

#include "cs315.h"
#include "MaterialInfo.h"
#include "Sphere.h"
#include "mesh.h"
#include "OpenGLContainer.h"

class Player : public Sphere {

public:
    GLboolean checkCollision(Sphere* otherSphere);
    Player(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat);
	GLuint getMeshDL();
	void loadPlayerMesh(const char *filename);
	void drawPlayerMesh();

	void setXVelocity(GLdouble xV);
    void setYVelocity(GLdouble yV);

	GLdouble getXVelocity();
    GLdouble getYVelocity();

private:
    void updateAngle();	

    GLuint health;
    GLuint meshDL;
	Mesh m;
};


#endif
