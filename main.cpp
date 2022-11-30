#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "stdio.h"
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height); //lokalizacja kamery
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt (6.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //gdzie kamera ma patrzec
}
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //czas
    double year_period = 4.0;                  // 4 sekundy to jeden rok
    double year     = (t / year_period);
    double day      = 365 * year; //dzien na ziemi
    double moon_sid = (365 / 27.3) * year; //dzien na ksiezycu
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie bufforu

    glPushMatrix();
    glColor4f (1.0, 1.0, 0, 1);
    glutSolidSphere(1.0, 20, 16);            // slonce

    glRotatef(year*100, 0.0, 1.0, 0.0);    // obrot ziemi wokool slonca
    glTranslatef(3.0, 0.0, 0.0);          // lokalizacja ziemi

    glPushMatrix();                      // wdrozenie ziemi

    glPushMatrix();
    glRotatef(day*100, 0.0, 1.0, 0.0);      // obracanie sie zami
    glRotatef(90-23.4, 1.0, 0.0, 0.0);       // osie ziemi
    glColor3f (0, 0, 1);         // kolor ziemi
    glutSolidSphere(0.3, 10, 8);           //bryla ziemi
    glPopMatrix();

    glPushMatrix();
    glRotatef(moon_sid*100, 0.0, 1.0, 0.0); // obrot ksiezyca
    glTranslatef(1.0, 0.0, 0.0);        // odleglosc ksiezyca od ziemi
    glRotatef(90, 1.0, 0.0, 0.0);
    glColor4f (0.4, 0.5, 0.6, 1);
    glutSolidSphere(0.1, 10, 8); // bryla ksiezyca

    glPopMatrix();
    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

static void idle(void)
{
    glutPostRedisplay();
}
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 0.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };



const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 1000.0f };
//swiatla (schowane mniej wiecej jest w sloncu)

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(720,480); // wielkosc okna
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("UKLAD SLONECZNY"); //nazwa okna

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}