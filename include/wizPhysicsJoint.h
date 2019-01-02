#ifndef WIZPHYSICSJOINT_H
#define WIZPHYSICSJOINT_H

#include "wizVector3.h"
#include "wizPhysicsBody.h"

class wizPhysicsJoint
{
    public:

    wizPhysicsJoint();
    virtual ~wizPhysicsJoint();

    void setSource(wizPhysicsBody* _source);
    void setTarget(wizPhysicsBody* _target);
    void setSourcePoint(wizVector3 _point);
    void setTargetPoint(wizVector3 _point);
    wizPhysicsBody* getSource();
    wizPhysicsBody* getTarget();
    wizVector3 getSourcePoint();
    wizVector3 getTargetPoint();

    virtual void update(float _dt) = 0;

    protected:

    wizVector3 getTranslatedSourcePoint();
    wizVector3 getTranslatedTargetPoint();

    wizPhysicsBody* source;
    wizPhysicsBody* target;
    wizVector3 sourcePoint;
    wizVector3 targetPoint;
};

#endif // WIZPHYSICSJOINT_H
