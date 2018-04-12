#ifndef PRIMITIVE_H
#define PRIMITIVE_H


enum Direction{
    Up, Down, Left, Right
};

Direction getOppositeDirection(Direction d){
    if(d == Up) return Down;
    if(d == Down) return Up;
    if(d == Left) return Right;
    if(d == Right) return Left;
}

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
