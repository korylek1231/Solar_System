#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "stdio.h"
float i = 4.0,t = 0, timer = 150;
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height); //lokalizacja kamery
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    gluLookAt (1.0, 10.0, 5.0, 0.0, 0.0, 0.0, -10.0, 0.0, 0.0); //gdzie kamera ma patrzec
}
void zegar(int wartosc)
{
    glutTimerFunc(timer, zegar, 0);
	t += 0.01;
	glutPostRedisplay();
}
static void display(void)
{
    i += 0.5;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glColor4f (1.0, 1.0, 0, 1);
    glutSolidSphere(1.0, 20, 16);            // slonce

    glRotatef(i, 0.0, 1.0, 0.0);    // obrot ziemi wokool slonca
    glTranslatef(3.0, 0.0, 0.0);          // lokalizacja ziemi

    glPushMatrix();                      // wdrozenie ziemi

    glPushMatrix();
    glRotatef(i*100, 0.0, 1.0, 0.0);      // obracanie sie ziemi
    glRotatef(66, 1.0, 0.0, 0.0);       // osie ziemi
    glColor3f (0, 0, 1);         // kolor ziemi
    glutSolidSphere(0.3, 10, 8);           //bryla ziemi
    glPopMatrix();

    glPushMatrix();
    glRotatef(i*10, 0.0, 1.0, 0.0); // obrot ksiezyca
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
    glutTimerFunc(timer, zegar, 0);


    glutMainLoop();

    return EXIT_SUCCESS;
}
