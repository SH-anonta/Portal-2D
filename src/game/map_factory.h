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


class PitNestsMapFactory:public MapFactory
{
    public:
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

class RandomMazeMapFactory: public MapFactory{

public:
    Map createMap() override{
        Map game_map = VoidMapFactory().createMap();
        game_map.setMapName("Random Map");

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

    return maps;
}

#endif
