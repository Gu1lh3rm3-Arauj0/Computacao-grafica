#include <windows.h>
#include <GL/glut.h>

GLUquadricObj *obj;

#define VERMELHO 1.0, 0.0, 0.0
#define AMARELO 1.0, 1.0, 0.0
#define AZUL 0.0, 0.0, 1.0
#define BRANCO 1.0, 1.0, 1.0
#define PRETO 0.0, 0.0, 0.0

int objId = 1;
float angX = 0;
float angY = 0;

void init(){
     glClearColor(0.0,0.0,0.0,0.0);
     glEnable(GL_DEPTH_TEST);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glOrtho(-7,7,-7,7,-7,7);
     glPushMatrix();
     obj = gluNewQuadric();
     gluQuadricDrawStyle(obj,GLU_LINE);
}


void desenhaEsfera(float r, float g, float b, float raio) {
    glColor3f(r, g, b);
    glutSolidSphere(raio, 20, 20);
}

void desenhaCone(float r, float g, float b, float raio, float altura) {
    glColor3f(r, g, b);
    glutSolidCone(raio, altura, 20, 20);
}

void palhaco(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		glRotatef(angX,1,0,0);
	     glRotatef(angY,0,1,0);

	    glPushMatrix();
	    glTranslatef(0.0, 2.5, 0.0);
	    desenhaEsfera(BRANCO, 1.5);
	    glPopMatrix()

	    glPushMatrix();
	    glTranslatef(-0.5, 0.5, -1.4);
	    desenhaEsfera(PRETO, 0.2);
	    glPopMatrix();

	    glPushMatrix();
	    glTranslatef(0.5, 0.5, -1.4);
	    desenhaEsfera(PRETO, 0.2);
	    glPopMatrix();

	    glPushMatrix();
	    glTranslatef(0.0, -0.2, -1.4);
	    desenhaEsfera(VERMELHO, 0.4);
	    glPopMatrix();

	    glPushMatrix();
	    glTranslatef(0.0, -0.8, -1.4);
	    desenhaCone(VERMELHO, 0.6, 0.2);
	    glPopMatrix();

	    glPushMatrix();
	    glTranslatef(-1.5, 0.0, 0.0);
	    desenhaCone(AMARELO, 0.5, 2.0);
	    glPopMatrix();

	    glPushMatrix();
	    glTranslatef(1.5, 0.0, 0.0);
	    desenhaCone(AMARELO, 0.5, 2.0);
	    glPopMatrix();

	    glPopMatrix();
	    glFlush();

    glFlush();
}

void display()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(0.0,0.0,1.0);

     glPopMatrix();
     glPushMatrix();

     glRotatef(angX,1,0,0);
     glRotatef(angY,0,1,0);

     switch(objId){
        case 1:
           glutWireSphere(3,50,50);
           break;
        case 2:
           glutSolidCube(3);
           break;
        case 3:
           glutSolidCone(3,5,5,1000);
           break;
        case 4:
           glutSolidTorus(3,4,20,1000);
           break;
        case 5:
           glScalef(3,3,3);
           glutSolidIcosahedron();
           break;
        case 6:
           glScalef(3,3,3);
           glutWireOctahedron();
           break;
        case 7:
           glScalef(3,3,3);
           glutWireTetrahedron();
           break;
        case 8:
           glScalef(3,3,3);
           glutSolidDodecahedron();
           break;
        case 9:
           glutSolidTeapot(3);
           break;
        case 10:
           gluCylinder(obj,2,2,5,20,20);
           break;
        case 11:
           gluDisk(obj,2,5,10,10);
           break;
        case 12:
           gluSphere(obj,2,10,10);
           break;
        default:
           break;
     }
     glFlush();
}

void tecladoEspecial(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angX+=5;
           break ;
        case GLUT_KEY_DOWN :
           angX-=5;
           break ;
        case GLUT_KEY_LEFT :
           angY-=5;
           break ;
        case GLUT_KEY_RIGHT :
           angY+=5;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[])
{
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(50,50);
     glutInitWindowSize(600,600);
     glutCreateWindow("Atividade 7 - 1");
     glutDisplayFunc(palhaco);
     glutSpecialFunc(tecladoEspecial);
     init();
     glutMainLoop();
}
