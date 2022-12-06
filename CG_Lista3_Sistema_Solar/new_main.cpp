#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <cmath>

#include "Complementary/light.h"

using namespace std;

float razaoaspecto;
float earthAngleTrans, moonAngleTrans;
float earthAngleRotat, moonAngleRotat, sunAngleRotat;
GLuint texturaSol, texturaLua, texturaTerra, texturaEstrelas;

void keyboardAct (unsigned char key, int x, int y) {

    switch (key) {

        case 27:

            exit(0);
        break;

        case 'Z':
        case 'z':

            if (m < 1.0)
                m += 0.01;
            /*Aumentar a intensidade de luz uniforme*/
        break;

        case 'X':
        case 'x':

            if (m > 0.0)
                m -= 0.01;
            /*Diminuir a intensidade de luz uniforme*/
        break;

        case 'C':
        case 'c':

            if (d < 1.0) 
                d += 0.01;
            /*Aumentar a intensidade de luz difusa*/
        break;

        case 'V':
        case 'v':

            if (d > 0.0)
                d -= 0.01;

            /*Diminuir a intensidade de luz difusa*/
        break;

        case 'B':
        case 'b':

            if (e < 1.0)
                e += 0.01;
            /*Aumentar a intensidade de luz especular*/
        break;

        case 'N':
        case 'n':

            if (e > 0.0)
                e -= 0.01;
            /*Diminuir a intensidade de luz especular*/
        break;    
    }
}

void lightSetup() {

    float carryDif0[] = { d, d, d, 1.0 }; 
    float carrySpec0[] = { e, e, e, 1.0 };
    float carryPos0[] = { 0.0, 0.0, 0.0, p };
    float carryglobAmb[] = { m, m, m, 1.0 };

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, carryDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, carrySpec0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, carryglobAmb);        
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, false);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);// teria que variarcmom pressionamento de tela
}

void criaEsfera (int raio, int stacks, int columns) {

    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, raio, 200, 200);
    gluDeleteQuadric(quadObj);
}

void loadTextureEsfera () {

    texturaSol = SOIL_load_OGL_texture
    (
        "jpg_archives/sol.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

        if (texturaSol == 0) 
        printf("Erro do SOIL: '%s' + %s\n", SOIL_last_result(),"/JPG Archives/sol.jpg");

    texturaLua = SOIL_load_OGL_texture
    (
        "jpg_archives/lua.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

        if (texturaLua == 0) 
        printf("Erro do SOIL: '%s' + %s\n", SOIL_last_result(),"/JPG Archives/lua.jpg");

    texturaTerra = SOIL_load_OGL_texture
    (
        "jpg_archives/terra.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
        if (texturaTerra == 0) 
        printf("Erro do SOIL: '%s' + %s\n", SOIL_last_result(),"/JPG Archives/terra.jpg");

    texturaEstrelas = SOIL_load_OGL_texture
    (
        "jpg_archives/estrelas.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    
        if (texturaTerra == 0) 
        printf("Erro do SOIL: '%s' + %s\n", SOIL_last_result(),"/JPG Archives/estrelas.jpg");
}

void cameraSetup () {
    gluLookAt(50,105,30,
              0,0,0,
              0,1,0);
}

float matAmbAndDif[4] = {1,1,1,1};
float matSpec[4] = {1,1,1,1};

void inicializa() {
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0); 
    glEnable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 70);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    loadTextureEsfera();
    glShadeModel(GL_PHONG_HINT_WIN);
}

void drawSolidSphere(double radius, int stacks, int columns)
{
    GLUquadric* quadObj = gluNewQuadric(); // cira uma quadrica 
    gluQuadricDrawStyle(quadObj, GLU_FILL); // estilo preenchido
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE); // chama 01 glTexCoord por vértice
    gluSphere(quadObj, radius, stacks, columns); // cria os vértices de uma esfera
    gluDeleteQuadric(quadObj);
}

void drawObject(double raio, GLuint textura, int x, int z, float angle)
{

    int y = 0;

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textura);
    glTranslatef(x,y,z);
    glRotatef(angle, 0, 1, 0);
    drawSolidSphere(raio, 200, 200);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
 
void drawScene()
{

    float pos_x, pos_y;

    pos_x = 70 * cos(earthAngleTrans);
    pos_y = 70 * sin(earthAngleTrans);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    cameraSetup();
    lightSetup();

    drawObject(20,texturaSol, 0, 0, sunAngleRotat);
    drawObject(150, texturaEstrelas, 0, 0, 0);

    glEnable(GL_LIGHTING);


    drawObject(8,texturaTerra, pos_x, pos_y, earthAngleRotat);
    drawObject(3,texturaLua, pos_x + 16 * cos(moonAngleTrans), pos_y + 16 * sin(moonAngleTrans), moonAngleRotat);

    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void translateSpheres() {

    if (earthAngleTrans >= 0 && earthAngleTrans <= 360)
        earthAngleTrans += 0.01;

    if (moonAngleTrans >= 0 && moonAngleTrans <= 360)
        moonAngleTrans += 0.03;

    if (earthAngleTrans > 360)
        earthAngleTrans = 0;
    
    if (moonAngleTrans > 360)
        moonAngleTrans = 0;

    if (earthAngleRotat >= 0 && earthAngleRotat <= 360)
        earthAngleRotat += 0.5;
    
    if (moonAngleRotat >= 0 && moonAngleRotat <= 360)
        moonAngleRotat += 0.2;

    if (sunAngleRotat >= 0 && sunAngleRotat <= 360)
        sunAngleRotat += 0.1;

    if (earthAngleRotat > 360)
        earthAngleRotat = 0;

    if (moonAngleRotat > 360)
        moonAngleRotat = 0;

    if (sunAngleRotat > 360)
        sunAngleRotat = 0;
}

void timer(int t) {

    translateSpheres();

    glutPostRedisplay();
    glutTimerFunc(t, timer, t);
}

void redimension(int width, int height) {

    razaoaspecto = (float) glutGet(GLUT_WINDOW_WIDTH)/(float) glutGet(GLUT_WINDOW_HEIGHT);

    glViewport (0, 0, width, height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-razaoaspecto, razaoaspecto, -1, 1, 1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Terra/Lua/Sol");

    inicializa();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(redimension);
    glutKeyboardFunc(keyboardAct);
    glutTimerFunc(8, timer, 8);
    //glutPassiveMotionFunc();
    //glutIdleFunc();

    glutMainLoop();

    return 0;
}