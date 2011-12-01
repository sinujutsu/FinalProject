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

Rectangular::Rectangular(GLdouble height, GLdouble width){
    h = height;
    w = width;
    
    height = height/2;
    width = width/2;
    fieldd = glGenLists(1);
    glNewList(fieldd,GL_COMPILE);
    glBegin(GL_QUADS);
    glVertex3d(width, 0, height);
    glVertex3d(-width, 0, height);
    glVertex3d(-width, 0, -height);
    glVertex3d(width, 0, -height);
    glEnd();
    glEndList();
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


