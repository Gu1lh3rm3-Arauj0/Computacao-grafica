#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct BMPImagem{
    int   width;
    int   height;
    char *data;
}BMPImage;

#define MAX_NO_TEXTURES 6

GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "grama.bmp",
		"surface1.bmp",
		"surface2.bmp",
		"surface3.bmp",
		"surface4.bmp",
		"surface5.bmp"
};

int k=5;
int y=1;
float a = 0;

GLUquadricObj *obj;

GLfloat angleXD = 0.0f;
GLfloat angleXE = 0.0f;
GLfloat angleY = 0.0f;

/*------------------------------------------------------------------------------------------------------------------------------*/
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


void CarregaTexturas()
{
    BMPImage textura;

    glGenTextures(MAX_NO_TEXTURES, texture_id);

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

//----------------------------------------------------------------------------------------------------------------------------

void initTexture (void){

    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    CarregaTexturas();
}

void lightning(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(void)
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 5.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 2.0, 8.0);
    glViewport(0, 0, 500, 500);

    lightning();
}


void grama() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, 0.0f, -5.0f);
    glTexCoord2f(5.0f, 0.0f); glVertex3f(5.0f, 0.0f, -5.0f);
    glTexCoord2f(5.0f, 5.0f); glVertex3f(5.0f, 0.0f, 5.0f);
    glTexCoord2f(0.0f, 5.0f); glVertex3f(-5.0f, 0.0f, 5.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void esfera(float radius, int slices, int stacks) {
    for (int i = 0; i <= stacks; ++i) {
        float lat0 = M_PI * (-0.5 + (float)(i - 1) / stacks);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = M_PI * (-0.5 + (float)i / stacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float)(j - 1) / slices;
            float x = cos(lng);
            float y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glTexCoord2f((float)j / slices, (float)(i - 1) / stacks);
            glVertex3f(radius * x * zr0, radius * y * zr0, radius * z0);

            glNormal3f(x * zr1, y * zr1, z1);
            glTexCoord2f((float)j / slices, (float)i / stacks);
            glVertex3f(radius * x * zr1, radius * y * zr1, radius * z1);
        }
        glEnd();
    }
}


void coxa_esquerda(){
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glPushMatrix();
	glTranslatef(-0.1,0.0,0.0);
	glScalef(0.25,0.7,0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glPushMatrix();
	glTranslatef(-0.1,-0.225,0.0);
	glScalef(0.25, 0.25, 0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();
}


void perna_esquerda(){
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glTranslatef(-0.1,-0.45,0.0);
	glScalef(0.25, 0.7, 0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glTranslatef(-0.1,-0.6,0.1);
	glScalef(0.25, 0.25, 0.55);
	esfera(0.2, 20, 20);
	glPopMatrix();
}


void coxa_direita(){
	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glPushMatrix();
	glTranslatef(0.1,0.0,0.0);
	glScalef(0.25,0.7,0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[4]);
	glPushMatrix();
	glTranslatef(0.1,-0.225,0.0);
	glScalef(0.25, 0.25, 0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();
}

void perna_direita(){
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glTranslatef(0.1,-0.45,0.0);
	glScalef(0.25, 0.7, 0.25);
	esfera(0.3, 20, 20);
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glTranslatef(0.1,-0.6,0.1);
	glScalef(0.25, 0.25, 0.55);
	esfera(0.2, 20, 20);
	glPopMatrix();
}

void braco_esquerdo(){
	  glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	  glPushMatrix();
	  glTranslatef(-0.25,0.45,0.15);
	  glScalef(0.25,0.25,0.6);
	  esfera(0.3, 20, 20);
	  glRotatef(45, 0, 1, 0);
	  glPopMatrix();
}

void braco_direito(){
	glBindTexture(GL_TEXTURE_2D, texture_id[5]);
	glPushMatrix();
	glTranslatef(0.25,0.45,0.15);
	glScalef(0.25,0.25,0.6);
	esfera(0.3, 20, 20);
	glRotatef(45, 0, 1, 0);
	glPopMatrix();
}

void robo(){
  glMatrixMode(GL_MODELVIEW);

  //Cabeça
  glBindTexture(GL_TEXTURE_2D, texture_id[1]);
  glPushMatrix();
  glTranslatef(0.0, 0.95, 0.0);
  glScalef(0.5, 0.5, 0.5);
  esfera(0.3, 20, 20);
  glPopMatrix();

  //Corpo
  glBindTexture(GL_TEXTURE_2D, texture_id[2]);
  glPushMatrix();
  glTranslatef(0.0,0.5,0.0);
  glScalef(0.7,1.3,0.5);
  esfera(0.3, 20, 20);
  glPopMatrix();

  //Perna esquerda
  coxa_esquerda();

  //Perna direita
  coxa_direita();

  //Braço esquerdo
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glPushMatrix();
  glTranslatef(-0.19,0.72,0.0);
  glScalef(0.22, 0.22, 0.22);
  esfera(0.2, 20, 20);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glPushMatrix();
  glTranslatef(-0.25,0.6,0.0);
  glScalef(0.25,0.6,0.25);
  esfera(0.3, 20, 20);
  glPopMatrix();

  braco_esquerdo();

  //Braço Direito
  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glPushMatrix();
  glTranslatef(0.19,0.72,0.0);
  glScalef(0.22,0.22,0.22);
  esfera(0.2, 20, 20);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, texture_id[3]);
  glPushMatrix();
  glTranslatef(0.25,0.6,0.0);
  glScalef(0.25,0.6,0.25);
  esfera(0.3, 20, 20);
  glPopMatrix();

  braco_direito();

}


void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //grama()

    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);


    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glTranslatef(0, 0, a);
    robo();

    glPushMatrix();
    glRotatef(angleXD, 1.0, 0.0, 0.0);
    perna_esquerda();
    glPopMatrix();

    glPushMatrix();
    glRotatef(angleXE, 1.0, 0.0, 0.0);
    perna_direita();
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();

    glFlush();
}


void rotacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
        	angleXD+=k;
        	angleXE-=k;
        	a += 0.1;

        	if (angleXD > 45) {
        		k = k*(-1);
        	}

        	if (angleXD < -45) {
        	    k = k*(-1);
        	}

           break ;
        case GLUT_KEY_DOWN :
        	angleXD-=k;
        	angleXE+=k;
        	a -= 0.1;

        	if (angleXD < 45) {
        		k = k*(-1);
        	}

        	if (angleXD > -45) {
        	   k = k*(-1);
        	 }

           break ;

        case GLUT_KEY_LEFT :
           angleY-=y;

           if (angleY < 0) {
               y = y*(1);
           }

           if (angleY > 360) {
               y = y*(1);
           }
           break ;

        case GLUT_KEY_RIGHT :
           angleY+=y;

           if (angleY > 360) {
              y = y*(1);
           }

           if (angleY < 0) {
               y = y*(1);
           }

           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Atividade 3");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(rotacoes);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}
