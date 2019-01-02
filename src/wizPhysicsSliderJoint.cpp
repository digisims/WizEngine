#include "wizPhysicsSliderJoint.h"

wizPhysicsSliderJoint::wizPhysicsSliderJoint() : wizPhysicsSpringJoint()
{
}

wizPhysicsSliderJoint::~wizPhysicsSliderJoint()
{
}

void wizPhysicsSliderJoint::update(float _dt)
{
    wizVector3 _src = getTranslatedTargetPoint();
    wizVector3 _tgt = getTranslatedSourcePoint();
    wizVector3 vec = _src.sub(_tgt);
    float diffLength = vec.length();
    float diff = diffLength - length;

    if (diff>0)
    {
        vec = vec.normalize();

        source->applyImpulse(vec.mul(diff*scale), _src);
        source->applyImpulse(vec.mul(-diff*scale), _tgt);
    }
}
