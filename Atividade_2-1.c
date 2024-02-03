#include <windows.h>
#include <GL/glut.h>

// Variáveis para armazenar as coordenadas do ponto
double pontoX = 0.0;
double pontoY = 0.0;

void MouseInt(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        pontoX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        pontoY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
        glutPostRedisplay();
    }
}

void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3f(0.0, 0.0, 1.0); // Cor azul
    glBegin(GL_POINTS);
    glVertex2f(pontoX, pontoY);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 1");

    glClearColor(1.0, 1.0, 1.0, 1.0); // Cor de fundo branca
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(desenhar);
    glutMouseFunc(MouseInt);

    glutMainLoop();

    return 0;
}
