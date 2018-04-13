#ifndef PORTAL_H
#define PORTAL_H

const float PORTAL_LENGTH= 0.3;
const float PORTAL_THICKNESS= 0.06;
const Color DEFAULT_PORTAL_COLOR = Color(1, 0, 0);

class Portal{
public:
    vector<Point> points;
    Color color = DEFAULT_PORTAL_COLOR;
    Portal* linked_portal = nullptr;

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

    void setLinkedPortal(Portal* p){
        linked_portal= p;
    }

    bool detectCollision(Bullet& bullet){
        return points[0].x <= bullet.position.x &&
               points[1].x >= bullet.position.x &&
               points[0].y <= bullet.position.y &&
               points[3].y >= bullet.position.y;
    }

    // if bullet is on portal, teleport it to new position
    Point teleportBullet(Bullet& bullet){
        if(detectCollision(bullet)){
//            printf("Portal collision\n");

            Point& p = linked_portal->points[0];
            float collision_point = 0;

            if(orientation == Up || orientation == Down){
                collision_point = bullet.position.x - points[0].x;
            }
            else{
                collision_point = bullet.position.y - points[0].y;
            }

            if(linked_portal->orientation == Up || linked_portal->orientation == Down){
                Point adj = getPositionAdjustment(linked_portal->orientation);

                bullet.position = Point(p.x+collision_point+adj.x, p.y+adj.y);
            }
            else{
                Point adj = getPositionAdjustment(linked_portal->orientation);

                bullet.position = Point(p.x+adj.x, p.y+collision_point+adj.y);
            }

            bullet.updateDirection(getOppositeDirection(linked_portal->orientation));
        }
    }

    // get how much position should be adjusted for a given orientation in order to avoid collision after teleportation
    Point getPositionAdjustment(Direction d){

        // .06 is just above the thickness of portals
        if(d == Left)
            return Point(.06,0);
        if(d == Right)
            return Point(-.06,0);
        if(d == Up)
            return Point(0,-.06);
        if(d == Down)
            return Point(0,.06);

    }

};

#endif
