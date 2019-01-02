#ifndef WIZVECTOR3_H
#define WIZVECTOR3_H

#include <math.h>
#include <cstdlib>

class wizVector3
{
    public:

    wizVector3();
    wizVector3(float _x, float _y, float _z);

    void setX(float _x);
    void setY(float _y);
    void setZ(float _z);
    float getX();
    float getY();
    float getZ();
    float* getArray();
    float* getArray(float _w);

    float length();
    wizVector3 normalize();

    float dot(wizVector3 _vector);
    wizVector3 cross(wizVector3 _vector);

    wizVector3 mul(float _c);
    wizVector3 mul(float* _m);
    wizVector3 mul(wizVector3 _vector);
    wizVector3 add(float _c);
    wizVector3 sub(float _c);
    wizVector3 add(wizVector3 _vector);
    wizVector3 sub(wizVector3 _vector);

    protected:

    float x;
    float y;
    float z;
    float* v;
};

#endif // WIZVECTOR3_H
