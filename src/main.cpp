#include "./include_me.h"

WindowEngine w_engine(new SplashScreenWindow());
//Window    Engine w_engine(new HelpScreenWindow(NULL));
//WindowEngine w_engine(new GameWindow());

float _cameraAngle = 0.0;


// this is where all drawing code belongs
void drawScreen(){
    w_engine.execute();
}

void update(int value) {
	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(10, update, 0);
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
    w_engine.specialKeyPress(key, x, y);
}

void keyUpHandler(unsigned char key, int x, int y){
    w_engine.keyUp(key, x, y);
}

void specialKeyUpHandler(int key, int x, int y){
    w_engine.specialKeyUp(key, x, y);
}

void idle(){
    glutPostRedisplay();
}

void setCallbacks(){
    glutDisplayFunc(updateScreen);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyHandler);
	glutKeyboardUpFunc(keyUpHandler);
	glutSpecialFunc(specialKeyHandler);
	glutSpecialUpFunc(specialKeyUpHandler);

//	glutIdleFunc(idle);
}

//Initializes 3D rendering
void initRendering() {
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main(int argc, char** argv){
    //Initialize GLUT
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,700);
	glutInitWindowPosition(300,50);

	glutCreateWindow("Portal 2D");
//    glutFullScreen();

	initRendering();
    setCallbacks();
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
