#ifndef WIZLIGHT_H
#define WIZLIGHT_H

#include "wizColour.h"
#include "wizVector3.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizLight
{
    public:

    wizLight();
    virtual ~wizLight();

    virtual void applySettings() = 0;
    virtual void undoSettings();

    void setIndex(unsigned int _idx);
    unsigned int getIndex();

    void setAmbient(wizColour* _ambient);
    void setDiffuse(wizColour* _diffuse);
    void setSpecular(wizColour* _specular);
    void setPosition(wizVector3* _position);
    wizColour* getAmbient();
    wizColour* getDiffuse();
    wizColour* getSpecular();
    wizVector3* getPosition();

    protected:

    wizColour* ambient;
    wizColour* diffuse;
    wizColour* specular;
    wizVector3* position;
    unsigned int idx;
};

#endif // WIZLIGHT_H
