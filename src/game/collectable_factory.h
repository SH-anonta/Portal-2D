
#ifndef COLLECTABLE_FACTORY_H
#define COLLECTABLE_FACTORY_H

class CollectableFactory{
public:

    // given position point create a collectable at that position
    virtual Collectable* getCollectable(const Point& pos){
    }
};

class RandomCollectableFactory: public CollectableFactory{
public:
    RandomCollectableFactory(){

    }

    Collectable* getCollectable(const Point& pos) override{
        float random = randomf();

        if(random < .25){
            return new HealthCollectable(pos);
        }
        else if(random < .5){
            return new ShieldCollectable(pos);
        }
        else if(random < .75){
            return new BearTrapCollectable(pos);
        }
        else{
            return new SpeedBoostCollectable(pos);
        }
    }
};

#endif
