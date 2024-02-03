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
float tz = 0.0;
float m = 0.0;
int cont = 0;


#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO 1.0, 1.0, 0.0
#define AZUL 0.0, 0.0, 1.0
#define BRANCO 1.0, 1.0, 1.0
#define PRETO 0.0, 0.0, 0.0
#define ROSA 1.0, 0.0, 1.0
#define LARANJA 1.0, 0.5, 0.0

void cubo() {
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.15,0.15,0.15);
    glVertex3f(0.15,0.15,0.15);
    glVertex3f(0.15,-0.15,0.15);
    glVertex3f(-0.15,-0.15,0.15);
  glEnd();

  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.15,0.15,-0.15);
    glVertex3f(0.15,0.15,-0.15);
    glVertex3f(0.15,-0.15,-0.15);
    glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

  glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.15,-0.15,0.15);
    glVertex3f(0.15,0.15,0.15);
    glVertex3f(0.15,0.15,-0.15);
    glVertex3f(0.15,-0.15,-0.15);
  glEnd();

  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.15,-0.15,0.15);
    glVertex3f(-0.15,0.15,0.15);
    glVertex3f(-0.15,0.15,-0.15);
    glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

  glColor3f(1.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.15,0.15,0.15);
    glVertex3f(0.15,0.15,0.15);
    glVertex3f(0.15,0.15,-0.15);
    glVertex3f(-0.15,0.15,-0.15);
  glEnd();

  glColor3f(0.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.15,-0.15,0.15);
    glVertex3f(0.15,-0.15,0.15);
    glVertex3f(0.15,-0.15,-0.15);
    glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

}

void triangulo(){
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
  	glVertex3f(0,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0.15,-0.15,-0.15);
	glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

  glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0.15,0.15,-0.15);
    glVertex3f(0.15,-0.15,-0.15);

  glEnd();
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(0,0,0);
	glVertex3f(-0.15,0.15,-0.15);
	glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

  glColor3f(1.0,0.0,1.0);
  glBegin(GL_POLYGON);
	glVertex3f(0,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0.15,0.15,-0.15);
	glVertex3f(-0.15,0.15,-0.15);
  glEnd();

  glColor3f(0.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0.15,-0.15,-0.15);
    glVertex3f(-0.15,-0.15,-0.15);
  glEnd();

}


void torre(){
    float altura =-1.0;

    float largura = 0.1;

    for (int i = 0; i < 6; i++) {

        glColor3f(BRANCO);

        glBegin(GL_POLYGON);

        float angulo1 = i * M_PI / 3;
        float angulo2 = (i + 1) * M_PI / 3;

        glVertex3f(largura * cos(angulo1), altura, largura * sin(angulo1));
        glVertex3f(largura * cos(angulo2), altura, largura * sin(angulo2));
        glVertex3f(largura * cos(angulo2), -0.15, largura * sin(angulo2));
        glVertex3f(largura * cos(angulo1), -0.15, largura * sin(angulo1));

        glEnd();
    }
}

void desenha() {
  triangulo();

  glPushMatrix();
  glTranslatef(0.0,0.30,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.30,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.30,0.0,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.30,0.0,0.0);
  cubo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.60,0.0);
  glRotatef(90,1.0,0.0,0.0);
  glRotatef(180,0.0,1.0,0.0);
  triangulo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,-0.60,0.0);
  glRotatef(90,1.0,0.0,0.0);
  triangulo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.60,0.0,0.0);
  glRotatef(270,0.0,1.0,0.0);
  glRotatef(270,0.0,0.0,1.0);
  triangulo();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.60,0.0,0.0);
  glRotatef(90,0.0,1.0,0.0);
  glRotatef(90,0.0,0.0,1.0);
  triangulo();
  glPopMatrix();

  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  glFlush();

}


void gira(){
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();
  glRotatef(ty,0.0,1.0,0.0);
  glRotatef(tx,0.0,0.0,1.0);
  desenha();
  glPopMatrix();
  glPopMatrix();

  torre();
  glPopMatrix();
  glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
  switch (tecla) {
  case GLUT_KEY_RIGHT:
    ty += 2;
    break;
  case GLUT_KEY_LEFT:
    ty -= 2;
    break;
  case GLUT_KEY_UP:
    tx += 2;
    break;
  case GLUT_KEY_DOWN:
    tx -= 2;
    break;
  default:
    break;
  }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    	cont=1;
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
    	cont=2;
    }
}

void timerFunc(int value){
    switch (cont) {
        case 1:
        	if(m<20){
        	     m += 0.3;
        	     tx += 0.3;
        	   }
        	tx+= m;
        	break;

        case 2:
        	if(m>-20){
        		m -=0.3;
        		tx -= 0.3;
        	}
        	tx+= m;
        	break;
    }
    glutPostRedisplay();
    glutTimerFunc(10,timerFunc, 1);
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(400,400);
  glutCreateWindow("Atividade 7-2");
  glutDisplayFunc(gira);
  glutSpecialFunc(tecladoEspecial);
  glutMouseFunc(mouse);
  glutTimerFunc(10,timerFunc, 1);
  glutMainLoop();
  return 0;
}
