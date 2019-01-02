#include "wizInput.h"

wizVector2 wizInput::touchPosition;

void wizInput::initialize()
{
    g_cInput.Initialize();
}

void wizInput::destroy()
{
}

void wizInput::update()
{
    g_cInput.ScanInputDevice();
}

bool wizInput::isKeyDown(int _key)
{
    return g_cInput.IsPushKey(_key);
}

bool wizInput::isKeyPressed(int _key)
{
    return g_cInput.IsPushKeyOnce(_key);
}

bool wizInput::isScreenTouched()
{
    return g_cInput.IsTouch();
}

wizVector2 wizInput::getTouchPosition()
{
    touchPosition.setX(g_cInput.GetTouchX());
    touchPosition.setY(g_cInput.GetTouchY());
    return touchPosition;
}
