#ifndef WIZUISLIDER_H
#define WIZUISLIDER_H

#include "wizUIComponent.h"

class wizUISlider : wizUIComponent
{
    public:

    wizUISlider();
    wizUISlider(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, int _minimum, int _maximum, int _value, wizVector2 _position, wizVector2 _size);
    virtual ~wizUISlider();

    void setValue(int _value);
    void setMinimum(int _minimum);
    void setMaximum(int _maximum);
    int getValue();
    int getMinimum();
    int getMaximum();

    virtual void render();

    protected:

    int minimum;
    int maximum;
    int value;
};

#endif // WIZUISLIDER_H
