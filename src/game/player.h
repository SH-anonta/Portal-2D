#ifndef PLAYER_H
#define PLAYER_H



const double RELOAD_TIME= 0.1;    // in seconds
Color DEFAULT_PLAYER_COLOR = Color(.2,.2,.8);
const int MAX_PLAYER_HEALTH= 100;
double PLAYER_SPEED = .01;   // positions per iteration

class Player{
public:
    static constexpr float move_step= .05;
    int health;
    Direction direction = Up;
    Point position;
    Point next_position;    // next position that will be occupied by the player if the game allows it
    Color color;

    clock_t last_bullet_shoot_time;

    Player(){
        printf("Player created\n");
        last_bullet_shoot_time= 0;
        color = DEFAULT_PLAYER_COLOR;
        health= MAX_PLAYER_HEALTH;
    }

    Player(Point& pos){
        printf("Player created\n");
        position.x= next_position.x = pos.x;
        position.y= next_position.y = pos.y;
        color = DEFAULT_PLAYER_COLOR;
        health= MAX_PLAYER_HEALTH;

        last_bullet_shoot_time= 0;
    }

    Player(double x, double y){
        printf("Player created\n");
        position.x= next_position.x = x;
        position.y= next_position.y = y;
        health= MAX_PLAYER_HEALTH;
        last_bullet_shoot_time= 0;
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
        direction = Up;
    }

    void moveDown(){
        next_position.y-= move_step;
        direction = Down;
    }

    void moveLeft(){
        next_position.x-= move_step;
        direction = Left;
    }

    void moveRight(){
        next_position.x+= move_step;
        direction = Right;
    }


    bool reloadTimeIsOver(){
        clock_t time_now= clock();

        return double(double(time_now - last_bullet_shoot_time) / CLOCKS_PER_SEC) > RELOAD_TIME;
    }

    void takeDamage(){
        health -= 10;
    }

    bool detectHit(Bullet& bullet){
        return abs(position.x - bullet.position.x) < .0001 && abs(position.y - bullet.position.y) < .0001;
    }

    Bullet shootBullet(){
        //record when this bullet was shot
        last_bullet_shoot_time= clock();

        int x_inc= 0;
        int y_inc= 0;

        if(direction == Up)
            y_inc= 1;
        else if(direction == Down)
            y_inc= -1;
        else if(direction == Left)
            x_inc= -1;
        else if(direction == Right)
            x_inc= 1;

        return Bullet(position, x_inc, y_inc);
    }


};

#endif
