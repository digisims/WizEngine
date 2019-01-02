#ifndef WIZFADEWIPEEFFECT_H
#define WIZFADEWIPEEFFECT_H

#include "wizFadeEffect.h"
#include "wizPrimitives.h"
#include "wizColour.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#define WIPE_RIGHT      0
#define WIPE_LEFT       1
#define WIPE_DOWN       2
#define WIPE_UP         3
#define WIPE_SPHERE_OUT 4
#define WIPE_SPHERE_IN  5

class wizFadeWipeEffect : public wizFadeEffect
{
    public:

    wizFadeWipeEffect(float _maxTime, bool _allowInterrupt, wizPrimitives* _primitive, wizColour _dst, unsigned int _dir, bool _cover);
    virtual ~wizFadeWipeEffect();

    void render();

    protected:

    bool cover;
    unsigned int direction;
    wizColour dst;
    wizPrimitives* primitive;
};

#endif // WIZFADEWIPEEFFECT_H
