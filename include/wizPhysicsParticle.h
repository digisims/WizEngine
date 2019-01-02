#ifndef WIZPHYSICSPARTICLE_H
#define WIZPHYSICSPARTICLE_H

#include "wizVector3.h"

class wizPhysicsParticle
{
    public:

    wizPhysicsParticle();
    wizPhysicsParticle(wizVector3* _position, float _mass);
    virtual ~wizPhysicsParticle();

    void setPosition(wizVector3* _position);
    void setTarget(wizVector3* _target);
    void setMass(float _mass);
    void setCollided(bool _collided);
    wizVector3* getPosition();
    wizVector3* getTarget();
    bool getCollided();
    float getMass();
    float getInverseMass();

    void update(float _dt);

    protected:

    wizVector3* position;
    wizVector3* target;
    wizVector3* force;
    bool collided;
    float CoF;
    float mass;
    float invMass;
};

#endif // WIZPHYSICSPARTICLE_H
