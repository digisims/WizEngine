#ifndef WIZPHYSICSCONSTRAINT_H
#define WIZPHYSICSCONSTRAINT_H

#include "wizPhysicsParticle.h"

class wizPhysicsConstraint
{
    public:

    wizPhysicsConstraint();
    wizPhysicsConstraint(wizPhysicsParticle* _src, wizPhysicsParticle* _dst);
    wizPhysicsConstraint(wizPhysicsParticle* _src, wizPhysicsParticle* _dst, float _length);
    virtual ~wizPhysicsConstraint();

    void setParticles(wizPhysicsParticle** _particle);
    void setLength(float _length);
    wizPhysicsParticle** getParticles();
    float getLength();

    void satisfy();

    protected:

    wizPhysicsParticle** particles;
    float length;
};

#endif // WIZPHYSICSCONSTRAINT_H
