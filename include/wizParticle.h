#ifndef WIZPARTICLE_H
#define WIZPARTICLE_H

#include "wizVector3.h"
#include "wizSpriteEntity.h"

class wizParticle
{
    public:

    wizParticle();
    virtual ~wizParticle();

    virtual void setLife(float _life);
    virtual void setDecayRate(float _decayRate);
    virtual float getLife();
    virtual float getDecayRate();
    virtual bool isDead();

    virtual void update(float _dt) = 0;

    protected:

    float life;
    float decayRate;
};

#endif // WIZPARTICLE_H
