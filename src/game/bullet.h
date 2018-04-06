#ifndef BULLET_H
#define BULLET_H

Color DEFAULT_BULLET_COLOR = Color(1,1,1);
class Bullet{
public:
    Point position;

    Bullet(Point& position){
        this->position = position;
    }

    Bullet(double x, double y){
        position.x= x;
        position.y= y;
    }

    void draw(){
        setColor(DEFAULT_BULLET_COLOR);
        glBegin(GL_POINTS);
        plot(position);
        glEnd();
    }
};


#endif
