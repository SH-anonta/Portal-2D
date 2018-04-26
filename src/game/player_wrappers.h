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

};

// player wrapper classes:

class PlayerWrapper: public BasePlayer{
    BasePlayer* player;
public:

    PlayerWrapper(BasePlayer* player){
        this->player = player;
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


};

class PlayerShield: public PlayerWrapper{
    void draw(){
    }
};

#endif
