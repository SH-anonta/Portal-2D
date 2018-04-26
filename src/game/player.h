#ifndef PLAYER_H
#define PLAYER_H



const double RELOAD_TIME= 0.1;    // in seconds
const double PORTAL_GUN_RELOAD_TIME= 0.2;    // in seconds
Color DEFAULT_PLAYER_COLOR = Color(.2,.2,.8);
const int DAMAGE_PER_HIT= 5;
const int MAX_PLAYER_HEALTH= 100;
double PLAYER_SPEED = .01;   // positions per iteration

class Player: public BasePlayer{
public:
    static constexpr float move_step= .03;
    int health;
    Direction direction = Up;
    Point position;
    Point next_position;    // next position that will be occupied by the player if the game allows it
    Color color;

    clock_t last_bullet_shoot_time= 0;
    clock_t last_portal_open_time= 0;

    Player(){
        printf("Player created\n");
        last_bullet_shoot_time= 0;
        color = DEFAULT_PLAYER_COLOR;
        health= MAX_PLAYER_HEALTH;
    }

    Player(const Point& pos){
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

    Point getPosition(){
        return position;
    }

    // simply assign next_position to position
    void updatePosition() override{
        position.x= next_position.x;
        position.y= next_position.y;
    }

    void resetNextPosition() override{
        next_position.x= position.x;
        next_position.y= position.y;
    }

    void draw() override{
        setColor(color);

        float h = .07;
        float w = .07;

        // rotate the player model to it's appropriate direction
        glPushMatrix();
        glTranslatef(position.x, position.y, 0);
        if(direction == Down){
            glRotatef(180, 0,0,1);
        }
        else if(direction == Left){
            glRotatef(90, 0,0,1);
        }
        else if(direction == Right){
            glRotatef(90, 0,0,-1);
        }
        glTranslatef(-1*position.x, -1*position.y, 0);

        glBegin(GL_TRIANGLES);
        plot(position.x-w, position.y-h);
        plot(position.x+w, position.y-h);
        plot(position.x, position.y+h);
        glEnd();



        glPopMatrix();
    }


    bool detectHit(Bullet& bullet) override{
        return abs(position.x - bullet.position.x) < .06 && abs(position.y - bullet.position.y) < .06;
    }

    // movement methods
    void moveUp() override{
        next_position.y+= move_step;
        direction = Up;
    }

    void moveDown() override{
        next_position.y-= move_step;
        direction = Down;
    }

    void moveLeft() override{
        next_position.x-= move_step;
        direction = Left;
    }

    void moveRight() override{
        next_position.x+= move_step;
        direction = Right;
    }

    void shiftUp() override{
        next_position.y+= move_step;
    }

    void shiftDown() override{
        next_position.y-= move_step;
    }

    void shiftLeft() override{
        next_position.x-= move_step;
    }

    void shiftRight() override{
        next_position.x+= move_step;
    }


    bool reloadTimeIsOver() override{
        clock_t time_now= clock();

        return float(float(time_now - last_bullet_shoot_time) / CLOCKS_PER_SEC) > RELOAD_TIME;
    }

    bool portalGunReloadTimeIsOver() override{
        clock_t time_now= clock();

        return float(float(time_now - last_portal_open_time) / CLOCKS_PER_SEC) > PORTAL_GUN_RELOAD_TIME;
    }

    void setPortalOpenTimeNow() override{
        last_portal_open_time = clock();
    }

    void takeDamage() override{
        if(health > 0){
            health -= DAMAGE_PER_HIT;
        }
    }

    Bullet shootBullet() override{
        //record when this bullet was shot
        last_bullet_shoot_time= clock();
        float adj_x = 0;
        float adj_y = 0;

        if(direction == Up){
            adj_y = .08;
        }
        else if(direction == Down){
            adj_y = -.08;
        }
        else if(direction == Left){
            adj_x = -.08;
        }
        else{
            //right
            adj_x = .08;
        }

        return Bullet(position.x+adj_x, position.y+adj_y, direction);
    }

    void updateDirection(Direction new_direction) override{
        direction = new_direction;
    }

};

#endif
