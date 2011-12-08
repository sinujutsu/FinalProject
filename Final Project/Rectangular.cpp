//
//  Rectangular.cpp
//  Final Project
//
//  Created by Nick Burns on 11/15/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Rectangular.h"
#include "cs315.h"
#include "MaterialInfo.h"
#include "OpenGLContainer.h"
#include "tga.h"

unsigned int texTop;
unsigned int texBack;
unsigned int texLeft;
unsigned int texRight;
unsigned int texFront;
unsigned int texBottom;
unsigned int texArena;

Rectangular::Rectangular(GLdouble height, GLdouble width, MaterialInfo fieldMaterial){
    h = height;
    w = width;//poop
    
    
    glGenTextures(1, &texTop);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texTop, 1));
	glGenTextures(1, &texBack);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texBack, 1));
	glGenTextures(1, &texLeft);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texLeft, 1));
	glGenTextures(1, &texRight);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texRight, 1));
	glGenTextures(1, &texFront);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texFront, 1));
	glGenTextures(1, &texBottom);
	printf("Texture load result: %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronbluefixed.tga", texBottom, 1));

	glGenTextures(1, &texArena);
	printf("Texture load result; %i\n", Tga::loadTGA("FinalProject\\Final Project\\Textures\\tronorangefixed.tga", texArena, 1));

	background = glGenLists(1);
	drawBackground();
    
    arena = glGenLists(1);
    
    mat = fieldMaterial;
    GLdouble thick = 2;
    
    height = height/2;
    width = width/2;
    fieldd = glGenLists(1);
    glNewList(fieldd,GL_COMPILE);

	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texArena);
    glBegin(GL_QUADS);
    //field
	glTexCoord2d(0,0); glVertex3d(width, 0, height);
    glTexCoord2d(1,0); glVertex3d(-width, 0, height);
    glTexCoord2d(1,1); glVertex3d(-width, 0, -height);
    glTexCoord2d(0,1); glVertex3d(width, 0, -height);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_CULL_FACE);

    //corner squares
	instance->setMaterial(MAT_BLACK);
    glVertex3d(height+thick, thick, width+thick);
    glVertex3d(height, thick, width+thick);
    glVertex3d(height, thick, width);
    glVertex3d(height+thick, thick, width);
    
    glVertex3d(-height, thick, width);
    glVertex3d(-height, thick, width+thick);
    glVertex3d(-height-thick, thick, width+thick);
    glVertex3d(-height-thick, thick, width);
    
    glVertex3d(height+thick, thick, -width-thick);
    glVertex3d(height+thick, thick, -width);
    glVertex3d(height, thick, -width);
    glVertex3d(height, thick, -width-thick);
    
    glVertex3d(-height, thick, -width-thick);
    glVertex3d(-height, thick, -width);
    glVertex3d(-height-thick, thick, -width);
    glVertex3d(-height-thick, thick, -width-thick);
    
    //side longs
    glVertex3d(height+thick, thick, -width);
    glVertex3d(height+thick, thick, width);
    glVertex3d(height, thick, width);
    glVertex3d(height, thick, -width);
    
    glVertex3d(height, thick, width);
    glVertex3d(height, thick, width+thick);
    glVertex3d(-height, thick, width+thick);
    glVertex3d(-height, thick, width);
    
    glVertex3d(-height, thick, -width);
    glVertex3d(-height, thick, width);
    glVertex3d(-height-thick, thick, width);
    glVertex3d(-height-thick, thick, -width);
    
    glVertex3d(height, thick, -width-thick);
    glVertex3d(height, thick, -width);
    glVertex3d(-height, thick, -width);
    glVertex3d(-height, thick, -width-thick);
    //vert side walls  outside
    glVertex3d(-width-thick, 0, -height-thick);
    glVertex3d(-width-thick, thick, -height-thick);
    glVertex3d(width+thick, thick, -height-thick);
    glVertex3d(width+thick, 0, -height-thick);
    
    glVertex3d(width+thick, thick, -height-thick);
    glVertex3d(width+thick, thick, height+thick);
    glVertex3d(width+thick, 0, height+thick);
    glVertex3d(width+thick, 0, -height-thick);
    
    glVertex3d(width+thick, thick, height+thick);
    glVertex3d(-width-thick, thick, height+thick);
    glVertex3d(-width-thick, 0, height+thick);
    glVertex3d(width+thick, 0, height+thick);
    
    glVertex3d(-width-thick, thick, height+thick);
    glVertex3d(-width-thick, thick, -width-thick);
    glVertex3d(-width-thick, 0, -width-thick);
    glVertex3d(-width-thick, 0, height+thick);
    
    //inside
    glVertex3d(-width, 0, -height);
    glVertex3d(-width, thick, -height);
    glVertex3d(width, thick, -height);
    glVertex3d(width, 0, -height);
    
    glVertex3d(width, thick, -height);
    glVertex3d(width, thick, height);
    glVertex3d(width, 0, height);
    glVertex3d(width, 0, -height);
    
    glVertex3d(width, thick, height);
    glVertex3d(-width, thick, height);
    glVertex3d(-width, 0, height);
    glVertex3d(width, 0, height);
    
    glVertex3d(-width, thick, height);
    glVertex3d(-width, thick, -width);
    glVertex3d(-width, 0, -width);
    glVertex3d(-width, 0, height);
    
    
    glEnd();
    glEndList();
}

