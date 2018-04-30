#ifndef PLAYER_WRAPPER_H
#define PLAYER_WRAPPER_H

class BasePlayer{
public:

    // update the chain of PlayerWrappers
    virtual BasePlayer* updateWrapperChain()= 0;
    virtual BasePlayer* stripAllWrappers()= 0;

    virtual void updatePosition()= 0;
    virtual void resetNextPosition()= 0;


    virtual void draw()= 0;

    virtual bool detectHit(Bullet& bullet)= 0;

    virtual void moveUp()= 0;
    virtual void moveDown()= 0;
    virtual void moveRight()= 0;
    virtual void moveLeft()= 0;

    virtual void shiftUp()= 0;
    virtual void shiftDown()= 0;
    virtual void shiftRight()= 0;
    virtual void shiftLeft()= 0;


    virtual bool reloadTimeIsOver()= 0;
    virtual bool portalGunReloadTimeIsOver()= 0;

    virtual void setPortalOpenTimeNow()= 0;

    virtual void takeDamage(float damage)= 0;

    virtual Bullet shootBullet()= 0;

    virtual void updateDirection(Direction new_direction)= 0;

    // getters
    virtual float getHealth()= 0;

    virtual Direction getDirection()= 0;

    virtual Point getPosition()= 0;

    virtual Point getNextPosition()= 0;

    virtual Color getColor()= 0;

    // setters
    virtual void setHealth(float health)= 0;

    virtual void setDirection(Direction d)= 0;

    virtual void setPosition(Point& pos)= 0;

    virtual void setNextPosition(const Point& pos)= 0;

    virtual void setColor(const Color& color)= 0;

    virtual void increaseHealth(float inc)= 0;


};

// player wrapper classes:

class PlayerWrapper: public BasePlayer{
protected:
    BasePlayer* player;
public:

    PlayerWrapper(BasePlayer* player){
        this->player = player;
    }

    BasePlayer* updateWrapperChain() override{
        return this;
    }

    BasePlayer* stripAllWrappers() override{
        return player->stripAllWrappers();
    }

    void updatePosition() override{
        player->updatePosition();
    }

    void resetNextPosition() override{
        player->resetNextPosition();
    }

    void draw() override{
        player->draw();
    }


    bool detectHit(Bullet& bullet) override{
        return player->detectHit(bullet);
    }

    // movement methods
    void moveUp() override{
        player->moveUp();
    }

    void moveDown() override{
        player->moveDown();
    }

    void moveLeft() override{
        player->moveLeft();
    }

    void moveRight() override{
        player->moveRight();
    }

    void shiftUp() override{
        player->shiftUp();
    }

    void shiftDown() override{
        player->shiftDown();
    }

    void shiftLeft() override{
        player->shiftLeft();
    }

    void shiftRight() override{
        player->shiftRight();
    }


    bool reloadTimeIsOver() override{
        return player->reloadTimeIsOver();
    }

    bool portalGunReloadTimeIsOver() override{
        return player->portalGunReloadTimeIsOver();
    }

    void setPortalOpenTimeNow() override{
        player->setPortalOpenTimeNow();
    }

    void takeDamage(float damage) override{
        player->takeDamage(damage);
    }

    Bullet shootBullet() override{
        return player->shootBullet();
    }

    void updateDirection(Direction new_direction) override{
        player->updateDirection(new_direction);
    }

    // getters
    float getHealth() override{
        return player->getHealth();
    }

    Direction getDirection() override{
        return player->getDirection();
    }

    Point getPosition() override{
        return player->getPosition();
    }

    Point getNextPosition() override{
        return player->getNextPosition();
    }

    Color getColor() override{
        return player->getColor();
    }

    // setters
    void setHealth(float health) override{
        player->setHealth(health);
    }

    void setDirection(Direction d) override{
        player->setDirection(d);
    }

    void setPosition(Point& pos) override{
        player->setPosition(pos);
    }

    void setNextPosition(const Point& pos) override{
        player->setNextPosition(pos);
    }

    void setColor(const Color& color) override{
        player->setColor(color);
    }

    void increaseHealth(float inc) override{
        player->increaseHealth(inc);
    }
};

class PlayerShield: public PlayerWrapper{
public:
    float shield_rotate_angle;
    clock_t obit;

    PlayerShield(BasePlayer* player)
    :PlayerWrapper(player){
        shield_rotate_angle = 0;

        // this wrapper will be removed after 5 seconds
        obit = clock()+ 10*CLOCKS_PER_SEC;
    }

