//
//  OpenGLContainer.h


#ifndef Final_Project_OpenGLContainer_h
#define Final_Project_OpenGLContainer_h

#include "cs315.h"
#include "MaterialInfo.h"
#include "Arena.h"

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
    
    void draw();
    void lights();
    void setMaterial(MaterialInfo m);
};


static const GLdouble CAMERA_ADJ = 5;
static const GLdouble ANIMATION_PRAM = .000001;

static const double PI = 3.141593;

static OpenGLContainer *instance = NULL;
#endif