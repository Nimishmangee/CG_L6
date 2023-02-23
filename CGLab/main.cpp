#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<ctime>
#include <unistd.h>
#define pie 3.14

using namespace std;
float rp=0;
bool pendulum_dir=1, pendulumRotation=0;
int hours=1, minutes=30, seconds=10;
bool operationApplied=0;
bool ct=0,cr=0,cs=0;

GLfloat V[8][3]={
    {-0.5,0.8,0.2},
    {0.5,0.8,0.2},
    {0.5,-0.5,0.2},
    {-0.5,-0.5,0.2},
    
    {-0.5,0.8,-0.2},
    {0.5,0.8,-0.2},
    {0.5,-0.5,-0.2},
    {-0.5,-0.5,-0.2}
};
void init(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}
void xAndyAxis(){
        //x
        glColor3ub(254, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);
        glEnd();
    
        //y
        glColor3ub(200, 255, 0);
        glBegin(GL_LINES);
        glVertex2f(0.0,-1.0);
        glVertex2f(0.0,1.0);
        glEnd();

}
void circle(float x,float y,float z, float a=0.2, int ang1=0, int ang2=360){
    float r=0.2;
    glBegin(GL_TRIANGLE_FAN);
    
    if(a!=0.2)
        r=a;
    
    for(int i=ang1;i<ang2;i++)
        glVertex3f(x+cos((i*pie)/180)*r,y+sin((i*pie)/180)*r, z);
    glEnd();
}

void Face(GLfloat A[],GLfloat B[],GLfloat C[],GLfloat D[])
{
    glBegin(GL_POLYGON);
        glVertex3fv(A);
        glVertex3fv(B);
        glVertex3fv(C);
        glVertex3fv(D);
    glEnd();
}

void Cube()
{
    glColor3ub(210, 210, 210);
    Face(V[0],V[1],V[2],V[3]);  //Front
    glColor3ub(210,210,210);
    Face(V[4],V[5],V[6],V[7]);  //Back
    glColor3ub(119,136,153);
    Face(V[0],V[4],V[7],V[3]);  //Left
    glColor3ub(119,136,153);
    Face(V[1],V[5],V[6],V[2]);  //Right
    glColor3ub(119,136,153);
    Face(V[2],V[3],V[7],V[6]);  //Bot
    glColor3ub(119,136,153);
    Face(V[0],V[1],V[5],V[4]);  //Top
}

