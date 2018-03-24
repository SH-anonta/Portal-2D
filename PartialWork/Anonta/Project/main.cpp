#include "./include_me.h"

WindowEngine w_engine(new GameWindow());
//WindowEngine w_engine(new SplashScreenWindow());

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float angle= 0.0;

// this is where all drawing code belongs
void drawScreen(){
//    drawHorizontalLine(.5);
    glPointSize(5);

    w_engine.execute();
//    drawVerticalLine();

//    glPushMatrix(); //Save the transformations performed thus far
//	glTranslatef(1.0, 1.0, 0.0);
//	//glScalef(0.5,0.5,0); //Move to the center of the trapezoid
//    glRotatef(_ang_tri ,0.0, 0.0, 1.0); //Rotate about the z-axis
//
//	glBegin(GL_TRIANGLES);
//
//	//Triangle
//	glVertex3f(0.5, -0.5, 0.0);
//	glVertex3f(0.0, 0.5, 0.0);
//	glVertex3f(-0.5, -0.5, 0.0);
//
//	glEnd();
}


void update(int value) {
//	glutPostRedisplay();
//	glutTimerFunc(25, update, 0);

    _angle += 2.0f;
	if (_angle > 360) {
		_angle -= 360;
	}
	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}


//DO NOT TOUCH THIS
// put drawing code in drawScreen function
void updateScreen(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective

	glLoadIdentity(); //Reset the drawing perspective
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units
	glPushMatrix(); //Save the transformations performed thus far

    drawScreen();

    glPopMatrix(); //Undo the move to the center of the triangle
    glutSwapBuffers();
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

// sets key status on and off
void keyHandler(unsigned char key, int x, int y){
    w_engine.keyPress(key, x, y);
}

// handles special key presses line arrow keys
void specialKeyHandler(int key, int x, int y){
    w_engine.keyPress(key, x, y);
}


void setCallbacks(){
    glutDisplayFunc(updateScreen);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyHandler);
	glutSpecialFunc(specialKeyHandler);
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv){
    //Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(200,100);

    //Create the window
	glutCreateWindow("Portal 2D");
	initRendering();

    setCallbacks();

    glutTimerFunc(25, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}
