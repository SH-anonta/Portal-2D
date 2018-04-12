#ifndef PORTAL_H
#define PORTAL_H

const float PORTAL_LENGTH= 0.3;
const Color DEFAULT_PORTAL_COLOR = Color(.8, .4, .3);

class Portal{
public:
    Point position;
    Point pointa;
    Point pointb;
    Color color = DEFAULT_PORTAL_COLOR;

    Direction orientation;

    Portal(){

    }
    Portal(float x, float y, Direction ori){
        position.x = x;
        position.y = y;
        orientation = ori;

        if(orientation == Up || orientation == Down){
            pointa.x = position.x - PORTAL_LENGTH;
            pointa.y = position.y;

            pointb.x = position.x + PORTAL_LENGTH;
            pointb.y = position.y;
        }
        else{
            pointa.x = position.x;
            pointa.y = position.y-PORTAL_LENGTH;

            pointb.x = position.x;
            pointb.y = position.y+PORTAL_LENGTH;
        }


    }

    void draw(){
        // a and b are two end points of the line that represents the portal
        // a is left and b is right, in case the portal has orientation Up or Down
        // a is bottom and b is top, in case the portal has orientation Left or Right
        glLineWidth(5);
        setColor(color);
        glBegin(GL_LINES);
        plot(pointa);
        plot(pointb);
        glEnd();
    }

};

#endif
