#include "./include_me.h"

float _angle = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;

void drawScreen(){
    glBegin(GL_LINES);

    plot(.5, .5);
    plot(3, .5);

    glEnd();
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

void setCallbacks(){
    glutDisplayFunc(updateScreen);
	glutReshapeFunc(handleResize);
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
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


    glutMainLoop();
    return 0;
}
