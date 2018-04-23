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


vector<Map> getAllMaps(){
    vector<Map> maps;

    maps.push_back(VoidMapFactory().createMap());
    maps.push_back(ChokePointMapFactory().createMap());
    maps.push_back(DivideMapFactory().createMap());

    return maps;
}

#endif
