#include "wizPhysicsCollisionParticle.h"

wizPhysicsCollisionParticle::wizPhysicsCollisionParticle()
{
}

wizPhysicsCollisionParticle::wizPhysicsCollisionParticle(wizVector3* _position, wizVector3* _target, wizPhysicsParticle** _particle)
{
    create(_position, _target, _particle);
}

wizPhysicsCollisionParticle::~wizPhysicsCollisionParticle()
{
    if (particle!=NULL) delete particle;
    if (constraints!=NULL) delete[] constraints;
}

void wizPhysicsCollisionParticle::update(wizVector3* _target)
{
    particle->setTarget(_target);
}

void wizPhysicsCollisionParticle::create(wizVector3* _position, wizVector3* _target, wizPhysicsParticle** _particle)
{
    particle = new wizPhysicsParticle(_position, 1.0f);

    constraints = new wizPhysicsConstraint*[4];
    constraints[0] = new wizPhysicsConstraint(particle, _particle[0]);
    constraints[1] = new wizPhysicsConstraint(particle, _particle[1]);
    constraints[2] = new wizPhysicsConstraint(particle, _particle[2]);
    constraints[3] = new wizPhysicsConstraint(particle, _particle[3]);

    particle->setTarget(_target);
    particle->setPosition(_target);
}

void wizPhysicsCollisionParticle::satisfy()
{
    for (unsigned int i=0; i<4; i++)
    {
        constraints[i]->satisfy();
    }
}

wizPhysicsParticle* wizPhysicsCollisionParticle::getParticle()
{
    return particle;
}
