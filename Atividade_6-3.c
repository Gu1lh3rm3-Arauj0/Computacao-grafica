#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float incX = 0.5;
float incY = 0.5;
float tx = 0.0;
float ty = 0.0;

void robo(){
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(tx,ty,0.0);

	glPushMatrix();


	// Cabeça
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.1, 0.7);
	glVertex2f(0.1, 0.7);
	glVertex2f(0.1, 0.9);
	glVertex2f(-0.1, 0.9);
	glEnd();

	//Corpo
	 glColor3f(1.0, 0.0, 0.0);
	 glBegin(GL_POLYGON);
	 glVertex2f(-0.2, 0.1);
	 glVertex2f(0.2, 0.1);
	 glVertex2f(0.2, 0.7);
	 glVertex2f(-0.2, 0.7);
	 glEnd();


	// Braço esquerdo
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(-0.2, 0.3);
	glVertex2f(-0.1, 0.3);
	glVertex2f(-0.1, 0.7);
	glVertex2f(-0.2, 0.7);
	glEnd();

	// Braço direito
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0.3);
	glVertex2f(0.2, 0.3);
	glVertex2f(0.2, 0.7);
	glVertex2f(0.1, 0.7);
	glEnd();

	 // Pernas
	 glColor3f(0.0, 0.0, 1.0);
	 glBegin(GL_POLYGON);
	 glVertex2f(-0.1, -0.2);
	 glVertex2f(0.0, -0.2);
	 glVertex2f(0.0, 0.1);
	 glVertex2f(-0.1, 0.1);
	 glEnd();

	 glBegin(GL_POLYGON);
	 glVertex2f(0.0, -0.2);
	 glVertex2f(0.1, -0.2);
	 glVertex2f(0.1, 0.1);
	 glVertex2f(0.0, 0.1);
	 glEnd();

	 glPopMatrix();
	 glFlush();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void tecladoEspecial(int tecla, int x, int y){
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            tx+=0.03;
            break;
        case GLUT_KEY_LEFT:
            tx-=0.05;
            break;
        case GLUT_KEY_UP:
            ty+=0.05;
            break;
        case GLUT_KEY_DOWN:
            ty-=0.05;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}


int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutInit(&argc, argv);
    glutCreateWindow ("Exercicio 3");
    init();
    glutDisplayFunc (robo);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop ();

    return 0;
}
