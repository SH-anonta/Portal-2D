#ifndef MAPS_H
#define MAPS_H


Color DEFAULT_WALL_COLOR= Color(.2, .5,.7);
//Color DEFAULT_PIT_COLOR= Color(0.1,0.05,0.05);
Color DEFAULT_PIT_COLOR= Color(.05, 0.05, .15);

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

    bool detectCollision(BasePlayer& player){
        Point next_position = player.getNextPosition();

        float buffer = .06;
        return points[0].x <= next_position.x+buffer &&
               points[1].x >= next_position.x-buffer &&
               points[0].y <= next_position.y+buffer &&
               points[3].y >= next_position.y-buffer;
    }

    // check if a given position has collision with this wall, and has buffer units of space in between
    bool detectCollision(const Point& position, float buffer = .5){

        return points[0].x <= position.x+buffer &&
               points[1].x >= position.x-buffer &&
               points[0].y <= position.y+buffer &&
               points[3].y >= position.y-buffer;
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

    bool detectCollision(BasePlayer& player){
        Point next_position = player.getNextPosition();

        return points[0].x <= next_position.x &&
               points[1].x >= next_position.x &&
               points[0].y <= next_position.y &&
               points[3].y >= next_position.y;
    }

    // check if a given position has collision with this pit, and has buffer units of space in between
    bool detectCollision(const Point& position, float buffer = .5){
        return points[0].x <= position.x+buffer &&
               points[1].x >= position.x-buffer &&
               points[0].y <= position.y+buffer &&
               points[3].y >= position.y-buffer;
    }
};

class Map{
    public:
    vector<Wall> walls;
    vector<Pit> pits;
    string map_name;

    // default map dimensions
    float x_min = -3;
    float x_max = 3;
    float y_max = 3;
    float y_min = -3;


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

    bool detectCollision(BasePlayer& player){
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

    // this function assumes there will be at least one wall which intercepts the line
    // a and b are assumed to be end points of a vertical line
    // finds intercept in horizontal walls
    Point getNearestHorizontalIntercept(Point a, Point b, Point player_pos){
        Point nearest_intercept(9999,9999);
        float nearest_vertical_dist = 9999;

        for(Wall& wall : walls){
            // if the line intercepts with a walls horizontal edge
            if(linesInterceptHorizontalVertical(wall.points[0], wall.points[1], a, b)){
                float bottom_edge_dist = getVerticalDistance(player_pos, wall.points[0]);
                float top_edge_dist = getVerticalDistance(player_pos, wall.points[2]);

                if(nearest_vertical_dist > bottom_edge_dist){
                    nearest_vertical_dist = bottom_edge_dist;
                    nearest_intercept.x= player_pos.x;
                    nearest_intercept.y= wall.points[0].y;
                }
                if(nearest_vertical_dist > top_edge_dist){
                    nearest_vertical_dist = top_edge_dist;
                    nearest_intercept.x= player_pos.x;
                    nearest_intercept.y= wall.points[2].y;
                }
            }
        }

        return nearest_intercept;
    }

    // this function assumes there will be at least one wall which intercepts the line
    // a and b are assumed to be end points of a horizontal line
    // finds intercept in vertical walls
    Point getNearestVerticalIntercept(Point a, Point b, Point player_pos){
        Point nearest_intercept(9999,9999);
        float nearest_horizontal_dist = 9999;

        for(Wall& wall : walls){
            // if the line intercepts with a walls horizontal edge
            if(linesInterceptHorizontalVertical(a, b, wall.points[0], wall.points[3])){
                float left_edge_dist = getHorizontalDistance(player_pos, wall.points[0]);
                float right_edge_dist = getHorizontalDistance(player_pos, wall.points[1]);

                if(nearest_horizontal_dist  > left_edge_dist ){
                    nearest_horizontal_dist  = left_edge_dist ;
                    nearest_intercept.x= wall.points[0].x;
                    nearest_intercept.y= player_pos.y;
                }
                if(nearest_horizontal_dist  > right_edge_dist){
                    nearest_horizontal_dist  = right_edge_dist;
                    nearest_intercept.x= wall.points[1].x;
                    nearest_intercept.y= player_pos.y;
                }
            }
        }

        return nearest_intercept;
    }

    float getVerticalDistance(Point& a, Point& b){
        return abs(a.y-b.y);
    }

    float getHorizontalDistance(Point& a, Point& b){
        return abs(a.x-b.x);
    }


    // return true if line ab intersects line bc
    // ab is assumed to be endpoints of a horizontal line
    // cd is assumed to be endpoints of a vertical line
    bool linesInterceptHorizontalVertical(Point& a, Point& b, Point& c, Point& d){
        if(a.x > b.x){
            swap(a.x, b.x);
        }
        if(c.y > d.y){
            swap(c.y, d.y);
        }

        return (a.x < c.x && b.x > c.x) && (a.y > c.y && a.y < d.y);
    }

    // return a point in the map which does not collide with any wall or pit with buffer units in between
    Point getValidSpawnPoint(float buffer= .1){
        float spawn_x = randomf()*6 - 3;  // get random value from (-3 to 3)
        float spawn_y = randomf()*6 - 3;  // get random value from (-3 to 3)

        int attepmt_no = 1;

        while(true){
            if(attepmt_no > 30){
                printf("WARNING: Map::getValidSpawnPoint my be stuck in infinite loop due to large buffer parameter\n", spawn_x);
            }
            spawn_x = randomf()*6 - 3;  // get random value from (-3 to 3)
            spawn_y = randomf()*6 - 3;  // get random value from (-3 to 3)

//            printf("%f\n", spawn_x);
//            printf("%f\n", spawn_y);

            if(!detectCollision(Point(spawn_x,spawn_y), 0.2)){
                break;
            }

            attepmt_no++;
        }

        return Point(spawn_x,spawn_y);
    }

    // check if a given position has collision with this wall, and has buffer units of space in between
    bool detectCollision(const Point& position, float buffer = .5){
        for(int i= 0, len = walls.size(); i<len; i++){
            if(walls[i].detectCollision(position, buffer)){
                return true;
            }
        }

        for(int i= 0, len= pits.size(); i<len; i++){
            if(pits[i].detectCollision(position, buffer)){
                return true;
            }
        }

        return false;
    }

    bool detectPitCollision(BasePlayer* player){
        Point pos = player->getPosition();

        for(Pit& pit : pits){
            if(pit.detectCollision(pos, 0)){
                return true;
            }
        }

        return false;
    }
};


#endif
