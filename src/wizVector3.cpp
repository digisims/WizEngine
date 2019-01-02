#include "wizVector3.h"

wizVector3::wizVector3()
{
    x = y = z = 0;
}

wizVector3::wizVector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

void wizVector3::setX(float _x)
{
    x = _x;
}

void wizVector3::setY(float _y)
{
    y = _y;
}

void wizVector3::setZ(float _z)
{
    z = _z;
}

float wizVector3::getX()
{
    return x;
}

float wizVector3::getY()
{
    return y;
}

float wizVector3::getZ()
{
    return z;
}

float* wizVector3::getArray()
{
    if (v==NULL)
    {
        v = new float[3];
    }

    v[0] = x;
    v[1] = y;
    v[2] = z;

    return v;
}

float* wizVector3::getArray(float _w)
{
    if (v==NULL)
    {
        v = new float[4];
    }

    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = _w;

    return v;
}

float wizVector3::length()
{
    return sqrt(x*x+y*y+z*z);
}

wizVector3 wizVector3::normalize()
{
    float l = length();

    if (l!=0)
    {
        l = 1.0f / l;
        return wizVector3(x*l, y*l, z*l);
    }
    else
    {
        return wizVector3(x, y, z);
    }
}

float wizVector3::dot(wizVector3 _vector)
{
    return x * _vector.getX() + y * _vector.getY() + z * _vector.getZ();
}

wizVector3 wizVector3::cross(wizVector3 _vector)
{
    return wizVector3(y * _vector.getZ() - z * _vector.getY(), z * _vector.getX() - x * _vector.getZ(), x * _vector.getY() - y * _vector.getX());
}

wizVector3 wizVector3::mul(float _c)
{
    return wizVector3(x * _c, y * _c, z * _c);
}

wizVector3 wizVector3::mul(wizVector3 _vector)
{
    return wizVector3(x * _vector.getX(), y * _vector.getY(), z * _vector.getZ());
}

wizVector3 wizVector3::mul(float* _m)
{
    return wizVector3(x * _m[0] + y * _m[4] + z * _m[8] + 1 * _m[12],
                      x * _m[1] + y * _m[5] + z * _m[9] + 1 * _m[13],
                      x * _m[2] + y * _m[6] + z * _m[10] + 1 * _m[14]);
}

wizVector3 wizVector3::add(float _c)
{
    return wizVector3(x + _c, y + _c, z + _c);
}

wizVector3 wizVector3::sub(float _c)
{
    return wizVector3(x - _c, y - _c, z - _c);
}

wizVector3 wizVector3::add(wizVector3 _vector)
{
    return wizVector3(x + _vector.getX(), y + _vector.getY(), z + _vector.getZ());
}

wizVector3 wizVector3::sub(wizVector3 _vector)
{
    return wizVector3(x - _vector.getX(), y - _vector.getY(), z - _vector.getZ());
}
