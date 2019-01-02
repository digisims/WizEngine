#ifndef WIZRAY_H
#define WIZRAY_H

#include "wizVector3.h"

#include <cstdlib>

class wizRay
{
    public:

    wizRay();
    wizRay(wizVector3 _origin, wizVector3 _direction);
    virtual ~wizRay();

    void setOrigin(wizVector3 _origin);
    void setDirection(wizVector3 _direction);
    wizVector3 getOrigin();
    wizVector3 getDirection();

    protected:

    wizVector3 origin;
    wizVector3 direction;
};

#endif // WIZRAY_H
