#ifndef WIZINTERSECTPOINT_H
#define WIZINTERSECTPOINT_H

#include "wizVector3.h"
#include "wizRay.h"

#include <cstdlib>

class wizIntersectionPoint
{
    public:

    static const unsigned int POINT_INTERSECTION  = 0;
    static const unsigned int POINT_COINCIDE = 1;
    static const unsigned int POINT_MISS = 2;

    wizIntersectionPoint();
    wizIntersectionPoint(unsigned int _type, wizVector3 _point, wizVector3 _normal, float _distance, wizRay _ray);
    virtual ~wizIntersectionPoint();

    void setType(unsigned int _type);
    void setPoint(wizVector3 _point);
    void setNormal(wizVector3 _normal);
    void setRay(wizRay _ray);
    void setDistance(float _distance);
    unsigned int getType();
    wizVector3 getPoint();
    wizVector3 getNormal();
    wizRay getRay();
    float getDistance();

    protected:

    unsigned int type;
    wizVector3 point;
    wizVector3 normal;
    wizRay ray;
    float distance;
};

#endif // WIZINTERSECTPOINT_H
