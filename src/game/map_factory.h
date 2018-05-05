#ifndef MAP_FACTORY_H
#define MAP_FACTORY_H


class MapFactory{
public:
    constexpr static const double DEFAULT_WALL_THICKNESS = .1;

    virtual Map createMap(){

    }

    virtual string getMapName(){
    }
};

// create a map with four borders only
class VoidMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "The Void";
    }

    Map createMap() override{
        Map gmap;
        double thickness= .1;
        gmap.setMapName("Void");

        Wall bottom = Wall(6, thickness, -2.9, -2.9);

        Wall top = Wall(6, thickness, -2.9, 2.8);

        Wall left = Wall(thickness, 6, -3, -3);

        Wall right= Wall(thickness, 6, 3, -3);

        gmap.addWall(bottom);
        gmap.addWall(top);
        gmap.addWall(left);
        gmap.addWall(right);

        gmap.p1position = Point(-2.5, -2.5);
        gmap.p2position = Point(2.5, 2.5);

        return gmap;
    }
};

class ChokePointMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "Choke Point";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Choke Point");
        float WALL_THICKNESS = .1;

        // walls
        Wall middle_horizontal1= Wall(2.95, WALL_THICKNESS, -3.0, 0);
        Wall middle_horizontal2= Wall(2.95, WALL_THICKNESS, .05, 0);

        game_map.addWall(middle_horizontal1);
        game_map.addWall(middle_horizontal2);

        // pits
        Pit center_pit = Pit(1,1, -.5, -.5);
        game_map.addPit(center_pit);

        return game_map;
    }
};



class PocketsMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "Pockets";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Pockets");

        return game_map;
    }
};

class DivideMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "The Divide";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Divide");

        Pit middlePit = Pit(6, 2, -3, -1);

        Wall left_pit_wall = Wall(2, DEFAULT_WALL_THICKNESS, -3, .9);
        Wall right_pit_wall = Wall(2, DEFAULT_WALL_THICKNESS, 1, -1);

        game_map.addPit(middlePit);
        game_map.addWall(left_pit_wall);
        game_map.addWall(right_pit_wall);

        return game_map;
    }
};

class StrandedMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "Stranded";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Stranded");

        Pit pit_top = Pit(6, 1, -3, 2);
        Pit pit_bottom = Pit(6, 1, -3, -3);
        Pit pit_left = Pit(1, 6, -3, -3);
        Pit pit_right = Pit(1, 6, 2, -3);

        game_map.addPit(pit_top);
        game_map.addPit(pit_bottom);
        game_map.addPit(pit_left);
        game_map.addPit(pit_right);

        game_map.p1position = Point(-1.5, -1.5);
        game_map.p2position = Point(1.5, 1.5);

        return game_map;
    }
};


class PitNestsMapFactory:public MapFactory
{
    public:
    string getMapName() override{
        return "Pit Nests";
    }

    Map createMap() override
    {
        double thickness=.1;
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Pit Nests");
        Pit one=Pit(.2,4,2,-2);
        Pit two=Pit(.2,4,-2,-2);
        Pit three=Pit(4.2,.2,-2,2);
        Pit four=Pit(4.1,.2,-2,-2);

        Pit five =Pit(.18,3,1.5,-1.5);
        Pit six =Pit(.18,3,-1.5,-1.5);
        Pit seven =Pit(3.18,.18,-1.5,1.5);
        Pit eight =Pit(3.1,.18,-1.5,-1.5);

        Pit nine=Pit(.15,2,1,-1);
        Pit ten= Pit(.15,2,-1,-1);
        Pit eleven= Pit(2.15,.15,-1,1);
        Pit twelve= Pit(2.1,.15,-1,-1);

       Wall Wall_one=Wall(thickness,.7,-1.2,-2.8);
       Wall Wall_two=Wall(1,thickness,-1.6,-2.1);
       Wall Wall_three=Wall(.8,thickness,2.2,-1.0);
       Wall Wall_four=Wall(thickness,.8,1.9,-1.3);
       Wall Wall_five=Wall(.7,thickness,-1,-1.09);
       Wall Wall_six=Wall(thickness,.5,-.9,-.2);
       Wall Wall_seven=Wall(.5,thickness,.5,.9);
       Wall Wall_eight=Wall(.5,thickness,-.9,1.9);
       Wall Wall_nine=Wall(thickness,.4,.6,1.2);


         game_map.addWall(Wall_one);
         game_map.addWall(Wall_two);
         game_map.addWall(Wall_three);
         game_map.addWall(Wall_four);
         game_map.addWall(Wall_five);
         game_map.addWall(Wall_six);
         game_map.addWall(Wall_seven);
         game_map.addWall(Wall_eight);
         game_map.addWall(Wall_nine);
        game_map.addPit(one);
        game_map.addPit(two);
        game_map.addPit(three);
        game_map.addPit(four);
        game_map.addPit(five);
        game_map.addPit(six);
        game_map.addPit(seven);
        game_map.addPit(eight);
        game_map.addPit(nine);
        game_map.addPit(ten);
        game_map.addPit(eleven);
        game_map.addPit(twelve);

        return game_map;
    }

};

