#include "wizRay.h"

wizRay::wizRay()
{
}

wizRay::wizRay(wizVector3 _origin, wizVector3 _direction)
{
    origin = _origin;
    direction = _direction;
}

wizRay::~wizRay()
{
}

void wizRay::setOrigin(wizVector3 _origin)
{
    origin = _origin;
}

void wizRay::setDirection(wizVector3 _direction)
{
    direction = _direction;
}

wizVector3 wizRay::getOrigin()
{
    return origin;
}

wizVector3 wizRay::getDirection()
{
    return direction;
}
