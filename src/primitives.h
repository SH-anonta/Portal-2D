#ifndef PRIMITIVE_H
#define PRIMITIVE_H


enum Direction{
    Up, Down, Left, Right
};

class Point{
public:
    double x, y;

    Point(){
    }

    Point(double x, double y){
        this->x= x;
        this->y= y;
    }
//
//    Point(Point& p){
//        x = p.x;
//        y = p.y;
//    }
};

class Color{
public:
    double r,g,b;
    Color(){
        this->r = 1;
        this->g = 1;
        this->b = 1;
    }

    Color(double r,double g,double b){
        this->r = r;
        this->g = g;
        this->b = b;
    }
};

#endif
