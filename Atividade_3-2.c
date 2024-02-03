#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

int x1, y1, x2, y2; // Coordenadas dos pontos inicial e final
int colorIndex = 0; // Índice da cor atual
int drawTriangle = 0; // Variável para alternar entre retas e triângulos
int numClicks = 0; // Contador de cliques para desenhar triângulos
int triangleVertices[3][2]; // Coordenadas dos três vértices do triângulo

// Cores pré-selecionadas (pode alterar as cores conforme desejar)
GLfloat colors[10][3] = {
    {0.0, 0.0, 1.0}, // Azul
    {0.0, 1.0, 0.0}, // Verde
    {1.0, 0.0, 0.0}, // Vermelho
    // Adicione mais cores conforme necessário
};

void drawLine(int x1, int y1, int x2, int y2) {
    glColor3fv(colors[colorIndex]); // Define a cor atual
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
    glFlush();
}

void drawTriangleLines() {
    // Desenha as linhas que formam o triângulo
    for (int i = 0; i < 2; i++) {
        drawLine(triangleVertices[i][0], triangleVertices[i][1], triangleVertices[i + 1][0], triangleVertices[i + 1][1]);
    }
    // Linha final que conecta o último vértice ao primeiro
    drawLine(triangleVertices[2][0], triangleVertices[2][1], triangleVertices[0][0], triangleVertices[0][1]);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (drawTriangle) {
        drawTriangleLines();
    } else {
        drawLine(x1, y1, x2, y2);
    }

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        drawTriangle = 0;
    } else if (key == 't' || key == 'T') {
        drawTriangle = 1;
        numClicks = 0;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (drawTriangle) {
            // Registrar os três cliques para definir os vértices do triângulo
            triangleVertices[numClicks][0] = x;
            triangleVertices[numClicks][1] = glutGet(GLUT_WINDOW_HEIGHT) - y; // Inverte a coordenada Y
            numClicks++;

            if (numClicks == 3) {
                glutPostRedisplay(); // Redesenha o triângulo após os três cliques
            }
        } else {
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
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 2");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    gluOrtho2D(0, 800, 0, 600);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
