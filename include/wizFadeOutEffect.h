#ifndef WIZFADEOUTEFFECT_H
#define WIZFADEOUTEFFECT_H

#include "wizFadeEffect.h"
#include "wizPrimitives.h"
#include "wizColour.h"

#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizFadeOutEffect : public wizFadeEffect
{
    public:

    wizFadeOutEffect(float _maxTime, bool _allowInterrupt, wizPrimitives* _primitive, wizColour _scr, wizColour _dst);
    virtual ~wizFadeOutEffect();

    void render();

    protected:

    wizColour src;
    wizColour dst;
    wizPrimitives* primitive;
};

#endif // WIZFADEOUTEFFECT_H
