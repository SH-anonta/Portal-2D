#ifndef PLAYER_H
#define PLAYER_H

Color DEFAULT_PLAYER_COLOR = Color(.8,.2,.1);
double PLAYER_SPEED = .05;   // positions per iteration


class Player{
public:

    Point position;

    // next position that will be occupied by the player if the game allows it
    Point next_position;
    Color color;

    // move directions
    bool move_up;
    bool move_down;
    bool move_left;
    bool move_right;

    Player(){
        printf("Player created\n");
        clearMoveDirections();
    }

    Player(Point& pos){
        printf("Player created\n");
        position.x= next_position.x = pos.x;
        position.y= next_position.y = pos.y;
        color = DEFAULT_PLAYER_COLOR;
        clearMoveDirections();
    }

    Player(double x, double y){
        printf("Player created\n");
        position.x= next_position.x = x;
        position.y= next_position.y = y;
        clearMoveDirections();
    }

    // simply assign next_position to position
    void updatePosition(){
        position.x= next_position.x;
        position.y= next_position.y;
    }

    // update
    void calculateNextPosition(){
        if(move_up){
            next_position.y+= PLAYER_SPEED;
        }
        if(move_down){
            next_position.y-= PLAYER_SPEED ;
        }
        if(move_left){
            next_position.x-= PLAYER_SPEED;
        }
        if(move_right){
            next_position.x+= PLAYER_SPEED;
        }

//        printf("%f %f\n", position.x, next_position.x);
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

    void clearMoveDirections(){
//        SS
        move_up = move_down = move_left = move_right = false;
    }
};

#endif
