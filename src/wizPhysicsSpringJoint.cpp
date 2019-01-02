#include "wizPhysicsSpringJoint.h"

wizPhysicsSpringJoint::wizPhysicsSpringJoint() : wizPhysicsJoint()
{
    scale = 0;
    length = 0;
}

wizPhysicsSpringJoint::~wizPhysicsSpringJoint()
{
}

void wizPhysicsSpringJoint::calculateLength()
{
    length = getTranslatedTargetPoint().sub(getTranslatedSourcePoint()).length();
}

void wizPhysicsSpringJoint::setLength(float _length)
{
    length = _length;
}

void wizPhysicsSpringJoint::setScale(float _scale)
{
    scale = _scale;
}

float wizPhysicsSpringJoint::getLength()
{
    return length;
}

float wizPhysicsSpringJoint::getScale()
{
    return scale;
}

void wizPhysicsSpringJoint::update(float _dt)
{
    wizVector3 _src = getTranslatedTargetPoint();
    wizVector3 _tgt = getTranslatedSourcePoint();
    wizVector3 vec = _src.sub(_tgt);
    float diffLength = vec.length();
    float diff = diffLength - length;
    vec = vec.normalize();

    source->applyImpulse(vec.mul(diff*scale), _src);
    source->applyImpulse(vec.mul(-diff*scale), _tgt);
}
