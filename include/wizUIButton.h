#ifndef WIZUIBUTTON_H
#define WIZUIBUTTON_H

#include "wizUIComponent.h"
#include "wizFontManager.h"
#include "wizFont.h"

#include <string>

class wizUIButton : public wizUIComponent
{
    public:

    wizUIButton();
    wizUIButton(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, std::string _font, std::string _text, wizVector2 _position, wizVector2 _size);
    wizUIButton(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, std::string _font, short _fontSize, std::string _text, wizVector2 _position, wizVector2 _size);
    virtual ~wizUIButton();

    virtual void render();

    protected:

    std::string font;
    std::string text;
    short fontSize;
};

#endif // WIZUIBUTTON_H
