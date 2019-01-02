#include "wizMenuItem.h"

wizMenuItem::wizMenuItem(unsigned int _id)
{
    id = _id;
}

wizMenuItem::~wizMenuItem()
{
}

void wizMenuItem::setID(unsigned int _id)
{
    id = _id;
}

void wizMenuItem::setAlpha(float _alpha)
{
    alpha = _alpha;
}

void wizMenuItem::setSelected(bool _selected)
{
    selected = _selected;
}

void wizMenuItem::setRenderer(wizRenderer* _renderer)
{
    renderer = _renderer;
}

unsigned int wizMenuItem::getID()
{
    return id;
}

float wizMenuItem::getAlpha()
{
    return alpha;
}

bool wizMenuItem::getSelected()
{
    return selected;
}
