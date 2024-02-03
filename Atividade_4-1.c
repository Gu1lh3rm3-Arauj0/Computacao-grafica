#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.141592654

int PontoX;
int PontoY;
int raio = 50;

void setPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2f(2.0f * x / glutGet(GLUT_WINDOW_WIDTH) - 1.0f, -2.0f * y / glutGet(GLUT_WINDOW_HEIGHT) + 1.0f);
    glEnd();
}

void bresenhamCirculo(int xc, int yc, int raio) {
    int x = 0;
    int y = raio;
    int p = PI - 2 * raio;

    while (x <= y) {
        setPixel(xc + x, yc + y);
        setPixel(xc - x, yc + y);
        setPixel(xc + x, yc - y);
        setPixel(xc - x, yc - y);
        setPixel(xc + y, yc + x);
        setPixel(xc - y, yc + x);
        setPixel(xc + y, yc - x);
        setPixel(xc - y, yc - x);

        if (p < 0) {
            p += 2 * x + 3;
        } else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glColor3f(0.0, 0.0, 0.0);

    bresenhamCirculo(PontoX, PontoY, raio);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            raio = 25;
            break;
        case '2':
            raio = 50;
            break;
        case '3':
            raio = 75;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void MouseInt(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        PontoX = x;
        PontoY = y;

        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 1");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutDisplayFunc(desenha);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(MouseInt);
    glutMainLoop();

    return 0;
}
