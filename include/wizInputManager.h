#ifndef WIZINPUT_H
#define WIZINPUT_H

#include "DGE_Input.h"
#include "wizVector2.h"
#include "wizGame.h"

#include <vector>

#define BUTTON_UP           0
#define BUTTON_DOWN         1
#define BUTTON_LEFT         2
#define BUTTON_RIGHT        3
#define BUTTON_SELECT       4
#define BUTTON_MENU         5
#define BUTTON_L            6
#define BUTTON_R            7
#define BUTTON_A            8
#define BUTTON_B            9
#define BUTTON_X            10
#define BUTTON_Y            11
#define BUTTON_VOLUME_DOWN  12
#define BUTTON_VOLUME_UP    13
#define KEY_COUNT           14

class wizInputManager
{
    public:

    static void initialize();
    static void destroy();

    static void flush();
    static void update();

    static int getLastUpdate();

    static int getKeyPressed();
    static int getPreviousKeyPressed();
    static bool wasKeyPressed();
    static bool isKeyPressed();
    static bool isKeyDown(unsigned int _key);
    static bool wasKeyDown(unsigned int _key);
    static bool isKeyPressed(unsigned int _key);

    static bool isTouched();
    static bool isClicked();
    static bool isDoubleClicked();
    static wizVector2 getTouchPosition();
    static wizVector2 getPreviousTouchPosition();
    static void setTouchPosition(wizVector2 _position);

    protected:

    static wizVector2 touchPosition;
    static wizVector2 previousTouchPosition;
    static unsigned int doubleClickThreshold;
    static int lastUpdate;
    static std::vector<unsigned int> clickTime;
    static bool* buttonDown;
    static bool* buttonPressed;
    static bool* previousButtonDown;
    static bool touched;
    static bool previousTouched;
    static int KEY_LIST[];
};

#endif // WIZINPUT_H
