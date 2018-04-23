#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

Color BACKGROUND_COLOR= Color(.05, .1, .15);
Color BACKGROUND_GRID_COLOR= Color(.15, .15, .3);
Color DEFAULT_TEXT_COLOR= Color(0.2,0.6,.9);

void drawMainBackground(){
    setColor(BACKGROUND_GRID_COLOR);

    glBegin(GL_LINES);
    // draw horizontal lines
    for(float r= -3; r<3; r+= .6){
        plot(-3, r);
        plot(3, r);
    }

    // draw vertical lines
    for(float c= -3; c<3; c+= .6){
        plot(c, -3);
        plot(c, 3);
    }
    glEnd();

    setColor(BACKGROUND_COLOR);
    glBegin(GL_QUADS);
    plot(-3,-3);
    plot(3,-3);
    plot(3,3);
    plot(-3,3);

    glEnd();
}

#endif
