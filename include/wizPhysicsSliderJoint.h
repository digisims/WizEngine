#ifndef WIZPHYSICSSLIDERJOINT_H
#define WIZPHYSICSSLIDERJOINT_H

#include "wizPhysicsSpringJoint.h"

class wizPhysicsSliderJoint : public wizPhysicsSpringJoint
{
    public:

    wizPhysicsSliderJoint();
    virtual ~wizPhysicsSliderJoint();

    void update(float _dt);
};

#endif // WIZPHYSICSSLIDERJOINT_H
