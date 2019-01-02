#ifndef WIZCAMERA2D_H
#define WIZCAMERA2D_H

#include "wizCamera.h"
#include "wizVector2.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizCamera2D : public wizCamera
{
    public:

    wizCamera2D();
    virtual ~wizCamera2D();

    void setEye(wizVector2* _eye);
    wizVector2* getEye();

    void applySettings();
    void undoSettings();

    protected:

    wizVector2* eye;
};

#endif // WIZCAMERA2D_H
