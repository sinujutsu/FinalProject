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

Rectangular::Rectangular(GLdouble height, GLdouble width, MaterialInfo fieldMaterial){
    h = height;
    w = width;
    mat = fieldMaterial;
    GLdouble thick = 1;
    height = height/2;
    width = width/2;
    fieldd = glGenLists(1);
    glNewList(fieldd,GL_COMPILE);
    
    instance->setMaterial(MAT_RED);
    glBegin(GL_QUADS);
    //field
    glVertex3d(width, 0, height);
    glVertex3d(-width, 0, height);
    glVertex3d(-width, 0, -height);
    glVertex3d(width, 0, -height);
    //corner squares
    glVertex3d(height+thick, 0, width+thick);
    glVertex3d(height, 0, width+thick);
    glVertex3d(height, 0, width);
    glVertex3d(height+thick, 0, width);
    
    glVertex3d(-height, 0, width);
    glVertex3d(-height, 0, width+thick);
    glVertex3d(-height-thick, 0, width+thick);
    glVertex3d(-height-thick, 0, width);
    
    glVertex3d(height+thick, 0, -width-thick);
    glVertex3d(height+thick, 0, -width);
    glVertex3d(height, 0, -width);
    glVertex3d(height, 0, -width-thick);
    
    glVertex3d(-height, 0, -width-thick);
    glVertex3d(-height, 0, -width);
    glVertex3d(-height-thick, 0, -width);
    glVertex3d(-height-thick, 0, -width-thick);
    
    //side longs
    glVertex3d(height+thick, 0, -width);
    glVertex3d(height+thick, 0, width);
    glVertex3d(height, 0, width);
    glVertex3d(height, 0, -width);
    
    glVertex3d(height, 0, width);
    glVertex3d(height, 0, width+thick);
    glVertex3d(-height, 0, width+thick);
    glVertex3d(-height, 0, width);
    
    glVertex3d(-height, 0, -width);
    glVertex3d(-height, 0, width);
    glVertex3d(-height-thick, 0, width);
    glVertex3d(-height-thick, 0, -width);
    
    glVertex3d(height, 0, -width-thick);
    glVertex3d(height, 0, -width);
    glVertex3d(-height, 0, -width);
    glVertex3d(-height, 0, -width-thick);
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


