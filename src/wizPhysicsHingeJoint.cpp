#include "wizPhysicsHingeJoint.h"

wizPhysicsHingeJoint::wizPhysicsHingeJoint()
{
}

wizPhysicsHingeJoint::~wizPhysicsHingeJoint()
{
}

void wizPhysicsHingeJoint::constrainAngle(bool _x, bool _y, bool _z)
{
    constrainAxis.setX(_x ? 1 : 0);
    constrainAxis.setY(_y ? 1 : 0);
    constrainAxis.setZ(_z ? 1 : 0);
}

void wizPhysicsHingeJoint::setMinimumXAngle(float _angle)
{
    minAngle.setX(_angle);
}

void wizPhysicsHingeJoint::setMaximumXAngle(float _angle)
{
    maxAngle.setX(_angle);
}

void wizPhysicsHingeJoint::setMinimumYAngle(float _angle)
{
    minAngle.setY(_angle);
}

void wizPhysicsHingeJoint::setMaximumYAngle(float _angle)
{
    maxAngle.setY(_angle);
}

void wizPhysicsHingeJoint::setMinimumZAngle(float _angle)
{
    minAngle.setZ(_angle);
}

void wizPhysicsHingeJoint::setMaximumZAngle(float _angle)
{
    maxAngle.setZ(_angle);
}

bool wizPhysicsHingeJoint::isXConstrained()
{
    return constrainAxis.getX() > 0;
}

bool wizPhysicsHingeJoint::isYConstrained()
{
    return constrainAxis.getY() > 0;
}

bool wizPhysicsHingeJoint::isZConstrained()
{
    return constrainAxis.getZ() > 0;
}

void wizPhysicsHingeJoint::setScale(float _scale)
{
    scale = _scale;
}

float wizPhysicsHingeJoint::getScale()
{
    return scale;
}

void wizPhysicsHingeJoint::update(float _dt)
{
    if (isXConstrained())
    {
        float angle = target->getRotation()->getX() - source->getRotation()->getX();
        float diff = 0;

        if (angle < minAngle.getX())
        {
            diff = minAngle.getX() - angle;
        }
        else if (angle > maxAngle.getX())
        {
            diff = maxAngle.getX() - angle;
        }

        wizVector3 newRotation  = *target->getRotation();
        newRotation.setX(newRotation.getX() + diff * _dt * scale);
        target->setRotation(newRotation);
    }

    if (isYConstrained())
    {
        float angle = target->getRotation()->getY() - source->getRotation()->getY();
        float diff = 0;

        if (angle < minAngle.getY())
        {
            diff = minAngle.getY() - angle;
        }
        else if (angle > maxAngle.getY())
        {
            diff = maxAngle.getY() - angle;
        }

        wizVector3 newRotation  = *target->getRotation();
        newRotation.setY(newRotation.getY() + diff * _dt * scale);
        target->setRotation(newRotation);
    }

    if (isZConstrained())
    {
        float angle = target->getRotation()->getZ() - source->getRotation()->getZ();
        float diff = 0;

        if (angle < minAngle.getZ())
        {
            diff = minAngle.getZ() - angle;
        }
        else if (angle > maxAngle.getZ())
        {
            diff = maxAngle.getZ() - angle;
        }

        wizVector3 newRotation  = *target->getRotation();
        newRotation.setZ(newRotation.getZ() + diff * _dt * scale);
        target->setRotation(newRotation);
    }
}