    void draw() override{
        glColor3f(0,.8,0);
        Point p = player->getPosition();

        glPushMatrix();
        shield_rotate_angle+= 3;

        Point position = player->getPosition();
        glTranslatef(position.x, position.y, 0);
        glRotatef(shield_rotate_angle, 0,0, -1);
        glTranslatef(-1*position.x, -1*position.y, 0);

        glLineWidth(1);
        glBegin(GL_LINE_LOOP);

        // draw shield
        plot(p.x-.1, p.y-.1);
        plot(p.x+.1, p.y-.1);
        plot(p.x+.1, p.y+.1);
        plot(p.x-.1, p.y+.1);
        glEnd();

        glPopMatrix();

        player->draw();
    }

    void takeDamage(float damage){
        // intentionally reuse to take damage
        return;
    }

    BasePlayer* updateWrapperChain(){
        if(clock() < obit){
            return this;
        }
        else{
            return player;
        }
    }
};

// when the player enters a pit
// this decorator wills cause the player to loose health very quickly, resulting in death

class FallingIntoPit: public PlayerWrapper{
public:
    int iterations;

    // to create the illusion of the player falling into the pit
    // when this decorator is applied, the player is displayed to be smaller and smaller on each iteration
    float scale = 1;

    FallingIntoPit(BasePlayer* player)
    :PlayerWrapper(player){
        iterations= 0;
    }

    void draw() override{
        glPushMatrix();

        // player's position will be fixed.
        Point pos = player->getPosition();

        glTranslatef(pos.x, pos.y, 0);
        glScalef(scale,scale,1);
        glTranslatef(-1*pos.x, -1*pos.y, 0);

        if(scale > 0){
            scale -= .05;
        }

        player->draw();
        glPopMatrix();
    }

    // this also causes all existing decorators to be removed
    BasePlayer* updateWrapperChain(){
        player->takeDamage(5);
        player = player->stripAllWrappers();
        // this is a permanent decorator
        return this;
    }


    // players can't move when they fall into a pit
    // movement methods
    void moveUp() override{
    }

    void moveDown() override{
    }

    void moveLeft() override{
    }

    void moveRight() override{
    }

    void shiftUp() override{
    }

    void shiftDown() override{
    }

    void shiftLeft() override{
    }

    void shiftRight() override{
    }

    bool reloadTimeIsOver(){
        return false;
    }

    bool portalGunReloadTimeIsOver(){
        return false;
    }

    BasePlayer* stripAllWrappers(){
        return this;
    }

};



class AcquireHealth: public PlayerWrapper{
public:
    AcquireHealth(BasePlayer* player)
    :PlayerWrapper(player){
    }


    BasePlayer* updateWrapperChain(){
        // player's health should increase by 20
        player->increaseHealth(20);

        return player;
    }
};



class BearTrap: public PlayerWrapper{
public:
    clock_t obit;

    BearTrap(BasePlayer* player)
    :PlayerWrapper(player){

        // this wrapper will be removed after 5 seconds
        obit = clock()+ 5*CLOCKS_PER_SEC;
    }

    void draw() override{

        drawCage();
        player->draw();
    }

    void drawCage(){
        glColor3f(.8,0,0);
        Point pos = player->getPosition();
        float d= .1;

        glPushMatrix();
        glTranslatef(pos.x, pos.y, 0);

        glLineWidth(3);
        glBegin(GL_LINES);

        //bottom line
        plot(-d, -d);
        plot(d, -d);

        // top line
        plot(-d, d);
        plot(d, d);

        glEnd();

        glLineWidth(1);
        // middle bars
        glBegin(GL_LINES);
        plot(-d, -d);
        plot(-d, d);

        plot(-.05, -d);
        plot(-.05, d);

        plot(0, -d);
        plot(0, d);

        plot(.05, -d);
        plot(.05, d);

        plot(d, -d);
        plot(d, d);

        glEnd();

        glPopMatrix();
    }

    BasePlayer* updateWrapperChain(){
        if(clock() < obit){
            return this;
        }
        else{
            return player;
        }
    }

    void moveUp() override{
    }

    void moveDown() override{
    }

    void moveLeft() override{
    }

    void moveRight() override{
    }

    void shiftUp() override{
    }

    void shiftDown() override{
    }

    void shiftLeft() override{
    }

    void shiftRight() override{
    }


};


#endif
