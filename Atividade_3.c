#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

int x1, y1, x2, y2; // Coordenadas dos pontos inicial e final
int colorIndex = 0; // Índice da cor atual

// Cores pré-selecionadas (pode alterar as cores conforme desejar)
GLfloat colors[10][3] = {
    {0.0, 0.0, 1.0}, // Azul
    {0.0, 1.0, 0.0}, // Verde
    {1.0, 0.0, 0.0}, // Vermelho
    {1.0, 1.0, 0.0}, // Amarelo
    {1.0, 0.0, 1.0}, // Magenta
    {0.0, 1.0, 1.0}, // Ciano
    {0.5, 0.5, 0.5}, // Cinza
    {1.0, 0.5, 0.0}, // Laranja
    {0.5, 0.0, 0.5}, // Roxo
    {0.0, 0.5, 0.5}  // Turquesa
};

void drawLine(int x1, int y1, int x2, int y2) {
    glColor3fv(colors[colorIndex]); // Define a cor atual
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(x1, y1, x2, y2);
    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key >= '0' && key <= '9') {
        colorIndex = key - '0';
        glutPostRedisplay(); // Redesenha a linha com a nova cor
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x1 == 0 && y1 == 0) {
            x1 = x;
            y1 = glutGet(GLUT_WINDOW_HEIGHT) - y; // Inverte a coordenada Y
        } else {
            x2 = x;
            y2 = glutGet(GLUT_WINDOW_HEIGHT) - y; // Inverte a coordenada Y
            glutPostRedisplay(); // Redesenha a linha com os novos pontos
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 1");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
