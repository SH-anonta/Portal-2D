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
        return new PlayerShield(player);
    }
};

#endif
