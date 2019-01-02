#ifndef WIZUITOUCHEVENT_H
#define WIZUITOUCHEVENT_H

#include "wizUIEvent.h"
#include "wizVector2.h"

class wizUITouchEvent : public wizUIEvent
{
    public:

    wizUITouchEvent();
    wizUITouchEvent(wizVector2 _point, wizVector2 _previousPoint);
    virtual ~wizUITouchEvent();

    wizVector2 getPoint();
    wizVector2 getPreviousPoint();

    protected:

    wizVector2 point;
    wizVector2 previousPoint;
};

#endif // WIZUITOUCHEVENT_H
