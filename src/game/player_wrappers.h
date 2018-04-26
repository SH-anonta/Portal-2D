#ifndef PLAYER_WRAPPER_H
#define PLAYER_WRAPPER_H

class BasePlayer{
public:

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

    virtual void takeDamage()= 0;

    virtual Bullet shootBullet()= 0;

    virtual void updateDirection(Direction new_direction)= 0;

    // getters
    virtual int getHealth()= 0;

    virtual Direction getDirection()= 0;

    virtual Point getPosition()= 0;

    virtual Point getNextPosition()= 0;

    virtual Color getColor()= 0;

    // setters
    virtual void setHealth(int health)= 0;

    virtual void setDirection(Direction d)= 0;

    virtual void setPosition(Point& pos)= 0;

    virtual void setNextPosition(const Point& pos)= 0;

    virtual void setColor(const Color& color)= 0;


};

// player wrapper classes:

class PlayerWrapper: public BasePlayer{
protected:
    BasePlayer* player;
public:

    PlayerWrapper(BasePlayer* player){
        this->player = player;
    }

    BasePlayer* getWrappedObject(){
        return player;
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

    void takeDamage() override{
        player->takeDamage();
    }

    Bullet shootBullet() override{
        return player->shootBullet();
    }

    void updateDirection(Direction new_direction) override{
        player->updateDirection(new_direction);
    }

    // getters
    int getHealth() override{
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
    void setHealth(int health) override{
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
};

class PlayerShield: public PlayerWrapper{
public:
    float shield_rotate_angle;

    PlayerShield(BasePlayer* player)
    :PlayerWrapper(player){
        shield_rotate_angle = 0;
    }

    void draw(){
        glColor3f(0,1,0);
        Point p = player->getPosition();

        glPushMatrix();
        shield_rotate_angle+= 5;

        Point position = player->getPosition();
        glTranslatef(position.x, position.y, 0);
        glRotatef(shield_rotate_angle, 0,0, -1);
        glTranslatef(-1*position.x, -1*position.y, 0);

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

    void takeDamage(){
        // intentionally reuse to take damage
        return;
    }
};

#endif
