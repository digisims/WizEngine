#include "wizPhysicsParticle.h"

wizPhysicsParticle::wizPhysicsParticle()
{
    position = NULL;
    target = NULL;
    force = NULL;
    mass = 0;
    invMass = 0;
    CoF = 0.2f;
    collided = false;
}

wizPhysicsParticle::wizPhysicsParticle(wizVector3* _position, float _mass)
{
    position = _position;
    target = new wizVector3(*position);
    force = new wizVector3();
    mass = _mass;
    invMass = 1 / mass;
    CoF = 0.2f;
    collided = false;
}

wizPhysicsParticle::~wizPhysicsParticle()
{
    if (position != NULL) delete position;
    if (target != NULL) delete target;
    if (force != NULL) delete force;
}

void wizPhysicsParticle::setPosition(wizVector3* _position)
{
    position = _position;
    if (target == NULL) target = new wizVector3(*_position);
}

void wizPhysicsParticle::setTarget(wizVector3* _target)
{
    target = _target;
}

void wizPhysicsParticle::setMass(float _mass)
{
    mass = _mass;
    invMass = 1.0f / mass;
}

void wizPhysicsParticle::setCollided(bool _collided)
{
    collided = _collided;
}

wizVector3* wizPhysicsParticle::getPosition()
{
    return position;
}

wizVector3* wizPhysicsParticle::getTarget()
{
    return target;
}

float wizPhysicsParticle::getMass()
{
    return mass;
}

float wizPhysicsParticle::getInverseMass()
{
    return invMass;
}

bool wizPhysicsParticle::getCollided()
{
    return collided;
}

void wizPhysicsParticle::update(float _dt)
{
    if (force == NULL) force = new wizVector3();

    wizVector3 tmp(*target);
    wizVector3 vel = target->sub(*position);

    if (collided)
    {
        vel = vel.mul(CoF);
    }

    wizVector3 tmpTarget = target->add(vel.add(force->mul(_dt*_dt*invMass)));
    target->setX(tmpTarget.getX());
    target->setY(tmpTarget.getY());
    target->setZ(tmpTarget.getZ());
    position->setX(tmp.getX());
    position->setY(tmp.getY());
    position->setZ(tmp.getZ());
    force->setX(0);
    force->setY(0);
    force->setZ(-1.0f);
    collided = false;
}