class VerticalPathsMapFactory:public MapFactory
{
    public:
    string getMapName() override{
        return "Vertical Paths";
    }

    Map createMap() override
    {
        double thickness=.1;
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Vertical Paths");

        Wall one=Wall(thickness,2.2,-2,.7);
        Wall two=Wall(thickness,4.2,-1,-2.8);
        Wall three=Wall(thickness,3.8,0.7,-1);
        Wall four=Wall(thickness,3.9,2,-2.8);

        Pit pit_one=Pit(1,1,-2.9,1.2);
        Pit pit_two=Pit(1,.3,-2.0,1.0);
        Pit pit_three=Pit(1.7,.8,-0.9,-1.0);
        Pit pit_four=Pit(1.19,0.5,.8,.4);
        Pit pit_five=Pit(1.0,0.6,2,-1);




        game_map.addPit(pit_one);
        game_map.addPit(pit_two);
        game_map.addPit(pit_three);
        game_map.addPit(pit_four);
        game_map.addPit(pit_five);



        game_map.addWall(one);
        game_map.addWall(two);
        game_map.addWall(three);
        game_map.addWall(four);
        return game_map;
    }
};

class islandsMapFactory: public MapFactory{

public:
    string getMapName() override{
        return "Islands";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Islands");
        float WALL_THICKNESS = .1;

        // walls
        Wall one = Wall(0.1, 0.7, -2.4, 1.55);
        Wall two = Wall(0.7, 0.1, 1.8, 2.2);
        Wall three = Wall(0.1, 0.8, 1.0, 1.1);
        Wall four = Wall(0.1, 0.6, -2.2, -0.2);
        Wall five = Wall(0.7, 0.1, -1.0, -0.35);
        Wall six = Wall(0.7, 0.1, 0.0, 0.45);
        Wall seven = Wall(0.1, 0.6, 2.43, -0.2);
        Wall eight = Wall(0.9, 0.1, -1.7, -2.32);
        Wall nine = Wall(0.1, 0.9, 2.43, -2.3);

        game_map.addWall(one);
        game_map.addWall(two);
        game_map.addWall(three);
        game_map.addWall(four);
        game_map.addWall(five);
        game_map.addWall(six);
        game_map.addWall(seven);
        game_map.addWall(eight);
        game_map.addWall(nine);

        // pits
        Pit bottom_pit = Pit(6,0.5, -3.0, -2.8);
        Pit top_pit = Pit(6,0.5, -3.0, 2.28);
        Pit left_pit = Pit(0.6, 5.7, -3.0, -2.8);
        Pit right_pit = Pit(0.6, 5.7, 2.5, -2.8);

        Pit middle_bottom = Pit(1, 2.4, -0.5, -2.8);
        Pit middle_top = Pit(1, 2.4, -0.5, 0.5);
        Pit middle_left1 = Pit(0.8, 1, -3.0, -0.5);
        Pit middle_left2 = Pit(0.5, 1.0, -1.5, -0.4);
        Pit middle_right = Pit(1.0, 1.0, 0.75, -0.4);
        Pit lower_edge = Pit(6.0, 0.2, -3.0, 0.5);
        Pit upper_edge = Pit(6.0, 0.2, -3.0, -0.5);


        game_map.addPit(bottom_pit);
        game_map.addPit(top_pit);
        game_map.addPit(left_pit);
        game_map.addPit(right_pit);

        game_map.addPit(middle_bottom);
        game_map.addPit(middle_top);
        game_map.addPit(middle_left1);
        game_map.addPit(middle_left2);
        game_map.addPit(middle_right);
        game_map.addPit(lower_edge);
        game_map.addPit(upper_edge);

        game_map.p1position = Point(-2.0, -2.0);
        game_map.p2position = Point(2.0, 2.0);



        return game_map;
    }
};


class RandomMazeMapFactory: public MapFactory{
    int MAZE_DIMENSION; // # of row and column
    vector<vector<char>> maze;
    int wall_count;
    int desired_wall_count;

    void generateRandomMaze(){
        int n = MAZE_DIMENSION;

        maze.clear();
        for(int i= 0; i<n; i++){
            maze.push_back(vector<char>(MAZE_DIMENSION, '#'));
        }

        wall_count = MAZE_DIMENSION*MAZE_DIMENSION;
        desired_wall_count = (randomf() * (wall_count*3));

        desired_wall_count%=90;
        printf("%d\n",desired_wall_count);
        int tries = 1;
        while(desired_wall_count != wall_count){
            int seed_x = randomf()*MAZE_DIMENSION;
            int seed_y = randomf()*MAZE_DIMENSION;

            createRandomPath(seed_x, seed_y);
            tries++;
        }

//        printf("%d\n", tries);
    }

