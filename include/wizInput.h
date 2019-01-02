#ifndef WIZINPUT_H
#define WIZINPUT_H

#include "DGE_Input.h"
#include "wizVector2.h"

class wizInput
{
    public:

    static void initialize();
    static void destroy();

    static void update();

    static bool isKeyDown(int _key);
    static bool isKeyPressed(int _key);

    static bool isScreenTouched();
    static wizVector2 getTouchPosition();

    protected:

    static wizVector2 touchPosition;
};

#endif // WIZINPUT_H
