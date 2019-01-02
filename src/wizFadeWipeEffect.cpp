#include "wizFadeWipeEffect.h"

wizFadeWipeEffect::wizFadeWipeEffect(float _maxTime, bool _allowInterrupt, wizPrimitives* _primitive, wizColour _dst, unsigned int _dir, bool _cover) : wizFadeEffect(_maxTime, _allowInterrupt)
{
    cover = _cover;
    direction = _dir;
    dst = _dst;
    primitive = _primitive;
    maxTime = _maxTime;
    allowInterrupt = _allowInterrupt;
}

wizFadeWipeEffect::~wizFadeWipeEffect()
{
}

void wizFadeWipeEffect::render()
{
    float r = getRatio();
    primitive->applyGlobalSettings();
    primitive->enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float x = 0;
    float y = 0;
    float w = 320;
    float h = 240;

    switch (direction)
    {
        case WIPE_RIGHT:
            if (cover)
            {
                w *= r;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            else
            {
                w *= (1-r);
                x = 320 - w;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            break;

        case WIPE_LEFT:
            if (cover)
            {
                x -= 320 * r;
                w = 320 * r;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            else
            {
                w *= (1-r);
                x = 0;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            break;

        case WIPE_DOWN:
            if (cover)
            {
                h *= r;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            else
            {
               h *= (1-r);
               y = 240 - h;
               primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            break;

        case WIPE_UP:
            if (cover)
            {
                y -= 240 * r;
                h = 240 * r;
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            else
            {
                y = 0;
                h = 240 * (1-r);
                primitive->drawRectangle(wizVector2(x, y), wizVector2(w, h), dst);
            }
            break;

        case WIPE_SPHERE_OUT:
            x = 320 / 2;
            y = 240 / 2;
            w = 320 * r;
            h = 320 * r;
            primitive->drawNGon(wizVector2(x, y), wizVector2(w, h), dst, 32);
            break;

        case WIPE_SPHERE_IN:
            x = 320 / 2;
            y = 240 / 2;
            w = 320 * (1-r);
            h = 320 * (1-r);
            primitive->drawNGon(wizVector2(x, y), wizVector2(w, h), dst, 32);
            break;
    }

    primitive->disableBlending();
    primitive->undoGlobalSettings();
}