    void printMaze(){
        int rows= maze.size();
        int cols= maze[0].size();

        for(int r= 0; r<rows; r++){
            for(int c= 0; c<cols; c++){
                printf("%c", maze[r][c]);
            }
            printf("\n");
        }
    }

    void createRandomPath(int x, int y){
//        printf("AAAAAAAAA\n");
//        printf("%d\n", wall_delete_count);
//        printf("%d %d\n", x, y);


        if(x < 0 || y < 0 || x >= MAZE_DIMENSION || y >= MAZE_DIMENSION){
            return;
        }

        if(desired_wall_count == wall_count){
            return;
        }

        if(maze[x][y] == '#'){
            maze[x][y] = ' ';
            wall_count--;
        }

        int tries = 0;
        // keep trying random direction until a valid one is found

        // randomly choose a direction to take
        int nx = randomf() < .5 ? x-1 : x+1;
        int ny = randomf() < .5 ? y+1 : y-1;
        createRandomPath(nx, ny);
    }

public:

    string getMapName() override{
        return "Random Maze";
    }

    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Random Map");

        MAZE_DIMENSION = 10;

       generateRandomMaze();

//        printMaze();
       double initsize=0.5;
        float WALL_THICKNESS = .1;
        int rows= maze.size();
        int cols= maze[0].size();
         double  w=initsize,x=-3,y=3,increase=.5;
         int flag=0;
        for(int r= 0; r<rows; r++){
              x=-3;
              y-=increase;
              flag=0;
              w=0;
            for(int c= 0; c<cols; c++){
                  if(maze[r][c]=='#')
                  {
                     // w+=0.033;
                        flag=1;
                        w+=initsize;                      //   w+=0.033
                     // flag=1;
                  }
                  else if(flag && maze[r][c]==' ')
                  {
                      Wall one=Wall(w,WALL_THICKNESS,x,y);
                      game_map.addWall(one);
                      flag=0;
                    x+=initsize;
                  }
                  else
                  {
                      x+=initsize;
                  }


            }
            if(flag)
            {
                 Wall one=Wall(w,WALL_THICKNESS,x,y);
                      game_map.addWall(one);
                      flag=0;
                    x+=w;
            }

        }
        y=-2.7,x=-3,w=initsize;
        double temp=.4;
       for(int r= 0; r<rows; r++){
              y=-2.7;
              x+=initsize;
              flag=0;
              w=0;
            for(int c= cols-1; c>=0; c--){
                  if(maze[c][r]=='#')
                  {
                     // w+=0.033;
                        flag=1;
                        w+=initsize;                      //   w+=0.033
                     // flag=1;
                  }
                  else if(flag && maze[c][r]==' ')
                  {
                      Wall one=Wall(WALL_THICKNESS,w,x,y);
                      game_map.addWall(one);
                      flag=0;
                    y+=temp;
                  }
                  else
                  {
                      y+=temp;
                  }


            }
            if(flag)
            {
                Wall one=Wall(WALL_THICKNESS,w,x,y);
                      game_map.addWall(one);
                      flag=0;
                    y-=w;
            }


        }


        game_map.p1position = game_map.getValidSpawnPoint();
        game_map.p2position = game_map.getValidSpawnPoint();

        return game_map;
    }


};

vector<Map> getAllMaps(){
    vector<Map> maps;

    maps.push_back(VoidMapFactory().createMap());
    maps.push_back(ChokePointMapFactory().createMap());
    maps.push_back(DivideMapFactory().createMap());
    maps.push_back(StrandedMapFactory().createMap());
    maps.push_back(PitNestsMapFactory().createMap());
    maps.push_back(VerticalPathsMapFactory().createMap());
    maps.push_back(islandsMapFactory().createMap());
//    srand(time(NULL)+1);
    maps.push_back(RandomMazeMapFactory().createMap());

    return maps;
}



vector<MapFactory*> getAllMapFactories(){
    vector<MapFactory*> maps;

    maps.push_back(new VoidMapFactory());
    maps.push_back(new ChokePointMapFactory());
    maps.push_back(new DivideMapFactory());
    maps.push_back(new StrandedMapFactory());
    maps.push_back(new PitNestsMapFactory());
    maps.push_back(new VerticalPathsMapFactory());
    maps.push_back(new islandsMapFactory());
//    srand(time(NULL)+1);
    maps.push_back(new RandomMazeMapFactory());

    return maps;
}
#endif
