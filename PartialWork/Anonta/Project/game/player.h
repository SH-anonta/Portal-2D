#ifndef PLAYER_H
#define PLAYER_H

Color DEFAULT_PLAYER_COLOR = Color(.8,.2,.1);
double PLAYER_SPEED = .05;   // positions per iteration


class Player{
public:
    static constexpr float move_step= .05;

    Point position;
    Point next_position;    // next position that will be occupied by the player if the game allows it
    Color color;

    Player(){
        printf("Player created\n");
    }

    Player(Point& pos){
        printf("Player created\n");
        position.x= next_position.x = pos.x;
        position.y= next_position.y = pos.y;
        color = DEFAULT_PLAYER_COLOR;
    }

    Player(double x, double y){
        printf("Player created\n");
        position.x= next_position.x = x;
        position.y= next_position.y = y;
    }

    // simply assign next_position to position
    void updatePosition(){
        position.x= next_position.x;
        position.y= next_position.y;
    }

    void resetNextPosition(){
        next_position.x= position.x;
        next_position.y= position.y;
    }

    void draw(){
        setColor(color);

        glBegin(GL_POINTS);
        plot(position.x, position.y);
        glEnd();
    }


    // movement methods
    void moveUp(){
        next_position.y+= move_step;
    }

    void moveDown(){
        next_position.y-= move_step;
    }

    void moveLeft(){
        next_position.x-= move_step;
    }

    void moveRight(){
        next_position.x+= move_step;
    }
};

#endif
