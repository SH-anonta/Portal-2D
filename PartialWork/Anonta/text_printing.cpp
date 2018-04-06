#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <string>

#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;
//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;


void drawCircle(float r, bool solid= true){

    if(solid) glBegin(GL_POLYGON);
    else glBegin(GL_LINES);

	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x,y);
	}
	glEnd();
}

void plot(double x, double y){
    glVertex2f(x,y);
}

void drawFan(){
    glColor3f(1,0,.5);

    drawCircle(.5);
    glBegin(GL_QUADS);

    glColor3f(.3, 1,.8);
    // top blade
    plot(.4, .5);
    plot(.4, 2.5);
    plot(-.4, 2.5);
    plot(-.4, .5);

    // right blade
    plot(.5, -.4);
    plot(2.5, -.4);
    plot(2.5, .4);
    plot(.5, .4);

    // left blade
    plot(-2.5, -.4);
    plot(-.5, -.4);
    plot(-.5, .4);
    plot(-2.5, .4);

    // bottom blade
    plot(-.4, -2.5);
    plot(.4, -2.5);
    plot(.4, -.5);
    plot(-.4, -.5);

	glEnd();
}

void drawScreen(){
//    glRasterPos2f(1280, 720);
    glColor3f(1.0f, 1.0f, 1.0f);

    glPushMatrix();

    glTranslatef(0, 2,0);
//    string menu = "Hello!";
//    int len = menu.length();
//    for (int i = 0; i < len; i++) {
//        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, menu[i]);
//    }

    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');

    glPopMatrix();
}

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
//	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

    drawScreen();

	glutSwapBuffers();
}

void update(int value) {


//	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(200,100);

	//Create the window
	glutCreateWindow("Transformations");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);

	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0); //Add a timer

	glutMainLoop();
	return 0;
}


