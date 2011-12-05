// PlayerObject is intended to be used as our class to hold our
// shape that the player will control and move around. Ideally, we can 
// just have it extend shape objects.

#ifndef Final_Project_Sphere_h
#define Final_Project_Sphere_h

#include "Sphere.h"
#include "cs315.h"

class PlayerObject : public Sphere
{
	public:
		GLdouble xVel;
		GLdouble yVel;
		GLint lives;

		void bounceSphere(Sphere* otherSphere);
}

#endif