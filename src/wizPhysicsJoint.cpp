#include "wizPhysicsJoint.h"

wizPhysicsJoint::wizPhysicsJoint()
{
    source = NULL;
    target = NULL;
}

wizPhysicsJoint::~wizPhysicsJoint()
{
}

void wizPhysicsJoint::setSource(wizPhysicsBody* _source)
{
    source = _source;
}

void wizPhysicsJoint::setTarget(wizPhysicsBody* _target)
{
    target = _target;
}

void wizPhysicsJoint::setSourcePoint(wizVector3 _point)
{
    sourcePoint = _point;
}

void wizPhysicsJoint::setTargetPoint(wizVector3 _point)
{
    targetPoint = _point;
}

wizPhysicsBody* wizPhysicsJoint::getSource()
{
    return source;
}

wizPhysicsBody* wizPhysicsJoint::getTarget()
{
    return target;
}

wizVector3 wizPhysicsJoint::getSourcePoint()
{
    return sourcePoint;
}

wizVector3 wizPhysicsJoint::getTargetPoint()
{
    return targetPoint;
}

wizVector3 wizPhysicsJoint::getTranslatedSourcePoint()
{
    return sourcePoint.add(*source->getTranslation());
}

wizVector3 wizPhysicsJoint::getTranslatedTargetPoint()
{
    return targetPoint.add(*target->getTranslation());
}
