#ifndef DEBUG_H
#define DEBUG_H

#define SS printf("AAAAAAAAAAAAA\n");


void drawVerticalLine(double x){
    glColor3f(.8,.8,.8);

    glBegin(GL_LINES);
    plot(x, -10);
    plot(x, 10);
    glEnd();
}

void drawHorizontalLine(double y){
    glColor3f(.8,.8,.8);

    glBegin(GL_LINES);
    plot(-3, y);
    plot(3, y);
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
