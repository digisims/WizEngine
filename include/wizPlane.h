#ifndef WIZPLANE_H
#define WIZPLANE_H

#include "wizVector3.h"

class wizPlane
{
    public:

    wizPlane();
    wizPlane(float _x, float _y, float _z, float _d);
    wizPlane(wizVector3 _v1, wizVector3 _v2, wizVector3 _v3);
    virtual ~wizPlane();

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);
    void setD(float _d);
    float getX();
    float getY();
    float getZ();
    float getD();

    wizPlane normalize();

    float distanceToPoint(wizVector3 _point);

    protected:

    void calculate(wizVector3 _v1, wizVector3 _v2, wizVector3 _v3);

    float x;
    float y;
    float z;
    float d;
};

#endif // WIZPLANE_H
