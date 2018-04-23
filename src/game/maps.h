#ifndef MAPS_H
#define MAPS_H


Color DEFAULT_WALL_COLOR= Color(.2, .7, .5);
Color DEFAULT_PIT_COLOR= Color(0.1,0.05,0.05);
Color MAP_BACKGROUND_COLOR= Color(.04, .12, .08);
Color MAP_BACKGROUND_GRID_COLOR= Color(.15, .3, .15);


// Points that define the wall, should be in counter clockwise order
// this is important for collision detection
class Wall{
public:
    vector<Point> points;

    Wall(vector<Point>& pts){
        points = pts;
    }

    Wall(float w, float h, float translate_x= 0, float translate_y= 0){
        points= {
            Point(translate_x, translate_y),
            Point(translate_x+w, translate_y),
            Point(translate_x+w, translate_y+h),
            Point(translate_x, translate_y+h)
        };
    }

    // this function is meant to be called by the Map class only
    // call to setColor glBegin and glEnd have been omitted intentionally for performance concerns
    void draw(){
//        setColor(color);

//        glBegin(GL_QUADS);
        for(int i= 0; i<4; i++){
            plot(points[i]);
        }
//        glEnd();
    }

    void translate(double tx, double ty){
        for(int i= 0; i<4; i++){
            points[i].x+= tx;
            points[i].y+= ty;
        }
    }

    bool detectCollision(Player& player){
        float buffer = .06;
        return points[0].x <= player.next_position.x+buffer &&
               points[1].x >= player.next_position.x-buffer &&
               points[0].y <= player.next_position.y+buffer &&
               points[3].y >= player.next_position.y-buffer;
    }

    bool detectCollision(Bullet& bullet){
        return points[0].x <= bullet.position.x &&
               points[1].x >= bullet.position.x &&
               points[0].y <= bullet.position.y &&
               points[3].y >= bullet.position.y;
    }
};

class Pit{
public:
    // points that make up the pit (a quad)
    vector<Point> points;

    Pit(vector<Point>& pts){
        points = pts;
    }

    Pit(float w, float h, float translate_x= 0, float translate_y= 0){
        points= {
            Point(translate_x, translate_y),
            Point(translate_x+w, translate_y),
            Point(translate_x+w, translate_y+h),
            Point(translate_x, translate_y+h)
        };

    }

    // this function is meant to be called by the Map class only
    // call to setColor glBegin and glEnd have been omitted intentionally for performance concerns
    void draw(){
//        setColor(color);

//        glBegin(GL_QUADS);
        for(int i= 0; i<4; i++){
            plot(points[i]);
        }
//        glEnd();
    }


    void translate(double tx, double ty){
        for(int i= 0; i<4; i++){
            points[i].x+= tx;
            points[i].y+= ty;
        }
    }

    bool detectCollision(Player& player){

        return points[0].x <= player.next_position.x &&
               points[1].x >= player.next_position.x &&
               points[0].y <= player.next_position.y &&
               points[3].y >= player.next_position.y;
    }
};

class Map{
    vector<Wall> walls;
    vector<Pit> pits;
    string map_name;
public:
    Point p1position;
    Point p2position;

    Map(){
    }

    Map(vector<Wall>& walls){
        this->walls = walls;
    }

    void draw(){
        setColor(DEFAULT_WALL_COLOR);
        glBegin(GL_QUADS);
        for(int i= 0, len= walls.size(); i<len; i++){
            walls[i].draw();
        }

        setColor(DEFAULT_PIT_COLOR);
        for(int i= 0, len= pits.size(); i<len; i++){
            pits[i].draw();
        }

        glEnd();



        drawMainBackground();
    }

    void addWall(Wall wall){
        walls.push_back(wall);
    }

    void addPit(Pit pit){
        pits.push_back(pit);
    }

    bool detectCollision(Player& player){
        for(int i= 0, len= walls.size(); i<len; i++){
            if(walls[i].detectCollision(player)) return true;
        }
        return false;
    }

    bool detectCollision(Bullet& bullet){
        for(int i= 0, len= walls.size(); i<len; i++){
            if(walls[i].detectCollision(bullet)) return true;
        }
        return false;
    }

    string getMapName(){
        return map_name;
    }

    void setMapName(const string& name){
        map_name = name;
    }
};

double WALL_THICKNESS = .1;


#endif
