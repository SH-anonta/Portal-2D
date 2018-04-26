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

class PlayerWrapper: public BasePlayer{
    PlayerWrapper* player;
public:

    void updatePosition() override{
        player->updatePosition();
    }

    void getPlayerObject(){

    }


};

#endif
