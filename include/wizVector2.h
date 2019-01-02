#ifndef WIZVECTOR2_H
#define WIZVECTOR2_H

#include <math.h>

class wizVector2
{
    public:

    wizVector2();
    wizVector2(float _x, float _y);

    void setX(float _x);
    void setY(float _y);
    float getX();
    float getY();

    float length();
    wizVector2 normalize();

    float dot(wizVector2 _vector);
    wizVector2 crossCW(wizVector2 _vector);
    wizVector2 crossCCW(wizVector2 _vector);

    wizVector2 mul(float _c);
    wizVector2 add(float _c);
    wizVector2 sub(float _c);
    wizVector2 add(wizVector2 _vector);
    wizVector2 sub(wizVector2 _vector);

    bool equals(wizVector2 _vector);

    protected:

    float x;
    float y;
};

#endif // WIZVECTOR2_H
