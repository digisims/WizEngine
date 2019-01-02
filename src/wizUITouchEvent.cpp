#include "wizUITouchEvent.h"

wizUITouchEvent::wizUITouchEvent()
{
    point = wizVector2();
    previousPoint = wizVector2();
}

wizUITouchEvent::wizUITouchEvent(wizVector2 _point, wizVector2 _previousPoint)
{
    point = _point;
    previousPoint = _previousPoint;
}

wizUITouchEvent::~wizUITouchEvent()
{
}

wizVector2 wizUITouchEvent::getPoint()
{
    return point;
}

wizVector2 wizUITouchEvent::getPreviousPoint()
{
    return previousPoint;
}
