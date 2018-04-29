#ifndef MAP_FACTORY_H
#define MAP_FACTORY_H


class MapFactory{
public:
    constexpr static const double DEFAULT_WALL_THICKNESS = .1;

    virtual Map createMap(){

    }
};

// create a map with four borders only
class VoidMapFactory: public MapFactory{

public:
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
    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Pockets");

        return game_map;
    }
};

class DivideMapFactory: public MapFactory{

public:
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
        desired_wall_count = randomf() * (wall_count/2);

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
    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Random Map");

        MAZE_DIMENSION = 30;

        generateRandomMaze();

        printMaze();

        return game_map;
    }


};

vector<Map> getAllMaps(){
    vector<Map> maps;

    maps.push_back(VoidMapFactory().createMap());
    maps.push_back(ChokePointMapFactory().createMap());
    maps.push_back(DivideMapFactory().createMap());
    maps.push_back(StrandedMapFactory().createMap());

    return maps;
}

#endif
