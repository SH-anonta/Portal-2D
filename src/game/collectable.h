#ifndef COLLECTABLE_H
#define COLLECTABLE_H

class Collectable{
protected:
    const float MAX_DIMENSION = .08;    // Max and min height
    Point position;
public:

    Collectable(const Point& pos){
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

    bool detectCollision(BasePlayer* player){
        return pointDistance(player->getPosition(), position) < 0.18;
    };

    virtual void updateState(){
    }

    virtual bool checkExistance(){
        return true;
    }

    // when the player has a collision with this collectable,
    // use the returned wrapper to change the player's behavior
    virtual BasePlayer* getWrappedPlayer(BasePlayer* player)= 0;

    void setPosition(const Point& pos){
        position = pos;
    }
};

class HealthCollectable: public Collectable{
    vector<Point> points;
public:

    HealthCollectable(const Point& pos): Collectable(pos){
        points.push_back(Point(pos.x -.08, pos.y));
        points.push_back(Point(pos.x +.08, pos.y));
        points.push_back(Point(pos.x, pos.y -.08));
        points.push_back(Point(pos.x, pos.y +.08));
    }

    void draw() override{
        glLineWidth(5);
        glColor3f(0,1,0);
        glBegin(GL_LINES);

        for(Point& p : points){
            plot(p);
        }

        glEnd();
    }

    BasePlayer* getWrappedPlayer(BasePlayer* player) override{
        return new AcquireHealth(player);
    }
};


class ShieldCollectable: public Collectable{
    vector<Point> points;

public:

    ShieldCollectable(const Point& pos): Collectable(pos){
        const float d = .08;
        points.push_back(Point(pos.x, pos.y -d));
        points.push_back(Point(pos.x+.06, pos.y -.05));
        points.push_back(Point(pos.x+.06, pos.y +d));
        points.push_back(Point(pos.x-.06, pos.y +d));
        points.push_back(Point(pos.x-.06, pos.y -.05));
    }

    void draw() override{
//        glLineWidth(5);
        glColor3f(0,1,0);
        glBegin(GL_POLYGON);

        for(Point& p : points){
            plot(p);
        }

        glEnd();
    }

    BasePlayer* getWrappedPlayer(BasePlayer* player) override{
        return new PlayerShield(player);
    }
};



class BearTrapCollectable: public Collectable{

public:

    BearTrapCollectable(const Point& pos): Collectable(pos){


    }

    void draw() override{
//        glLineWidth(5);
        glColor3f(.8,0,0);

        float d= .1;

        glPushMatrix();
        glTranslatef(position.x, position.y, 0);

        glLineWidth(3);
        glBegin(GL_LINES);

        //bottom line
        plot(-d, -d);
        plot(d, -d);

        // top line
        plot(-d, d);
        plot(d, d);

        glEnd();

        glLineWidth(1);
        // middle bars
        glBegin(GL_LINES);
        plot(-d, -d);
        plot(-d, d);

        plot(-.05, -d);
        plot(-.05, d);

        plot(0, -d);
        plot(0, d);

        plot(.05, -d);
        plot(.05, d);

        plot(d, -d);
        plot(d, d);

        glEnd();

        glPopMatrix();
    }

    BasePlayer* getWrappedPlayer(BasePlayer* player) override{
        return new BearTrap(player);
    }
};

#endif
