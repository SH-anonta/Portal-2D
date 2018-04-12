#ifndef PORTAL_H
#define PORTAL_H

const float PORTAL_LENGTH= 0.5;
const float PORTAL_THICKNESS= 0.05;
const Color DEFAULT_PORTAL_COLOR = Color(1, 0, 0);

class Portal{
public:
    vector<Point> points;
    Color color = DEFAULT_PORTAL_COLOR;

    Direction orientation;

    Portal(){

    }

    Portal(float x, float y, Direction ori){
        orientation = ori;

        // order in which points are inserted is very important
        // points must be inserted in clockwise order
        // bottom left, bottom right, top right then top left
        if(orientation == Up){
            points.push_back(Point(x-PORTAL_LENGTH, y));
            points.push_back(Point(x+PORTAL_LENGTH, y));
            points.push_back(Point(x+PORTAL_LENGTH, y+PORTAL_THICKNESS));
            points.push_back(Point(x-PORTAL_LENGTH, y+PORTAL_THICKNESS));
        }
        else if(orientation == Down){
            points.push_back(Point(x-PORTAL_LENGTH, y-PORTAL_THICKNESS));
            points.push_back(Point(x+PORTAL_LENGTH, y-PORTAL_THICKNESS));
            points.push_back(Point(x+PORTAL_LENGTH, y));
            points.push_back(Point(x-PORTAL_LENGTH, y));
        }
        else if(orientation == Left){
            points.push_back(Point(x-PORTAL_THICKNESS, y-PORTAL_LENGTH));
            points.push_back(Point(x, y-PORTAL_LENGTH));
            points.push_back(Point(x, y+PORTAL_LENGTH));
            points.push_back(Point(x-PORTAL_THICKNESS, y+PORTAL_LENGTH));
        }
        else if(orientation == Right){
            points.push_back(Point(x, y-PORTAL_LENGTH));
            points.push_back(Point(x+PORTAL_THICKNESS, y-PORTAL_LENGTH));
            points.push_back(Point(x+PORTAL_THICKNESS, y+PORTAL_LENGTH));
            points.push_back(Point(x, y+PORTAL_LENGTH));
        }
        else{
            printf("Error: invalid direction encountered");
        }


    }

    void draw(){
        setColor(color);

        glBegin(GL_QUADS);
        plot(points);
        glEnd();
    }

};

#endif
