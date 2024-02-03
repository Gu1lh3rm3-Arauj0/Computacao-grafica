#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

float theta = 0.0;
float angle = 0.0f;
float tx = 0.0;
float ty = 0.0;

void flor()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(angle + ty * 60, 0.0f, 0.0f, 1.0f);

	glPushMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
    for (int i = 0; i < 6; i++) {
    	glPushMatrix();
    	glRotatef(angle + i * 60, 0.0f, 0.0f, 1.0f);
    	glTranslatef(tx, 0.0f, 0.0f);
    	glBegin(GL_POLYGON);
    	for (int j = 0; j < 360; j++) {
    	    float theta = j * 3.14159265359 / 180.0;
    	    float x = 0.05 * cos(theta);
    	    float y = 0.2 * sin(theta);
    	    glVertex2f(x, y);
    	}
    	glEnd();
    	glPopMatrix();
    }

	glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
            float theta = i * 3.14159265359 / 180.0;
            float x = 0.1 * cos(theta);
            float y = 0.1 * sin(theta);
            glVertex2f(x, y);
        }
    glEnd();

    glPopMatrix();
    glFlush();
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

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(50,100);
    glutInitWindowSize(400,400);
    glutInit(&argc, argv);
    glutCreateWindow("Exercicio 1");
    init();
    glutDisplayFunc(flor);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop ();
    return 0;
}
