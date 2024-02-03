#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

// Variáveis para armazenar as coordenadas do ponto e a cor atual
double pontoX = 0.0;
double pontoY = 0.0;
int corAtual = 0; // Índice da cor atual

// Cores indexadas para o ponto
GLfloat cores[][3] = {
    {0.0, 0.0, 1.0}, // Azul
    {1.0, 0.0, 0.0}, // Vermelho
    {0.0, 1.0, 0.0}, // Verde
    {1.0, 1.0, 0.0}, // Amarelo
    {1.0, 0.65, 0.0}, // Laranja
    {0.5, 0.0, 0.5}, // Roxo
    {0.0, 0.5, 0.5}, // Azul-esverdeado
    {0.5, 0.5, 0.5}, // Cinza
    {0.0, 0.0, 0.0}, // Preto
};

void MouseInt(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        pontoX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
        pontoY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
        glutPostRedisplay();
    }
}

void TecladoFunc(unsigned char tecla, int x, int y) {
    if (tecla >= '0' && tecla <= '9') {
        corAtual = tecla - '0'; // Atualiza a cor com base na tecla pressionada
        glutPostRedisplay();
    }
}

void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5.0);
    glColor3fv(cores[corAtual]); // Define a cor atual
    glBegin(GL_POINTS);
    glVertex2f(pontoX, pontoY);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 2");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(desenhar);
    glutMouseFunc(MouseInt);
    glutKeyboardFunc(TecladoFunc);

    glutMainLoop();

    return 0;
}