void drawClock(){
    Cube();
    
    if(pendulumRotation){
        time_t currentTime=time(NULL);
        struct tm *localTime=localtime(&currentTime);
        hours=localTime->tm_hour;
        minutes=localTime->tm_min;
        seconds=localTime->tm_sec;
    }
    
    //designCircle
    glColor3ub(255, 192, 203);
    circle(0, 0.15, 0.201,0.25);
    
    //hours label 12
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(0, 0.7, 0.201);
    glVertex3f(0, 0.775, 0.201);
    glEnd();

    //hours label 3
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(0.4, 0.15, 0.201);
    glVertex3f(0.475, 0.15, 0.201);
    glEnd();

    //hours label 6
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(0, -0.4, 0.201);
    glVertex3f(0, -0.475, 0.201);
    glEnd();

    //hours label 9
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(-0.4, 0.15, 0.201);
    glVertex3f(-0.475, 0.15, 0.201);
    glEnd();

    
    //pendulum
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(rp, 0, 0, 1);
    glTranslatef(0, 0.5, 0);
    glColor3ub(100, 100, 200);
    glRectf(-0.015, -0.85, 0.015, -0.5);
    glColor3ub(0, 0, 0);
    circle(0, -0.9,0,0.05);
    glPopMatrix();
    if(pendulum_dir==1) rp+=0.5;
    if(pendulum_dir==0) rp-=0.5;
    if(rp==30) pendulum_dir=!pendulum_dir;
    if(rp==-30) pendulum_dir=!pendulum_dir;
    
    if(pendulumRotation)
        glutPostRedisplay();
    
    
    glColor3ub(120,120,120);
    circle(0, 0.15,0.201,0.01);
    
    //hour hand
    glPushMatrix();
    glTranslatef(0, 0.15, 0);
    glRotatef(30*(hours)+0.5*(minutes), 0, 0, 1);
    glTranslatef(0, -0.15, 0);
    glLineWidth(7);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(0, 0.15, 0.201);
    glVertex3f(0, 0.45, 0.201);
    glEnd();
    glPopMatrix();
    
    //minute hand
    glPushMatrix();
    glTranslatef(0, 0.15, 0);
    glRotatef(6*(minutes)+0.1*(seconds), 0, 0, 1);
    glTranslatef(0, -0.15, 0);
    glLineWidth(7);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex3f(0, 0.15, 0.201);
    glVertex3f(0, 0.55, 0.201);
    glEnd();
    glPopMatrix();
    
    //second hand
    glPushMatrix();
    glTranslatef(0, 0.15, 0);
    glRotatef(6*(seconds), 0, 0, 1);
    glTranslatef(0, -0.15, 0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(80,80,80);
    glVertex3f(0, 0.15, 0.201);
    glVertex3f(0, -0.30, 0.201);
    glEnd();
    glPopMatrix();
}

void rotateClock(){
    
}

//************************ MAIN DISPLAY FUNCTION ****************************

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
//    xAndyAxis();
    gluLookAt(0, 0, 0, 0.6, 0.6, 1, 0, 1, 0);
    
    if(!operationApplied)
        drawClock();
    
    if(cr){
        
    }
    
    
    glutSwapBuffers();
}

void keyboard(unsigned char,int,int);

void keyboardToSetHours(unsigned char key, int x, int y){
    char ch=key;
    hours=ch-'0';
    glutPostRedisplay();
    
    glutKeyboardFunc(keyboard);
}

void keyboardToSetMinutes(unsigned char key, int x, int y){
    char ch=key;
    minutes=(ch-'0')*10;
    glutPostRedisplay();
    
    glutKeyboardFunc(keyboard);
}

void keyboard(unsigned char key, int x, int y){
    if(key=='Q' or key=='q')
        exit(1);
    if(key=='H' or key=='h'){
        glutKeyboardFunc(keyboardToSetHours);
    }
    if(key=='M' or key=='m')
        glutKeyboardFunc(keyboardToSetMinutes);
    if(key=='S' or key=='s'){
        pendulumRotation=!pendulumRotation;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y){
    if(button==GLUT_RIGHT_BUTTON and state==GLUT_DOWN){}
}

void operations(int id){
    switch(id){
    }
}

void translation(int id){
    switch(id){
        case 1:
            
            break;
        case 2:
            
            break;
    }
}

void rotation(int id){
    switch(id){
        case 1:
            
            break;
        case 2:
            
            break;
    }
}

void scaling(int id){
    switch(id){
        case 1:
            
            break;
        case 2:
            
            break;
    }
}

int main(int argc,char* argv[]){
    glutInit(&argc, argv);
    glutCreateWindow("Basic Shapes");
    glutInitWindowSize(1900, 800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    
    //**********Menu*************
    int sub_menu1=glutCreateMenu(translation);
    glutAddMenuEntry("2 Units", 1);
    glutAddMenuEntry("4 Units", 2);
    
    int sub_menu2=glutCreateMenu(rotation);
    glutAddMenuEntry("15 Degress", 1);
    glutAddMenuEntry("30 Degrees", 2);
    
    int sub_menu3=glutCreateMenu(scaling);
    glutAddMenuEntry("1.5 x", 1);
    glutAddMenuEntry("3 x", 2);
    
    glutCreateMenu(operations);
    glutAddSubMenu("Transalation", sub_menu1);
    glutAddSubMenu("Rotation", sub_menu2);
    glutAddSubMenu("Scaling", sub_menu3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
    glutMainLoop();
    return 0;
}

