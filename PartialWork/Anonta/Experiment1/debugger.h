#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

#ifndef DEBUG_H
#define DEBUG_H

using namespace std;

int CC_= 0;
#define SS printf("AAAAAAAAAAAAAAAAAAA( %d )>>\n",++CC_
#define DD(x_) cout<<">>>>( "<<++CC_<<" ) "<<#x_<<": "<<x_<<endl;



void plot(double x, double y){
    glVertex3f(x/100, y/100, 0.0);
}



void drawVerticalLine(double x){
    glBegin(GL_LINES);
    plot(x, 0);
    plot(x, 1);
    glEnd();
}

void drawHorizontalLine(double y){
    glBegin(GL_LINES);
    plot(0, y);
    plot(1, y);
    glEnd();
}

// draw a 10 by 10 grid
void drawGrid(){
    double x= 0;
    double y= 0;

    glBegin(GL_LINES);
    glColor3f(.8,.8,.8);

    for(int i= 10; i<100; i+= 10){
        plot(i, 0);
        plot(i, 100);
    }

    for(int i= 10; i<100; i+= 10){
        plot(0, i);
        plot(100, i);
    }

    glEnd();
}


#endif
