#ifndef WIZFADEINEFFECT_H
#define WIZFADEINEFFECT_H

#include "wizFadeEffect.h"
#include "wizPrimitives.h"
#include "wizColour.h"

#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizFadeToEffect : public wizFadeEffect
{
    public:

    wizFadeToEffect(float _maxTime, bool _allowInterrupt, wizPrimitives* _primitive, wizColour _src, wizColour _dst);
    virtual ~wizFadeToEffect();

    void render();

    protected:

    wizColour src;
    wizColour dst;
    wizPrimitives* primitive;
};

#endif // WIZFADEINEFFECT_H
