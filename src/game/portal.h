#ifndef PORTAL_H
#define PORTAL_H

const float PORTAL_LENGTH= 0.25;
const float PORTAL_THICKNESS= 0.05;
const Color DEFAULT_PORTAL_COLOR = Color(.6, 0, 0);

class Portal{
public:
    vector<Point> points;
    Color color = DEFAULT_PORTAL_COLOR;
    Portal* linked_portal = nullptr;
    Point centroid;
    float angle = 90;

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

        centroid = getCentroid();
    }

    void draw(){
        setColor(color);
        glPushMatrix();
        if(angle > 0){
            angle-= 3;
        }


        glTranslatef(centroid.x, centroid.y, 0);
//        glTranslatef(points[0].x, points[0].y, 0);
        glRotatef(angle, 0,0,0);
//        glTranslatef(-1*points[0].x, -1*points[0].y, 0);
        glTranslatef(-1*centroid.x, -1*centroid.y, 0);


        glBegin(GL_QUADS);
        plot(points);
        glEnd();


        glPopMatrix();
    }

    Point getCentroid(){
        return Point((points[0].x+points[1].x+points[2].x+points[3].x)/4,
                     (points[0].y+points[1].y+points[2].y+points[3].y)/4);
    }

    void setLinkedPortal(Portal& p){
        linked_portal= &p;
        p.linked_portal = this;
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
                Point adj = getBulletPositionAdjustment(linked_portal->orientation);

                bullet.position = Point(p.x+collision_point+adj.x, p.y+adj.y);
            }
            else{
                Point adj = getBulletPositionAdjustment(linked_portal->orientation);

                bullet.position = Point(p.x+adj.x, p.y+collision_point+adj.y);
            }

            bullet.updateDirection(getOppositeDirection(linked_portal->orientation));
        }
    }

    bool detectCollision(Player& player){

        float buffer = .08;
        return points[0].x <= player.next_position.x+buffer &&
               points[1].x >= player.next_position.x-buffer &&
               points[0].y <= player.next_position.y+buffer &&
               points[3].y >= player.next_position.y-buffer;
    }

    // position adjustment after teliportation
    Point getPlayerPositionAdjustment(Direction d){

        // .06 is just above the thickness of portals
        if(d == Left)
            return Point(.2,0);
        if(d == Right)
            return Point(-.11,0);
        if(d == Up)
            return Point(0,-.11);
        if(d == Down)
            return Point(0,.2);

    }

    void teleportPlayer(Player& player){
        if(detectCollision(player)){
//            printf("Portal collision\n");

            Point& p = linked_portal->points[0];
            float collision_point = 0;

            //calculate collision point
            if(orientation == Up || orientation == Down){
                collision_point = player.next_position.x - points[0].x;
            }
            else{
                collision_point = player.next_position.y - points[0].y;
            }

            if(linked_portal->orientation == Up || linked_portal->orientation == Down){
                Point adj = getPlayerPositionAdjustment(linked_portal->orientation);

                player.next_position = Point(p.x+collision_point+adj.x, p.y+adj.y);
            }
            else{
                Point adj = getPlayerPositionAdjustment(linked_portal->orientation);

                player.next_position = Point(p.x+adj.x, p.y+collision_point+adj.y);
            }

            player.updateDirection(getOppositeDirection(linked_portal->orientation));
        }
    }

    // get how much position should be adjusted for a given orientation in order to avoid collision after teleportation
    Point getBulletPositionAdjustment(Direction d){

        // .06 is just above the thickness of portals
        if(d == Left)
            return Point(.08,0);
        if(d == Right)
            return Point(-.08,0);
        if(d == Up)
            return Point(0,-.08);
        if(d == Down)
            return Point(0,.08);

    }

};

#endif
