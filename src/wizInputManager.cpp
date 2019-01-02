#include "wizInputManager.h"

wizVector2 wizInputManager::touchPosition;
wizVector2 wizInputManager::previousTouchPosition;
std::vector<unsigned int> wizInputManager::clickTime;
unsigned int wizInputManager::doubleClickThreshold = 100;   // 1/10th second
int wizInputManager::lastUpdate = -1;
bool wizInputManager::touched = false;
bool wizInputManager::previousTouched = false;
bool* wizInputManager::buttonDown = NULL;
bool* wizInputManager::buttonPressed = NULL;
bool* wizInputManager::previousButtonDown = NULL;
int wizInputManager::KEY_LIST[] = { DKEY_UP, DKEY_DOWN, DKEY_LEFT, DKEY_RIGHT, DKEY_SELECT, DKEY_MENU, DKEY_L, DKEY_R, DKEY_A, DKEY_B, DKEY_X, DKEY_Y, DKEY_VOL_DOWN, DKEY_VOL_UP };

void wizInputManager::initialize()
{
    buttonPressed = new bool[KEY_COUNT];
    buttonDown = new bool[KEY_COUNT];
    previousButtonDown = new bool[KEY_COUNT];

    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        buttonPressed[i] = false;
        buttonDown[i] = false;
        previousButtonDown[i] = false;
    }

    g_cInput.Initialize();
}

void wizInputManager::flush()
{
    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        previousButtonDown[i] = false;
        buttonDown[i] = false;
        buttonPressed[i] = false;
    }

    touched = false;
    previousTouched = false;
}

void wizInputManager::destroy()
{
}

int wizInputManager::getLastUpdate()
{
    return lastUpdate;
}

void wizInputManager::update()
{
    g_cInput.ScanInputDevice();

    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        previousButtonDown[i] = buttonDown[i];
        buttonDown[i] = g_cInput.IsPushKey(wizInputManager::KEY_LIST[i]);
        buttonPressed[i] = g_cInput.IsPushKeyOnce(wizInputManager::KEY_LIST[i]);

        if (buttonDown[i] || buttonPressed[i])
        {
            lastUpdate = SDL_GetTicks();
        }
    }

    previousTouched = touched;
    touched = g_cInput.IsTouch();

    if (touched)
    {
        int tmpX = g_cInput.GetTouchX();
        int tmpY = g_cInput.GetTouchY();

        if (tmpX != touchPosition.getX() || tmpY != touchPosition.getY())
        {
            previousTouchPosition = touchPosition;
            touchPosition = wizVector2(g_cInput.GetTouchX(), g_cInput.GetTouchY());

            lastUpdate = SDL_GetTicks();
        }

        lastUpdate = SDL_GetTicks();
    }
}

int wizInputManager::getKeyPressed()
{
    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        if (buttonDown[i]) return i;
    }

    return -1;
}

int wizInputManager::getPreviousKeyPressed()
{
    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        if (previousButtonDown[i]) return i;
    }

    return -1;
}

bool wizInputManager::isKeyPressed()
{
    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        if (buttonDown[i]) return true;
    }

    return false;
}

bool wizInputManager::wasKeyPressed()
{
    for (unsigned int i=0; i<KEY_COUNT; i++)
    {
        if (previousButtonDown[i]) return true;
    }

    return false;
}

bool wizInputManager::isKeyDown(unsigned int _key)
{
    return buttonDown[_key];
}

bool wizInputManager::isKeyPressed(unsigned int _key)
{
    return buttonPressed[_key];
}

bool wizInputManager::wasKeyDown(unsigned int _key)
{
    return previousButtonDown[_key];
}

bool wizInputManager::isTouched()
{
    return touched;
}

bool wizInputManager::isClicked()
{
    if (!touched && previousTouched)
    {
        wizInputManager::clickTime.push_back(wizGame::getTime());
        return true;
    }

    return false;
}

bool wizInputManager::isDoubleClicked()
{
    if (wizInputManager::isClicked() && wizInputManager::clickTime.size() > 1)
    {
        bool result = (wizInputManager::clickTime[1] - wizInputManager::clickTime[0]) > wizInputManager::doubleClickThreshold;
        wizInputManager::clickTime.clear();
        return result;
    }

    return false;
}

void wizInputManager::setTouchPosition(wizVector2 _position)
{
    touchPosition = _position;
}

wizVector2 wizInputManager::getTouchPosition()
{
    return touchPosition;
}

wizVector2 wizInputManager::getPreviousTouchPosition()
{
    return previousTouchPosition;
}
