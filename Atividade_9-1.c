#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float thetaX = 0.0;
float thetaY = 0.0;

#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO 1.0, 1.0, 0.0
#define AZUL 0.0, 0.0, 1.0
#define BRANCO 1.0, 1.0, 1.0
#define PRETO 0.0, 0.0, 0.0
#define ROSA 1.0, 0.0, 1.0
#define LARANJA 1.0, 0.5, 0.0

void cubo() {
    glColor3f(VERMELHO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(-0.1, -0.1, 0.1);
    glEnd();
    glColor3f(AMARELO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, -0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
    glColor3f(LARANJA);
    glBegin(GL_POLYGON);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glEnd();
    glColor3f(AZUL);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.1, 0.1);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(-0.1, 0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
    glColor3f(BRANCO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, 0.1);
    glVertex3f(0.1, 0.1, -0.1);
    glVertex3f(-0.1, 0.1, -0.1);
    glEnd();
    glColor3f(ROSA);
    glBegin(GL_POLYGON);
    glVertex3f(-0.1, -0.1, 0.1);
    glVertex3f(0.1, -0.1, 0.1);
    glVertex3f(0.1, -0.1, -0.1);
    glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
}

void cuboFino() {
    glColor3f(VERMELHO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, 0.04, 0.04);
    glVertex3f(0.04, 0.04, 0.04);
    glVertex3f(0.04, -0.04, 0.04);
    glVertex3f(-0.04, -0.04, 0.04);
    glEnd();
    glColor3f(ROSA);
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, 0.04, -0.04);
    glVertex3f(0.04, 0.04, -0.04);
    glVertex3f(0.04, -0.04, -0.04);
    glVertex3f(-0.04, -0.04, -0.04);
    glEnd();
    glColor3f(LARANJA);
    glBegin(GL_POLYGON);
    glVertex3f(0.04, -0.04, 0.04);
    glVertex3f(0.04, 0.04, 0.04);
    glVertex3f(0.04, 0.04, -0.04);
    glVertex3f(0.04, -0.04, -0.04);
    glEnd();
    glColor3f(AMARELO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, -0.04, 0.04);
    glVertex3f(-0.04, 0.04, 0.04);
    glVertex3f(-0.04, 0.04, -0.04);
    glVertex3f(-0.04, -0.04, -0.04);
    glEnd();
    glColor3f(AZUL);
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, 0.04, 0.04);
    glVertex3f(0.04, 0.04, 0.04);
    glVertex3f(0.04, 0.04, -0.04);
    glVertex3f(-0.04, 0.04, -0.04);
    glEnd();
    glColor3f(BRANCO);
    glBegin(GL_POLYGON);
    glVertex3f(-0.04, -0.04, 0.04);
    glVertex3f(0.04, -0.04, 0.04);
    glVertex3f(0.04, -0.04, -0.04);
    glVertex3f(-0.04, -0.04, -0.04);
    glEnd();
}

void robo() {
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.05, 0.0);
    cubo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.056, -0.13, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.056, -0.20, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.056, -0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.056, -0.39, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.056, -0.13, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.056, -0.20, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.056, -0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.056, -0.39, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.17, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.25, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.36, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.44, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.17, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.25, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.36, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.44, 0.31, 0.0);
    cuboFino();
    glPopMatrix();
}

void desenha() {
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glRotatef(10, 1.0, 0.0, 0.0);
        glRotatef(10, 0.0, 1.0, 0.0);
        glRotatef(thetaX, 1.0, 0.0, 0.0);
        glRotatef(thetaY, 0.0, 1.0, 0.0);
        robo();
        glPopMatrix();

    glFlush();
}

void tecladoEspecial(int tecla, int x, int y) {
    switch (tecla) {
        case GLUT_KEY_RIGHT:
            thetaY += 2;
            break;
        case GLUT_KEY_LEFT:
            thetaY -= 2;
            break;
        case GLUT_KEY_UP:
            thetaX += 2;
            break;
        case GLUT_KEY_DOWN:
            thetaX -= 2;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Atividade 9");
    glutDisplayFunc(desenha);
    glutSpecialFunc(tecladoEspecial);
    glutMainLoop();
    return 0;
}
