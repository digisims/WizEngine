#include "wizFadeInEffect.h"

wizFadeInEffect::wizFadeInEffect(float _maxTime, bool _allowInterrupt, wizPrimitives* _primitive, wizColour _src, wizColour _dst) : wizFadeEffect(_maxTime, _allowInterrupt)
{
    src = _src;
    dst = _dst;
    primitive = _primitive;
    maxTime = _maxTime;
    allowInterrupt = _allowInterrupt;
}

wizFadeInEffect::~wizFadeInEffect()
{
}

void wizFadeInEffect::render()
{
    float r = getRatio();
    wizColour colour = src.mul(1-r).add(dst.mul(r));
    primitive->applyGlobalSettings();
    primitive->enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    primitive->drawRectangle(wizVector2(0, 0), wizVector2(320, 240), colour);
    primitive->disableBlending();
    primitive->undoGlobalSettings();
}
