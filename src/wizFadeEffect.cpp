#include "wizFadeEffect.h"

wizFadeEffect::wizFadeEffect(float _maxTime, bool _allowInterrupt)
{
    time = 0;
    maxTime = _maxTime;
    allowInterrupt = _allowInterrupt;
    done = false;
}

wizFadeEffect::~wizFadeEffect()
{
}

void wizFadeEffect::render()
{
}

void wizFadeEffect::update(float _delta)
{
    if (allowInterrupt && (wizInputManager::wasKeyPressed() || wizInputManager::isTouched()))
    {
        done = true;
    }

    time += _delta;
    if (time>=maxTime)
    {
        done = true;
        time = maxTime;
    }
}

float wizFadeEffect::getRatio()
{
    return time / maxTime;
}

bool wizFadeEffect::isDone()
{
    return done;
}
