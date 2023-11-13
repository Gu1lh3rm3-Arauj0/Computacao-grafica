#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM
#define TOP 8

#define x_min 50
#define x_max 150
#define y_min 50
#define y_max 150

int computeCode(double x, double y)
{

    int code = INSIDE;

    if (x < x_min)
        code |= LEFT;
    else if (x > x_max)
        code |= RIGHT;
    if (y < y_min)
        code |= BOTTOM;
    else if (y > y_max)
        code |= TOP;

    return code;
}

void cohenSutherlandClip(double x1, double y1,
                         double x2, double y2)
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = 1;
            break;
        }
        else if (code1 & code2) {

            break;
        }
        else {

            int code_out;
            double x, y;


            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;


            if (code_out & TOP) {

                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM) {

                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT) {

                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else if (code_out & LEFT) {

                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (accept) {
        glColor3f(0.0, 1.0, 0.0); // Cor verde
        glBegin(GL_LINES);
            glVertex2d(x1, y1);
            glVertex2d(x2, y2);
        glEnd();
    }
}

void drawFrame()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(x_min, y_min);
        glVertex2i(x_max, y_min);
        glVertex2i(x_max, y_max);
        glVertex2i(x_min, y_max);
    glEnd();
}

double x1, y1, x2, y2;

int first = 1;

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x = x - 250;
        y = 250 - y;

        if (first) {
            x1 = x;
            y1 = y;
            first = 0;
        }
        else {
            x2 = x;
            y2 = y;
            first = 1;

            cohenSutherlandClip(x1, y1, x2, y2);

            glutSwapBuffers();
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawFrame();

    glutSwapBuffers();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Atividade 12");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
