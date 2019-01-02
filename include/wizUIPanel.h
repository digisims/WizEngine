#ifndef WIZUIPANEL_H
#define WIZUIPANEL_H

#include "wizUIComponent.h"

#include <string>

class wizUIPanel : public wizUIComponent
{
    public:

    wizUIPanel();
    wizUIPanel(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, wizVector2 _position, wizVector2 _size);
    virtual ~wizUIPanel();

    protected:
};

#endif // WIZUIPANEL_H
