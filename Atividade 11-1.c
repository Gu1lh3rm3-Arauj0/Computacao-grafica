#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define x_min 50
#define x_max 150
#define y_min 50
#define y_max 150

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point* vertices;
    int size;
} Polygon;

Polygon* createPolygon()
{
    Polygon* p = (Polygon*)malloc(sizeof(Polygon));
    p->vertices = NULL;
    p->size = 0;
    return p;
}

void addPoint(Polygon* p, Point pt)
{
    p->size++;
    p->vertices = (Point*)realloc(p->vertices, p->size * sizeof(Point));
    p->vertices[p->size - 1] = pt;
}

void freePolygon(Polygon* p)
{
    free(p->vertices);
    free(p);
}

void drawPolygon(Polygon* p, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        for (int i = 0; i < p->size; i++) {
            glVertex2d(p->vertices[i].x, p->vertices[i].y);
        }
    glEnd();
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

double dotProduct(Point v1, Point v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

Point normal(Point p1, Point p2)
{
    Point n;
    n.x = p2.y - p1.y;
    n.y = p1.x - p2.x;
    return n;
}

Point intersection(Point p1, Point p2, Point p3, Point p4)
{
    Point i;
    double t;
    double num = (p3.y - p4.y) * (p1.x - p3.x) + (p4.x - p3.x) * (p1.y - p3.y);
    double den = (p3.y - p4.y) * (p2.x - p1.x) + (p4.x - p3.x) * (p2.y - p1.y);
    if (den == 0) {
        i = p1;
    }
    else {
        t = num / den;
        i.x = p1.x + t * (p2.x - p1.x);
        i.y = p1.y + t * (p2.y - p1.y);
    }
    return i;
}

int inside(Point p, Point p1, Point p2)
{
    Point n = normal(p1, p2);
    Point v;
    v.x = p.x - p1.x;
    v.y = p.y - p1.y;
    double d = dotProduct(n, v);
    return d >= 0;
}

Polygon* clipPolygon(Polygon* subject, Polygon* clipper)
{
    Polygon* output = createPolygon();
    for (int i = 0; i < subject->size; i++) {
        addPoint(output, subject->vertices[i]);
    }
    for (int i = 0; i < clipper->size; i++) {
        Point p1 = clipper->vertices[i];
        Point p2 = clipper->vertices[(i + 1) % clipper->size];
        Polygon* temp = createPolygon();
        for (int j = 0; j < output->size; j++) {
            Point s1 = output->vertices[j];
            Point s2 = output->vertices[(j + 1) % output->size];
            if (inside(s1, p1, p2)) {
                if (!inside(s2, p1, p2)) {
                    Point i = intersection(s1, s2, p1, p2);
                    addPoint(temp, i);
                }
                addPoint(temp, s1);
            }
            else {
                if (inside(s2, p1, p2)) {
                    Point i = intersection(s1, s2, p1, p2);
                    addPoint(temp, i);
                }
            }
        }
        freePolygon(output);
        output = temp;
    }
    return output;
}

Polygon* subject;
Polygon* clipper;
int mode = 0;

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x = x - 250;
        y = 250 - y;

        Point p;
        p.x = x;
        p.y = y;

        if (mode == 0) {
            addPoint(subject, p);
        }
        else {
            addPoint(clipper, p);
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        mode = 1 - mode;
    }
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawFrame();
	drawPolygon(subject, 0.0, 0.0, 1.0);
	drawPolygon(clipper, 0.0, 1.0, 0.0);
	Polygon* result = clipPolygon(subject, clipper);
	drawPolygon(result, 1.0, 1.0, 0.0);
	freePolygon(result);
	glutSwapBuffers();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250, 250, -250, 250);
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Atividade 12");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	init();
	subject = createPolygon();
	clipper = createPolygon();
	glutMainLoop();

	return 0;
}

