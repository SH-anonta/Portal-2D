#ifndef BULLET_H
#define BULLET_H

Color DEFAULT_BULLET_COLOR = Color(1,.1,.1);
float BULLET_SPEED= .09;

class Bullet{
public:
    Point position;
    float x_increment;
    float y_increment;

    Bullet(Point& position, float x_increment, float y_increment){
        this->position = position;
        this->x_increment = x_increment*BULLET_SPEED;
        this->y_increment = y_increment*BULLET_SPEED;
    }

    Bullet(double x, double y, float x_increment, float y_increment){
        position.x= x;
        position.y= y;
        this->x_increment = x_increment*BULLET_SPEED;
        this->y_increment = y_increment*BULLET_SPEED;
    }

    void draw(){
        setColor(DEFAULT_BULLET_COLOR);
        glBegin(GL_POINTS);
        plot(position);
        glEnd();
    }

    static void drawBullets(list<Bullet>& bullets){

        auto bullets_end = bullets.end();
        auto bullet =  bullets.begin();

//        glPointSize(3);
        setColor(DEFAULT_BULLET_COLOR);
        glBegin(GL_POINTS);

        while(bullet != bullets_end){
            plot(bullet->position);
            bullet++;
        }
        glEnd();
    }

    void updatePosition(){
        position.x += x_increment;
        position.y += y_increment;
    }
};


#endif
