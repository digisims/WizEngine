#include "wizVector2.h"

wizVector2::wizVector2()
{
    x = y = 0;
}

wizVector2::wizVector2(float _x, float _y)
{
    x = _x;
    y = _y;
}

void wizVector2::setX(float _x)
{
    x = _x;
}

void wizVector2::setY(float _y)
{
    y = _y;
}

float wizVector2::getX()
{
    return x;
}

float wizVector2::getY()
{
    return y;
}

float wizVector2::length()
{
    return sqrt(x*x+y*y);
}

wizVector2 wizVector2::normalize()
{
    float l = length();

    if (l!=0)
    {
        l = 1.0f / l;
        return wizVector2(x * l, y * l);
    }
    else
    {
        return wizVector2(x, y);
    }
}

float wizVector2::dot(wizVector2 _vector)
{
    return x * _vector.getX() + y * _vector.getY();
}

wizVector2 wizVector2::crossCW(wizVector2 _vector)
{
    float dx = _vector.getX() - x;
    float dy = _vector.getY() - y;
    float l = sqrt(dx*dx+dy*dy);
    l = 1.0f / l;
    dx *= l;
    dy *= l;
    return wizVector2::wizVector2(-dy, dx);
}

wizVector2 wizVector2::crossCCW(wizVector2 _vector)
{
    float dx = _vector.getX() - x;
    float dy = _vector.getY() - y;
    float l = sqrt(dx*dx+dy*dy);
    l = 1.0f / l;
    dx *= l;
    dy *= l;
    return wizVector2::wizVector2(dy, -dx);
}

wizVector2 wizVector2::mul(float _c)
{
    return wizVector2(x * _c, y * _c);
}

wizVector2 wizVector2::add(float _c)
{
    return wizVector2(x + _c, y + _c);
}

wizVector2 wizVector2::sub(float _c)
{
    return wizVector2(x - _c, y - _c);
}

wizVector2 wizVector2::add(wizVector2 _vector)
{
    return wizVector2(x + _vector.getX(), y + _vector.getY());
}

wizVector2 wizVector2::sub(wizVector2 _vector)
{
    return wizVector2(x - _vector.getX(), y - _vector.getY());
}

bool wizVector2::equals(wizVector2 _vector)
{
    return fabs(x-_vector.getX()) < 0.01f && fabs(y-_vector.getY())<0.01f;
}
