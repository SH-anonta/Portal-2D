#ifndef PLOT_H
#define PLOT_H

// all the plotting helper functions

void plot(double x, double y){
    glVertex3f(x,y, 0);
}

void plot(Point& p){
//    printf("%f %f", p.x, p.y);
//    getchar();

    glVertex3f(p.x,p.y, 0);
}

void plot(vector<Point> points){
}

void setColor(Color& c){
    glColor3f(c.r, c.b, c.g);
}
#endif
