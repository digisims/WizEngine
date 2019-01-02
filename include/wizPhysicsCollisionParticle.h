#ifndef WIZPHYSICSCOLLISIONPARTICLE_H
#define WIZPHYSICSCOLLISIONPARTICLE_H

#include "wizPhysicsParticle.h"
#include "wizPhysicsConstraint.h"

class wizPhysicsCollisionParticle
{
    public:

    wizPhysicsCollisionParticle();
    wizPhysicsCollisionParticle(wizVector3* _position, wizVector3* _target, wizPhysicsParticle** _particle);
    virtual ~wizPhysicsCollisionParticle();

    void create(wizVector3* _position, wizVector3* _target, wizPhysicsParticle** _particle);
    void update(wizVector3* _target);
    void satisfy();

    wizPhysicsParticle* getParticle();

    protected:

    wizPhysicsParticle* particle;
    wizPhysicsConstraint** constraints;
};

#endif // WIZPHYSICSCOLLISIONPARTICLE_H
