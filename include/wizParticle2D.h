#ifndef WIZPARTICLE2D_H
#define WIZPARTICLE2D_H

#include "wizVector2.h"
#include "wizParticle.h"

class wizParticle2D : public wizParticle, public wizSpriteEntity
{
    public:

    wizParticle2D();
    ~wizParticle2D();

    void setVelocity(wizVector2* _velocity);
    void setRotationVelocity(float _rotationVelocity);
    wizVector2* getVelocity();
    float getRotationVelocity();

    void update(float _dt);

    protected:

    float rotationVelocity;
    wizVector2* velocity;
};

#endif // WIZPARTICLE2D_H
