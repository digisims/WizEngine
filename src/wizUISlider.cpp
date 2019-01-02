#include "wizUISlider.h"

wizUISlider::wizUISlider()
{
}

wizUISlider::wizUISlider(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, int _minimum, int _maximum, int _value, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _touchOverAnimation, _activatedAnimation, _position, _size)
{
    minimum = _minimum;
    maximum = _maximum;
    value = _value;
}

wizUISlider::~wizUISlider()
{
}

void wizUISlider::setValue(int _value)
{
    value = _value;
}

void wizUISlider::setMinimum(int _minimum)
{
    minimum = _minimum;
}

void wizUISlider::setMaximum(int _maximum)
{
    maximum = _maximum;
}

int wizUISlider::getValue()
{
    return value;
}

int wizUISlider::getMinimum()
{
    return minimum;
}

int wizUISlider::getMaximum()
{
    return maximum;
}

void wizUISlider::render()
{
    renderer->applyGlobalSettings();
    renderer->renderSpriteList(entityList);
    renderer->undoGlobalSettings();

    for (unsigned int i=0; i<children.size(); i++)
    {
        glTranslatef(position.getX(), position.getY(), 0);
        children[i]->render();
        glTranslatef(-position.getX(), -position.getY(), 0);
    }
}
