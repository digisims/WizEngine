#ifndef WIZCOLOUR_H
#define WIZCOLOUR_H

#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <cstdlib>

class wizColour
{
    public:

    wizColour();
    wizColour(float _r, float _g, float _b, float _a);
    virtual ~wizColour();

    void setAlpha(float _a);
    void setRed(float _r);
    void setGreen(float _g);
    void setBlue(float _b);
    float getAlpha();
    float getRed();
    float getGreen();
    float getBlue();
    GLubyte getUAlpha();
    GLubyte getURed();
    GLubyte getUGreen();
    GLubyte getUBlue();
    float* getArray();

    wizColour mul(float _c);
    wizColour add(float _c);
    wizColour sub(float _c);
    wizColour add(wizColour _colour);
    wizColour sub(wizColour _colour);

    protected:

    float a;
    float r;
    float g;
    float b;
    float* v;
};

#endif // WIZCOLOUR_H
