#ifndef COLLECTABLE_H
#define COLLECTABLE_H

class Collectable{
protected:
    const float MAX_DIMENSION = .08;    // Max and min height
    Point position;
public:

    Collectable(Point& pos){
        position = pos;
    }

    virtual void draw(){
        glColor3f(0,1,0);
        glBegin(GL_LINE_LOOP);
        float d = .08;
        plot(-d,-d);
        plot(d,-d);
        plot(d,d);
        //      plot(-d,d);
        glEnd();
    }

    virtual bool detectCollision(BasePlayer& player){
        return pointDistance(player.getPosition(), position) < 0.18;
    };

    virtual void updateState(){
    }

    virtual bool checkExistance(){
        return true;
    }
};

class Health: public Collectable{
public:
    Health(Point& pos): Collectable(pos){

    }
};

#endif
