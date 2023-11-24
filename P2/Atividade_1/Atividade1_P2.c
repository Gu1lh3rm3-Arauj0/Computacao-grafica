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

#define MAX_NO_TEXTURES 5

float thetaX = 0.0;
float thetaY = 0.0;

GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "surface1.bmp",
        "surface2.bmp",
        "surface3.bmp",
        "surface4.bmp",
        "surface5.bmp"
};

int k;

GLUquadricObj *obj;

GLfloat angleX = 0.0f;
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
    gluLookAt(4.0, 2.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 2.0, 8.0);
    glViewport(0, 0, 500, 500);

    lightning();
}

void cubo() {
    glBegin(GL_POLYGON);
        glNormal3f(-0.1, 0.1, 0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.1, 0.1, 0.1);

        glNormal3f(0.1, 0.1, 0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.1, 0.1, 0.1);

        glNormal3f(0.1, 0.1, 0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.1, 0.1, 0.1);

        glNormal3f(-0.1, -0.1, 0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.1, -0.1, 0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.1, 0.1, -0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.1, 0.1, -0.1);

        glNormal3f(0.1, 0.1, -0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.1, 0.1, -0.1);

        glNormal3f(0.1, -0.1, -0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.1, -0.1, -0.1);

        glNormal3f(-0.1, -0.1, -0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.1, -0.1, 0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.1, -0.1, 0.1);

        glNormal3f(0.1, 0.1, 0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.1, 0.1, 0.1);

        glNormal3f(0.1, 0.1, -0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.1, 0.1, -0.1);

        glNormal3f(0.1, -0.1, -0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.1, -0.1, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.1, -0.1, 0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.1, -0.1, 0.1);

        glNormal3f(-0.1, 0.1, 0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-0.1, 0.1, 0.1);

        glNormal3f(-0.1, 0.1, -0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-0.1, 0.1, -0.1);

        glNormal3f(-0.1, -0.1, -0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.1, 0.1, 0.1);  // Top face
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.1, 0.1, 0.1);

        glNormal3f(0.1, 0.1, 0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.1, 0.1, 0.1);

        glNormal3f(0.1, 0.1, -0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.1, 0.1, -0.1);

        glNormal3f(-0.1, 0.1, -0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.1, 0.1, -0.1);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-0.1, -0.1, 0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.1, -0.1, 0.1);

        glNormal3f(0.1, -0.1, 0.1);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.1, -0.1, 0.1);

        glNormal3f(0.1, -0.1, -0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.1, -0.1, -0.1);

        glNormal3f(-0.1, -0.1, -0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.1, -0.1, -0.1);
    glEnd();
}


void cuboFino() {
    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.04, 0.04, 0.04);

        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.04, 0.04, 0.04);

        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.04, -0.04, 0.04);

        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.04, -0.04, 0.04);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.04, 0.04, -0.04);

        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.04, 0.04, -0.04);

        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.04, -0.04, -0.04);

        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.04, -0.04, -0.04);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0.04, -0.04, 0.04);

        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.04, 0.04, 0.04);

        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.04, 0.04, -0.04);

        glNormal3f(1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0.04, -0.04, -0.04);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.04, -0.04, 0.04);

        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(-0.04, 0.04, 0.04);

        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(-0.04, 0.04, -0.04);

        glNormal3f(-1.0, 0.0, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.04, -0.04, -0.04);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.04, 0.04, 0.04);

        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.04, 0.04, 0.04);

        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.04, 0.04, -0.04);

        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.04, 0.04, -0.04);
    glEnd();

    glBegin(GL_POLYGON);
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.04, -0.04, 0.04);

        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.04, -0.04, 0.04);

        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.04, -0.04, -0.04);

        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.04, -0.04, -0.04);
    glEnd();
}


void robo() {
	glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.0, 0.5, 0.0);
    cubo();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    cubo();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.0, 0.05, 0.0);
    cubo();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.056, -0.13, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.056, -0.20, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.056, -0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.056, -0.39, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.056, -0.13, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.056, -0.20, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.056, -0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.056, -0.39, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.17, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.25, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.36, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(-0.44, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.17, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.25, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.36, 0.31, 0.0);
    cuboFino();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture_id[k]);
    glPushMatrix();
    glTranslatef(0.44, 0.31, 0.0);
    cuboFino();
    glPopMatrix();
}

void displayFunc(){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);

        glPushMatrix();
        glRotatef(angleX,1.0,0.0,0.0);
        glRotatef(angleY,0.0,1.0,0.0);
        robo();
        glPopMatrix();

        glFlush();
}

void rotacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_UP :
           angleX+=15;
           break ;
        case GLUT_KEY_DOWN :
           angleX-=15;
           break ;
        case GLUT_KEY_LEFT :
           angleY-=15;
           break ;
        case GLUT_KEY_RIGHT :
           angleY+=15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void keyboard(unsigned char key, int x, int y){

     switch (key){
        case '1' :
        	k = 0;
           break ;
        case '2' :
        	k = 1;
           break ;
        case '3' :
        	k = 2;
           break ;
        case '4' :
        	k = 3;
           break ;
        case '5' :
           k = 4;
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
    glutCreateWindow("Atividade 1");
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(rotacoes);
    init();
    initTexture();
    glutMainLoop();
    return 0;
}
