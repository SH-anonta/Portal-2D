#ifndef MAPS_H
#define MAPS_H


Color DEFAULT_WALL_COLOR= Color(.2, .4, .8);

// Points that define the wall, should be in counter clockwise order
// this is important for collision detection
class Wall{
public:
    vector<Point> points;

    Wall(vector<Point>& pts){
        points = pts;
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

    bool detectCollision(Player& player){

        return points[0].x <= player.next_position.x &&
               points[1].x >= player.next_position.x &&
               points[0].y <= player.next_position.y &&
               points[3].y >= player.next_position.y;
    }

    bool detectCollision(Bullet& bullet){

        return points[0].x <= bullet.position.x &&
               points[1].x >= bullet.position.x &&
               points[0].y <= bullet.position.y &&
               points[3].y >= bullet.position.y;
    }
};

class Map{
public:
    vector<Wall> walls;
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

        glEnd();
    }

    void addWall(Wall wall){
        walls.push_back(wall);
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
};

double WALL_THICKNESS = .1;

// a map with 4 borders
Map createMapTheVoid(){
    Map gmap;
    double thickness= .1;
    Wall bottom = Wall::createWall(6, thickness);
    bottom.translate(-2.9, -2.9);

    Wall top = Wall::createWall(6, thickness);
    top.translate(-2.9, 2.8);

    Wall left = Wall::createWall(thickness, 6);
    left.translate(-3, -3);

    Wall right= Wall::createWall(thickness, 6);
    right.translate(3, -3);


    gmap.addWall(bottom);
    gmap.addWall(top);
    gmap.addWall(left);
    gmap.addWall(right);

    gmap.p1position = Point(-2.5, -2.5);
    gmap.p2position = Point(2.5, 2.5);

    return gmap;
}

Map createMap_NeedleEye(){
    Map game_map = createMapTheVoid();

    Wall middle_horizontal1= Wall::createWall(2.95, WALL_THICKNESS);
    Wall middle_horizontal2= Wall::createWall(3, WALL_THICKNESS);

    middle_horizontal1.translate(-3.0, 0);
    middle_horizontal2.translate(.05, 0);

    game_map.addWall(middle_horizontal1);
    game_map.addWall(middle_horizontal2);

    return game_map;
}

#endif
