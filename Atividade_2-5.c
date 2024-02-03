#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

enum ModoDesenho {
    LINHA,
    TRIANGULO
};

enum ModoDesenho modoAtual = LINHA; // Certifique-se de usar 'enum ModoDesenho' aqui
int corAtual = 0; // Índice da cor atual

// Variáveis para armazenar as coordenadas dos pontos iniciais e finais da linha ou triângulo
double pontoInicialX = 0.0;
double pontoInicialY = 0.0;
double pontoFinalX = 0.0;
double pontoFinalY = 0.0;
int pontosContados = 0; // Contador de pontos para desenhar triângulo

// Cores indexadas para a linha/triângulo
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
        if (modoAtual == LINHA) {
            pontoInicialX = pontoFinalX;
            pontoInicialY = pontoFinalY;

            pontoFinalX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
            pontoFinalY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
        } else if (modoAtual == TRIANGULO) {
            if (pontosContados == 0) {
                pontoInicialX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
                pontoInicialY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
                pontosContados++;
            } else if (pontosContados == 1) {
                pontoFinalX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
                pontoFinalY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);
                pontosContados++;
            } else if (pontosContados == 2) {
                double terceiroPontoX = (2.0 * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0;
                double terceiroPontoY = 1.0 - (2.0 * y) / glutGet(GLUT_WINDOW_HEIGHT);

                glBegin(GL_TRIANGLES);
                glColor3fv(cores[corAtual]);
                glVertex2f(pontoInicialX, pontoInicialY);
                glVertex2f(pontoFinalX, pontoFinalY);
                glVertex2f(terceiroPontoX, terceiroPontoY);
                glEnd();

                glFlush();

                pontoInicialX = pontoFinalX = terceiroPontoX;
                pontoInicialY = pontoFinalY = terceiroPontoY;

                pontosContados = 1;
            }
        }
        glutPostRedisplay();
    }
}

void TecladoFunc(unsigned char tecla, int x, int y) {
    if (tecla == 'r' || tecla == 'R') {
        modoAtual = LINHA;
    } else if (tecla == 't' || tecla == 'T') {
        modoAtual = TRIANGULO;
    }
    glutPostRedisplay();
}

void desenhar() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (modoAtual == LINHA) {
        glLineWidth(2.0);
        glColor3fv(cores[corAtual]);

        glBegin(GL_LINES);
        glVertex2f(pontoInicialX, pontoInicialY);
        glVertex2f(pontoFinalX, pontoFinalY);
        glEnd();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Exercicio 5");

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
