#ifndef MAP_FACTORY_H
#define MAP_FACTORY_H


class MapFactory{
    constexpr static const double DEFAULT_WALL_THICKNESS = .1;
public:

    virtual Map createMap(){

    }
};

class VoidMapFactory: public MapFactory{

public:
    Map createMap() override{
        Map gmap;
        double thickness= .1;
        gmap.setMapName("Void");

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
};

class ChokePointMapFactory: public MapFactory{

public:
    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Choke Point");

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
};



class PocketsMapFactory: public MapFactory{

public:
    Map createMap() override{

    }
};


vector<Map> getAllMaps(){
    vector<Map> maps;

    maps.push_back(VoidMapFactory().createMap());
    maps.push_back(ChokePointMapFactory().createMap());

    return maps;
}

#endif
