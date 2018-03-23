#include "./include_me.h"

float _cameraAngle = 0.0;
WindowEngine w_engine;

double angle= 0;
// this is where all drawing code belongs
void drawScreen(){
    drawHorizontalLine(.5);

    angle+= .5;
//    printf("%f\n", angle);

    glRotated(angle, 0,0,1);
    glPushMatrix(); //Save the transformations performed thus far

    glBegin(GL_LINES);
    plot(.5, .5);
    plot(3, .5);
    glEnd();

    w_engine.execute();

    glPopMatrix(); //Undo the move to the center of the triangle
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

void update(int value) {
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv){
    //Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(200,100);

    //Create the window
	glutCreateWindow("Portal 2D");
	initRendering();

    setCallbacks();

    glutTimerFunc(25, update, 0); //Add a timer

    glutMainLoop();
    return 0;
}
