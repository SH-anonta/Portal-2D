#ifndef MAPS_H
#define MAPS_H

// Points that define the wall, should be in counter clockwise order
// this is important for collision detection
class Wall{
public:
    vector<Point> points;
    Color color;

    Wall(vector<Point>& pts){
        points = pts;

        color.r= .8;
        color.g= .5;
        color.b= .7;
    }

    void draw(){
        setColor(color);

        glBegin(GL_QUADS);
        for(int i= 0; i<4; i++){
            plot(points[i]);
        }
        glEnd();
    }

    static Wall createWall(double w, double h){
        vector<Point> wall_points= {
            Point(0,0),
            Point(w, 0),
            Point(w, h),
            Point(0, h)
        };

        return Wall(wall_points);
    }

    void translate(double tx, double ty){
        for(int i= 0; i<4; i++){
            points[i].x+= tx;
            points[i].y+= ty;
        }
    }
};

class Map{
public:

};


#endif
