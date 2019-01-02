#ifndef WIZBOUNDINGVOLUME_H
#define WIZBOUNDINGVOLUME_H

#include "wizVector3.h"
#include "wizIntersectionPoint.h"
#include "wizRay.h"

class wizBoundingVolume
{
    public:

    wizBoundingVolume();
    virtual ~wizBoundingVolume();

    virtual wizVector3 getCenter() = 0;

    protected:
};

#endif // WIZBOUNDINGVOLUME_H
