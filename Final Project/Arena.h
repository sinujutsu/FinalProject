//
//  Arena.h


#ifndef Final_Project_Arena_h
#define Final_Project_Arena_h


#include "cs315.h"
#include "MaterialInfo.h"
#include "Sphere.h"
#include "Surface.h"
#include "Rectangular.h"
#include "Player.h"
#include "mesh.h"

#include <vector>

class Arena{

private:
    Rectangular* surface;
    vector<Sphere*> spheres;
    vector<Sphere*> bullets;
    Player* player;
    GLdouble xOffset;
    GLdouble yOffset;
    GLboolean wallsOrBalls;
    
	void doWalls(Sphere* object, GLdouble dTime);

public:
    void update(GLdouble dTime);
    void draw();
    
    void playerShoot(GLdouble angle);

    
    void addRigidBody(Sphere body);
    Arena(Player* thePlayer);
    virtual ~Arena();
};

#endif
