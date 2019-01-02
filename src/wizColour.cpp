#include "wizColour.h"

wizColour::wizColour()
{
    r = g = b = a = 0;
    v = NULL;
}

wizColour::wizColour(float _r, float _g, float _b, float _a)
{
    r = _r;
    g = _g;
    b = _b;
    a = _a;
    v = NULL;
}

wizColour::~wizColour()
{
    if (v!=NULL) delete v;
}

void wizColour::setAlpha(float _a)
{
    a = _a;
}

float wizColour::getAlpha()
{
    return a;
}

GLubyte wizColour::getUAlpha()
{
    return (GLubyte)(a*255);
}

void wizColour::setRed(float _r)
{
    r = _r;
}

float wizColour::getRed()
{
    return r;
}

GLubyte wizColour::getURed()
{
    return (GLubyte)(r*255);
}

void wizColour::setGreen(float _g)
{
    g = _g;
}

float wizColour::getGreen()
{
    return g;
}

GLubyte wizColour::getUGreen()
{
    return (GLubyte)(g*255);
}

void wizColour::setBlue(float _b)
{
    b = _b;
}

float wizColour::getBlue()
{
    return b;
}

GLubyte wizColour::getUBlue()
{
    return (GLubyte)(b*255);
}

float* wizColour::getArray()
{
    if (v==NULL)
    {
        v = new float[4];
    }

    v[0] = r;
    v[1] = g;
    v[2] = b;
    v[3] = a;

    return v;
}

wizColour wizColour::mul(float _c)
{
    return wizColour(r * _c, g * _c, b * _c, a * _c);
}

wizColour wizColour::add(float _c)
{
    return wizColour(r + _c, g + _c, b + _c, a + _c);
}

wizColour wizColour::sub(float _c)
{
    return wizColour(r - _c, g - _c, b - _c, a - _c);
}

wizColour wizColour::add(wizColour _colour)
{
        return wizColour(r + _colour.getRed(), g + _colour.getGreen(), b + _colour.getBlue(), a + _colour.getAlpha());
}

wizColour wizColour::sub(wizColour _colour)
{
        return wizColour(r - _colour.getRed(), g - _colour.getGreen(), b - _colour.getBlue(), a - _colour.getAlpha());
}
