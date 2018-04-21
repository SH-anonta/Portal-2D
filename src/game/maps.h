#ifndef MAPS_H
#define MAPS_H


Color DEFAULT_WALL_COLOR= Color(.2, .7, .5);
//Color DEFAULT_PIT_COLOR= Color(.1, .1, .1);
Color DEFAULT_PIT_COLOR= Color(0,0,0);
//Color MAP_BACKGROUND_COLOR= Color(.8, .8, .8);
Color MAP_BACKGROUND_COLOR= Color(.05, .15, .1);
Color MAP_BACKGROUND_GRID_COLOR= Color(.15, .3, .15);


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

class Pit{
public:
    // points that make up the pit (a quad)
    vector<Point> points;

    Pit(vector<Point>& pts){
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

    static Pit createPit(double w, double h){
        vector<Point> pit_points= {
            Point(0,0),
            Point(w, 0),
            Point(w, h),
            Point(0, h)
        };

        return Pit(pit_points);
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
public:
    vector<Wall> walls;
    vector<Pit> pits;

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

Map createMap_ChokePoint(){
    Map game_map = createMapTheVoid();

    // walls
    Wall middle_horizontal1= Wall::createWall(2.95, WALL_THICKNESS);
    Wall middle_horizontal2= Wall::createWall(2.95, WALL_THICKNESS);

    middle_horizontal1.translate(-3.0, 0);
    middle_horizontal2.translate(.05, 0);

    game_map.addWall(middle_horizontal1);
    game_map.addWall(middle_horizontal2);

    // pits

    Pit center_pit = Pit::createPit(1,1);

    center_pit.translate(-.5, -.5);
    game_map.addPit(center_pit);

    return game_map;
}

Map createMap_Pockets(){
    Map gmap = createMapTheVoid();
    double thickness= .1;

    Wall bottomLeft1 = Wall::createWall(2, thickness);
    bottomLeft1.translate(-2.7, -2.4);

    Wall bottomLeft2 = Wall::createWall(thickness, 2);
    bottomLeft2.translate(-0.8, -2.4);

    Wall bottomLeft3 = Wall::createWall(2, thickness);
    bottomLeft3.translate(-2.7, -0.4);


    Wall topLeft1 = Wall::createWall(2, thickness);
    topLeft1.translate(-2.7, 2.4);

    Wall topLeft2 = Wall::createWall(thickness, 2);
    topLeft2.translate(-2.7, 1.7);

    //Wall topLeft3 = Wall::createWall(6, thickness);
    //topLeft1.translate(-0.8, 2.8);

    //Wall left = Wall::createWall(thickness, 6);
    //left.translate(-3, -3);

    //Wall right= Wall::createWall(thickness, 6);
    //right.translate(3, -3);


//    gmap.addWall(bottomLeft1);
//    gmap.addWall(bottomLeft2);
//    gmap.addWall(bottomLeft3);
    gmap.addWall(topLeft1);
    gmap.addWall(topLeft2);
    //gmap.addWall(topLeft3);
    //gmap.addWall(left);
    //gmap.addWall(right);

    gmap.p1position = Point(-2.5, -2.5);
    gmap.p2position = Point(2.5, 2.5);

    return gmap;
}

#endif
