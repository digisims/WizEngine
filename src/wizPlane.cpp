#include "wizPlane.h"

wizPlane::wizPlane()
{

}

wizPlane::wizPlane(float _x, float _y, float _z, float _d)
{
    x = _x;
    y = _y;
    z = _z;
    d = _d;
}

wizPlane::wizPlane(wizVector3 _v1, wizVector3 _v2, wizVector3 _v3)
{
    calculate(_v1, _v2, _v3);
}

wizPlane::~wizPlane()
{
}

void wizPlane::setX(float _x)
{
    x = _x;
}

void wizPlane::setY(float _y)
{
    y = _y;
}

void wizPlane::setZ(float _z)
{
    z = _z;
}

void wizPlane::setD(float _d)
{
    d = _d;
}

float wizPlane::getX()
{
    return x;
}

float wizPlane::getY()
{
    return y;
}

float wizPlane::getZ()
{
    return z;
}

float wizPlane::getD()
{
    return d;
}

wizPlane wizPlane::normalize()
{
    float l = sqrt(x*x+y*y+z*z);

    if (l!=0)
    {
        l = 1.0f / l;
        return wizPlane(x * l, y * l, z * l, d * l);
    }
    else
    {
        return wizPlane(x, y, z, d);
    }
}

void wizPlane::calculate(wizVector3 _v1, wizVector3 _v2, wizVector3 _v3)
{
    wizVector3 u = _v2.sub(_v1);
    wizVector3 v = _v3.sub(_v1);
    wizVector3 n = u.cross(v).normalize();

    x = n.getX();
    y = n.getY();
    z = n.getZ();
    d = -(_v2.getX()*x + _v2.getY() * y + _v2.getZ() * z);

    /*
    x = _v1.getY() * (_v2.getZ() - _v3.getZ()) + _v2.getY() * (_v3.getZ() - _v1.getZ()) + _v3.getY() * (_v1.getZ() - _v2.getZ());
    y = _v1.getZ() * (_v2.getX() - _v3.getX()) + _v2.getZ() * (_v3.getX() - _v1.getX()) + _v3.getZ() * (_v1.getX() - _v2.getX());
    z = _v1.getX() * (_v2.getY() - _v3.getY()) + _v2.getX() * (_v3.getY() - _v1.getY()) + _v3.getX() * (_v1.getY() - _v2.getY());
    d = -(_v1.getX() * (_v2.getY() * _v3.getZ() - _v3.getY() * _v2.getZ()) + _v2.getX() * (_v3.getY() * _v1.getZ() - _v1.getY() * _v3.getZ()) + _v3.getX() * (_v1.getY() * _v2.getZ() - _v2.getY() * _v1.getZ()));
    */

    float l = sqrt(x * x + y * y + z * z);

    if (l != 0)
    {
        l = 1.0f / l;
        x *= l;
        y *= l;
        z *= l;
        d *= l;
    }
}

float wizPlane::distanceToPoint(wizVector3 _point)
{
    return x * _point.getX() + y * _point.getY() + z * _point.getZ() + d;
}
