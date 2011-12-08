//
//  OpenGLContainer.h


#ifndef Final_Project_OpenGLContainer_h
#define Final_Project_OpenGLContainer_h

#include "cs315.h"
#include "MaterialInfo.h"
#include "Arena.h"

void keyDownCallback(unsigned char key, int x, int y);
void redrawCallback();
void reshapeCallback(int w, int h);
void idleCallback();

class Arena;
class Player;

class OpenGLContainer {
public:
    OpenGLContainer();
    virtual ~OpenGLContainer();
    
    void initalizeOpenGLContainer();
    void keyDown(unsigned char key, int x, int y);//actions with keypresses
    void idle();
    void redraw();
    void reshape(GLuint witdth, GLuint height);
    void initGL();
    void setMaterial(MaterialInfo m);
    

    
    
private:
    Arena* theArena;
    
    GLdouble pitch;
    GLdouble yaw;
    GLdouble zoom;
    GLdouble centX;
    GLdouble centZ;
    
    GLboolean animate;
    GLdouble last_time;
    GLdouble cur_time;
    GLdouble elapsed;

	Player* thePlayer;
    
    void draw();
    void lights();
    
};


static const GLdouble CAMERA_ADJ = 5;
static const GLdouble ANIMATION_PRAM = 1;

static const GLdouble PI = 3.141593;
static const GLdouble MULT_RAD_TO_DEG = 180/PI;

static OpenGLContainer *instance = NULL;
#endif
