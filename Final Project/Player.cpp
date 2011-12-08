//
//  Player.cpp
//  XcodeCloneAttempt
//
//  Created by Nick Burns on 12/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "Player.h"
#include "OpenGLContainer.h"
#include <iostream>


void Player::setXVelocity(GLdouble xV){
    xVel = xV;
}

void Player::setYVelocity(GLdouble yV){
    yVel = yV;
}

void Player::loadPlayerMesh(const char *filename)
{
// Load the model
  m.init(filename);
  if (m.getFTotal() == 0) return;

  // Scale it to fit in a small box
  float minx, maxx;
  float miny, maxy;
  float minz, maxz;
  static const float MAX_SIZE = 1.0f;
  unsigned int nvertices = m.getVList().size();
  int i;
  for(i=1; i<nvertices; i++) 
  {
    // note: first vertex is "default vertex" - avoid using this as part of size calculations
    Vec3 v = m.getVList()[i];
    if (i == 1 || (v[0] < minx)) minx = v[0];
    if (i == 1 || (v[1] < miny)) miny = v[1];
    if (i == 1 || (v[2] < minz)) minz = v[2];
    if (i == 1 || (v[0] > maxx)) maxx = v[0];
    if (i == 1 || (v[1] > maxy)) maxy = v[1];
    if (i == 1 || (v[2] > maxz)) maxz = v[2];      
  }

  float xcenter = (maxx + minx) / 2.0;
  float ycenter = (maxy + miny) / 2.0;
  float zcenter = (maxz + minz) / 2.0;
  // Find the largest axis
  float span = maxx-minx;
  if (maxy - miny > span) span = maxy-miny;
  if (maxz - minz > span) span = maxz-minz;
  float scale_factor = MAX_SIZE / span;
  // Scale and translate each vertex to put the object in
  // a nice box
  for(i=0; i<nvertices; i++) 
  {
    Vec3 v = m.getVList()[i];
    v[0] -= xcenter;
    v[1] -= ycenter;
    v[2] -= zcenter;
    v[0] *= scale_factor;
    v[1] *= scale_factor;
    v[2] *= scale_factor;
    m.getVList()[i] = v;
  }
}

void Player::drawPlayerMesh()
{
// Draw our mesh if we have one
	if (m.getFList().size() > 0) 
	{
		float* vertices = (float*)(&(m.getVList()[0]));
		float* normals = (float*)(&(m.getNList()[0]));
		glDisable (GL_COLOR_MATERIAL);

		glBegin(GL_TRIANGLES);
		// For each face in the model:
		for(unsigned int i=0; i < m.getFList().size(); i++) 
		{
			Face f = m.getFList()[i];
			Material mat;
			mat = m.getMaterial()[f[0].getMaterialIndex()];
			GLfloat mat_shininess[1];

			// some meshes have a shininess of zero, which causes problems.
			mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;
			glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
			glNormal3f( normals[3*f[0].getNormalIndex()+0]  , normals[3*f[0].getNormalIndex()+1]  , normals[3*f[0].getNormalIndex()+2] );
			glVertex3f( vertices[3*f[0].getVertexIndex()+0] , vertices[3*f[0].getVertexIndex()+1] , vertices[3*f[0].getVertexIndex()+2] );
			mat = m.getMaterial()[f[1].getMaterialIndex()];

			// some meshes have a shininess of zero, which causes problems.
			mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;
			glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
			glNormal3f( normals[3*f[1].getNormalIndex()+0]  , normals[3*f[1].getNormalIndex()+1]  , normals[3*f[1].getNormalIndex()+2] );
			glVertex3f( vertices[3*f[1].getVertexIndex()+0] , vertices[3*f[1].getVertexIndex()+1] , vertices[3*f[1].getVertexIndex()+2] );
			mat = m.getMaterial()[f[2].getMaterialIndex()];

			// some meshes have a shininess of zero, which causes problems.
			mat_shininess[0] = (mat.Ns > 0) ? mat.Ns : 50.0f;
			glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, mat.Ka);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, mat.Kd);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, mat.Ks);
			glMaterialfv ( GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
			glNormal3f( normals[3*f[2].getNormalIndex()+0]  , normals[3*f[2].getNormalIndex()+1]  , normals[3*f[2].getNormalIndex()+2] );
			glVertex3f( vertices[3*f[2].getVertexIndex()+0] , vertices[3*f[2].getVertexIndex()+1] , vertices[3*f[2].getVertexIndex()+2] );
		}
		glEnd(); // Make sure you have this! It HATES having no glEnd (everthing breaks).
    }
}

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

Player::Player(GLdouble xPositionInit, GLdouble yPositionInit, GLdouble xVelocity, GLdouble yVelocity, GLdouble radius, MaterialInfo mat): Sphere(xPositionInit,  yPositionInit,  xVelocity,  yVelocity,  radius,  mat)
{
    health = 5;
    shape = glGenLists(1);
    glNewList(shape,GL_COMPILE);
		instance->setMaterial(material);
		glutWireSphere(size, 4, 5);
		drawPlayerMesh();
    glEndList();
}