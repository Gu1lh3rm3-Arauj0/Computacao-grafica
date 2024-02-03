#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

float theta = 0.0;
float tx = 0.0;

void robo(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(tx,0,0.0);

	glPushMatrix();


	glClear(GL_COLOR_BUFFER_BIT);

	// Carro
	glColor3f(1.0, 1.0, 0.0); // Amarelo
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.6, 0.0);
	    glVertex2f(0.4, 0.0);
	    glVertex2f(0.4, 0.3);
	    glVertex2f(-0.6, 0.3);
	    glEnd();

	    // Vidro dianteiro (azul)
	    glColor3f(0.0, 0.0, 1.0); // Azul
	    glBegin(GL_POLYGON);
	    glVertex2f(0.2, 0.1);
	    glVertex2f(0.4, 0.1);
	    glVertex2f(0.4, 0.3);
	    glVertex2f(0.3, 0.3);
	    glEnd();

	    // Vidro traseiro (azul)
	    glBegin(GL_POLYGON);
	    glVertex2f(-0.6, 0.1);
	    glVertex2f(-0.5, 0.1);
	    glVertex2f(-0.5, 0.3);
	    glVertex2f(-0.6, 0.3);
	    glEnd();

	    // Roda esquerda (preta)
	    glRotatef(tx,0.0,0.0,1.0);
	    glColor3f(0.0, 0.0, 0.0); // Preto
	    glBegin(GL_POLYGON);
	    for (int i = 0; i < 360; i++) {
	        float theta = i * 3.1415926 / 180.0;
	        float x = -0.4 + 0.1 * cos(theta);
	        float y = -0.05 + 0.1 * sin(theta);
	        glVertex2f(x, y);
	    }
	    glEnd();
	    glPopMatrix();

	    // Roda direita (preta)
	    glRotatef(tx,0.0,0.0,1.0);
	    glBegin(GL_POLYGON);
	    for (int i = 0; i < 360; i++) {
	        float theta = i * 3.1415926 / 180.0;
	        float x = 0.2 + 0.1 * cos(theta);
	        float y = -0.05 + 0.1 * sin(theta);
	        glVertex2f(x, y);
	    }
	    glEnd();
	    glPopMatrix();
	    glPopMatrix();
	    glFlush();
	}

void init(){
	glColor3f(1.0, 1.0, 1.0);
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
