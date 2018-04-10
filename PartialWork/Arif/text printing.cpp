#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <GL/glut.h>

void bitmap_output(int x, int y, char *string, void *font){
    int len, i;

    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
    }
}


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,1.0);
    bitmap_output(150, 35, "..............Key..............",GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0,0.0,1.0);
    bitmap_output(30, 100, "Action------------- Player1--------------Player2       ",GLUT_BITMAP_9_BY_15);
    bitmap_output(30, 140, "Move Up----------- W --------------- 5     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 180, "Move Down----------- S--------------- 2     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 220, "Move Left----------- A --------------- 1     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 260, "Move Right----------- D --------------- 3     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 300, "Shoot----------- <Space> --------------- 0     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 340, "Open Portal 1----------- Q --------------- 4     ",GLUT_BITMAP_HELVETICA_18);
    bitmap_output(30, 380, "Open Portal 2----------- E --------------- 6     ",GLUT_BITMAP_HELVETICA_18);
    //glMatrixMode(GL_PROJECTION);
    //glPushMatrix();
    //glLoadIdentity();
    //gluPerspective(40.0, 1.0, 0.1, 20.0);
    // glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    //gluLookAt(0.0, 0.0, 4.0,  /* eye is at (0,0,30) */
    //  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    //    0.0, 1.0, 0.);      /* up is in postivie Y direction */
    //glPushMatrix();
    //glTranslatef(0, 0, -4);
    //glRotatef(50, 0, 1, 0);
    //  stroke_output(-2.5, 1.1, "  This is written in a");
    //stroke_output(-2.5, 0, " GLUT stroke font.");
    //stroke_output(-2.5, -1.1, "using 3D perspective.");
    //glPopMatrix();
    //glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();
    //glMatrixMode(GL_PROJECTION);
    //glPopMatrix();
    //glMatrixMode(GL_MODELVIEW);
    glFlush();
}

void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScalef(1, -1, 1);
    glTranslatef(0, -h, 0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT bitmap & stroke font example");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0, 0);
    glLineWidth(3.0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;             /* ANSI C requires main to return int. */
}
