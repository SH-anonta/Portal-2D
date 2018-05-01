#ifndef BULLET_H
#define BULLET_H

Color DEFAULT_BULLET_COLOR = Color(1,.1,.1);
float BULLET_SPEED= .05;

class Bullet{
public:
    Point position;
    float x_increment;
    float y_increment;

    Bullet(Point& position, Direction direction){
        this->position = position;
        updateXYIncrements(direction);
    }

    Bullet(double x, double y, Direction direction){
        position.x= x;
        position.y= y;
        updateXYIncrements(direction);
    }

    void draw(){
        glPointSize(4);
        setColor(DEFAULT_BULLET_COLOR);
        glBegin(GL_POINTS);
        plot(position);
        glEnd();
    }

    static void drawBullets(list<Bullet>& bullets){

        auto bullets_end = bullets.end();
        auto bullet =  bullets.begin();

        glPointSize(4);
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

    void updateXYIncrements(Direction direction){
        x_increment= 0;
        y_increment= 0;

        if(direction == Up)
            y_increment= 1;
        else if(direction == Down)
            y_increment= -1;
        else if(direction == Left)
            x_increment= -1;
        else if(direction == Right)
            x_increment= 1;

        this->x_increment = x_increment*BULLET_SPEED;
        this->y_increment = y_increment*BULLET_SPEED;
    }

    void updateDirection(Direction direction){
        updateXYIncrements(direction);
    }
};


#endif
