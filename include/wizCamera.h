#ifndef WIZCAMERA_H
#define WIZCAMERA_H

#include "wizVector2.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizCamera
{
    public:

    wizCamera();
    virtual ~wizCamera();

    virtual void applySettings() = 0;
    virtual void undoSettings() = 0;

    bool isBoxInside(wizVector2 _min, wizVector2 _size);
};

#endif // WIZCAMERA_H
