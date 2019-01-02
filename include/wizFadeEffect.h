#ifndef WIZFADEEFFECT_H
#define WIZFADEEFFECT_H

#include "wizInputManager.h"

class wizFadeEffect
{
    public:

    wizFadeEffect(float _maxTime, bool _allowInterrupt);
    virtual ~wizFadeEffect();

    virtual void render();
    virtual void update(float _delta);

    bool isDone();

    protected:

    float getRatio();

    bool done;
    bool allowInterrupt;
    float maxTime;
    float time;
};

#endif // WIZFADEEFFECT_H