void Rectangular::drawBackground(){
	glNewList(background, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_CULL_FACE);
	//glDisable(GL_LIGHTING);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texTop);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(200.0,200.0,-200.0);
		glTexCoord2d(1,0); glVertex3f(-200.0,200.0,-200.0);
		glTexCoord2d(1,1); glVertex3f(-200.0,200.0,200.0);
		glTexCoord2d(0,1); glVertex3f(200.0,200.0,200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texBack);
	glBegin(GL_QUADS);
		/*glTexCoord2d(0,0); glVertex3f(200.0,-200.0,-200.0);
		glTexCoord2d(200,0); glVertex3f(-200.0,-200.0,-200.0);
		glTexCoord2d(200,200); glVertex3f(-200.0,200.0,-200.0);
		glTexCoord2d(0,200); glVertex3f(200.0,200.0,-200.0);
		*/
		glTexCoord2d(0,0); glVertex3f(200.0,-200.0,-200.0);
		glTexCoord2d(1.0,0); glVertex3f(-200.0,-200.0,-200.0);
		glTexCoord2d(1.0,1.0); glVertex3f(-200.0,200.0,-200.0);
		glTexCoord2d(0,1.0); glVertex3f(200.0,200.0,-200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texLeft);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(-200.0,-200.0,-200.0);
		glTexCoord2d(1,0); glVertex3f(-200.0,-200.0,200.0);
		glTexCoord2d(1,1); glVertex3f(-200.0,200.0,200.0);
		glTexCoord2d(0,1); glVertex3f(-200.0,200.0,-200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texRight);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(200.0,-200.0,200.0);
		glTexCoord2d(1,0); glVertex3f(200.0,-200.0,-200.0);
		glTexCoord2d(1,1); glVertex3f(200.0,200.0,-200.0);
		glTexCoord2d(0,1); glVertex3f(200.0,200.0,200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texFront);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(-200.0,-200.0,200.0);
		glTexCoord2d(1,0); glVertex3f(200.0,-200.0,200.0);
		glTexCoord2d(1,1); glVertex3f(200.0,200.0,200.0);
		glTexCoord2d(0,1); glVertex3f(-200.0,200.0,200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texBottom);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(200.0,-200.0, 200.0);
		glTexCoord2d(1,0); glVertex3f(-200.0,-200.0,200.0);
		glTexCoord2d(1,1); glVertex3f(-200.0,-200.0,-200.0);
		glTexCoord2d(0,1); glVertex3f(200.0,-200.0,-200.0);
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//glEnable(GL_CULL_FACE);
	//glEnable(GL_LIGHTING);
	glEndList();
}
GLuint Rectangular::getDisplayList(){
	return background;
}

Rectangular::~Rectangular(){
    glDeleteLists(fieldd, 1);
}

GLdouble Rectangular::getHeight(){
    return h;
}

GLdouble Rectangular::getWidth(){
    return w;
}

MaterialInfo Rectangular::getMat(){
    return mat;
}


