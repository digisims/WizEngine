#include "wizUIButtonEvent.h"

wizUIButtonEvent::wizUIButtonEvent()
{
    button = -1;
}

wizUIButtonEvent::wizUIButtonEvent(unsigned int _button)
{
    button = _button;
}

wizUIButtonEvent::~wizUIButtonEvent()
{
}

int wizUIButtonEvent::getButton()
{
    return button;
}
