//
//  OpenGLContainer.cpp


#include "cs315.h"
#include "OpenGLContainer.h"
#include "Arena.h"

#include <math.h>
#include <iostream>

using namespace std;


//Constructor
//Makes a new arena, sets initial view
OpenGLContainer::OpenGLContainer(){
    theArena = new Arena();
    pitch = 50;
    yaw = 0;
    zoom = 20;
    centX = 0;
    centZ = 0;
    animate = false;
}

//Deconstructor
//does nothing
OpenGLContainer::~OpenGLContainer(){}

void OpenGLContainer::initalizeOpenGLContainer(){}

//
//calls draw method of the arena
void OpenGLContainer::draw(){
    theArena->draw();
    
}

//Method for setting the current material
void OpenGLContainer::setMaterial(MaterialInfo m){
    float *diffuse = m.getDiffuse();
    glMaterialfv(GL_FRONT, GL_SPECULAR,  m.getSpecular());
    glMaterialf (GL_FRONT, GL_SHININESS, m.getShininess());
    glMaterialfv(GL_FRONT, GL_AMBIENT,   m.getAmbient());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   m.getDiffuse());
    glMaterialfv(GL_FRONT, GL_EMISSION, m.getEmitted());
    glColor4f(diffuse[0],diffuse[1],diffuse[2],1.0);
}

//Handles key presses
void OpenGLContainer::keyDown(unsigned char key, int x, int y){
    switch (key) {
        case 'r':
            pitch = 50;
            yaw = 0;
            zoom = 20;
            centX = 0;
            centZ = 0;
            animate = false;
            break;
        case 'g':
            last_time = CS315::getTime();
            cur_time = CS315::getTime();
            animate = !animate;
            break;
        case 'w':
            pitch -= CAMERA_ADJ;
            break;
        case 's':
            pitch += CAMERA_ADJ;
            break;
        case 'a':
            yaw -= CAMERA_ADJ;
            break;
        case 'd':
            yaw += CAMERA_ADJ;
            break;
        case 'q':
            zoom += CAMERA_ADJ/4;
            break;
        case 'e':
            zoom -= CAMERA_ADJ/4;
            break;
        case 'i':
            centZ -= CAMERA_ADJ/2;
            break;
        case 'k':
            centZ += CAMERA_ADJ/2;
            break;
        case 'j':
            centX -= CAMERA_ADJ/2;
            break;
        case 'l':
            centX += CAMERA_ADJ/2;
            break;
        default:
            break;
    }
    if (key != 'g') {
        redraw();
    }
    
}

//sets up one light
void OpenGLContainer::lights(){
    GLfloat position[] =  {0, 11.00, 10.0, 1.0};
    GLfloat dcolor[] = {1,1,1,1};
    GLfloat acolor[] = {1,1,1,1};
    GLfloat scolor[] = {.9,.9,.9,1};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, acolor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, dcolor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, scolor);
}

//updates the arena with how much time has passed
void OpenGLContainer::idle(){
    if (animate) {
        cur_time = CS315::getTime();
        elapsed = (cur_time - last_time) * ANIMATION_PRAM;
        last_time = cur_time;
        theArena->update(elapsed);
        cout<< elapsed << endl;
        glutPostRedisplay();
    }
}

//camera position set here
void OpenGLContainer::redraw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0,zoom, 0, 0, 0, 0, 0, 0, 1);
    glRotated(pitch, 1, 0, 0);
    glTranslated(centX, 0, centZ);
    glRotated(yaw, 0, 1, 0);
    lights(); 
    draw();
    glutSwapBuffers();
}

//reshapes the window
void OpenGLContainer::reshape(GLuint width, GLuint height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,500.0f);
    glMatrixMode(GL_MODELVIEW);             
    glLoadIdentity();
}

void OpenGLContainer::initGL(){
    glShadeModel(GL_SMOOTH);              
    glClearColor(131.0/255.0, 152.0/255.0, 163.0/255.0, 0.0f);       
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT,GL_FILL);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void keyDownCallback(unsigned char key, int x, int y)
{instance->keyDown(key, x, y);}

void redrawCallback()
{instance->redraw();}

void reshapeCallback(int w, int h)
{instance->reshape(w, h);}

void idleCallback()
{instance->idle();}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Rigid Body Test");
    glutIdleFunc(idleCallback);
    glutDisplayFunc(redrawCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyDownCallback);
    instance = new OpenGLContainer();
    instance->initGL();
    instance->initalizeOpenGLContainer();
    glutMainLoop();
    return 0;
}


