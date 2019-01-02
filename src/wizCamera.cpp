#include "wizCamera.h"

wizCamera::wizCamera()
{
}

wizCamera::~wizCamera()
{
}

bool wizCamera::isBoxInside(wizVector2 _min, wizVector2 _size)
{
    return !(_min.getX() + _size.getX() < 0 || _min.getX() >= DGE_DISPLAY_DEFAULT_WIDTH || _min.getY() + _size.getY() < 0 || _min.getY() >= DGE_DISPLAY_DEFAULT_HEIGHT);
}
