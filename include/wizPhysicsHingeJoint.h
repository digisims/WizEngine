#ifndef WIZPHYSICSHINGEJOINT_H
#define WIZPHYSICSHINGEJOINT_H

#include "wizPhysicsJoint.h"

class wizPhysicsHingeJoint : public wizPhysicsJoint
{
    public:

    wizPhysicsHingeJoint();
    virtual ~wizPhysicsHingeJoint();

    void setScale(float _scale);
    void constrainAngle(bool _x, bool _y, bool _z);
    void setMinimumXAngle(float _angle);
    void setMaximumXAngle(float _angle);
    void setMinimumYAngle(float _angle);
    void setMaximumYAngle(float _angle);
    void setMinimumZAngle(float _angle);
    void setMaximumZAngle(float _angle);
    bool isXConstrained();
    bool isYConstrained();
    bool isZConstrained();
    float getScale();

    void update(float _dt);

    protected:

    wizVector3 constrainAxis;
    wizVector3 minAngle;
    wizVector3 maxAngle;
    float scale;
};

#endif // WIZPHYSICSHINGEJOINT_H
