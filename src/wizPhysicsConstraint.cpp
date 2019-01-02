#include "wizPhysicsConstraint.h"

wizPhysicsConstraint::wizPhysicsConstraint()
{
    particles = NULL;
}

wizPhysicsConstraint::wizPhysicsConstraint(wizPhysicsParticle* _src, wizPhysicsParticle* _dst)
{
    particles = new wizPhysicsParticle*[2];
    particles[0] = _src;
    particles[1] = _dst;
    length = _src->getPosition()->sub(*_dst->getPosition()).length();
}

wizPhysicsConstraint::wizPhysicsConstraint(wizPhysicsParticle* _src, wizPhysicsParticle* _dst, float _length)
{
    particles = new wizPhysicsParticle*[2];
    particles[0] = _src;
    particles[1] = _dst;
    length = _length;
}

wizPhysicsConstraint::~wizPhysicsConstraint()
{
    if (particles!=NULL) delete[] particles;
}

void wizPhysicsConstraint::setParticles(wizPhysicsParticle** _particle)
{
    particles = _particle;
}

void wizPhysicsConstraint::setLength(float _length)
{
    length = _length;
}

wizPhysicsParticle** wizPhysicsConstraint::getParticles()
{
    return particles;
}

float wizPhysicsConstraint::getLength()
{
    return length;
}

void wizPhysicsConstraint::satisfy()
{
    float restLength = length;
    float restLength2 = length*length;
    float invMass1 = particles[0]->getInverseMass();
    float invMass2 = particles[1]->getInverseMass();
    float invMass = invMass1 + invMass2;

    if (invMass < 0.000001f) return;

    wizVector3* x1 = particles[0]->getTarget();
    wizVector3* x2 = particles[1]->getTarget();
    wizVector3 delta = x2->sub(*x1);

    float delta2 = delta.dot(delta);
    float diff = restLength2/(delta2 + restLength2)-0.5f;
    diff *= -2.0f;

    delta = delta.mul(diff/invMass);
    wizVector3 delta0 = delta.mul(invMass1);
    wizVector3 delta1 = delta.mul(invMass2);
    x1->setX(x1->getX()+delta0.getX());
    x1->setY(x1->getY()+delta0.getY());
    x1->setZ(x1->getZ()+delta0.getZ());
    x2->setX(x2->getX()-delta1.getX());
    x2->setY(x2->getY()-delta1.getY());
    x2->setZ(x2->getZ()-delta1.getZ());
}
