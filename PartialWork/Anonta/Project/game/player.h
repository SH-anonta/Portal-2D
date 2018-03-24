#ifndef PLAYER_H
#define PLAYER_H

class Player{
public:

    Point position;
    Point next_position;

    Player(double x, double y){
        position.x= next_position.x = x;
        position.y= next_position.y = y;
    }

    void updatePosition(){
        position.x= next_position.x;
        position.y= next_position.y;
    }

    void resetNewPosition(){
        next_position.x= position.x;
        next_position.y= position.y;
    }
};

#endif
