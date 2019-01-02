#ifndef WIZPHYSICSSPRINGJOINT_H
#define WIZPHYSICSSPRINGJOINT_H

#include "wizPhysicsJoint.h"

class wizPhysicsSpringJoint : public wizPhysicsJoint
{
    public:

    wizPhysicsSpringJoint();
    virtual ~wizPhysicsSpringJoint();

    void calculateLength();
    void setLength(float _length);
    void setScale(float _scale);
    float getLength();
    float getScale();

    void update(float _dt);

    protected:

    float length;
    float scale;
};

#endif // WIZPHYSICSSPRINGJOINT_H
