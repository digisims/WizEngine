#ifndef WIZUICHECKBOX_H
#define WIZUICHECKBOX_H

#include "wizUIComponent.h"
#include "wizFontManager.h"
#include "wizFont.h"

#include <string>

class wizUICheckBox : public wizUIComponent
{
    public:

    wizUICheckBox();
    wizUICheckBox(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _activatedAnimation, std::string _checkedAnimation, std::string _font, std::string _text, wizVector2 _position, wizVector2 _size);
    wizUICheckBox(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _activatedAnimation, std::string _checkedAnimation, std::string _font, short _fontSize, std::string _text, wizVector2 _position, wizVector2 _size);
    virtual ~wizUICheckBox();

    virtual void render();

    void setChecked(bool _checked);
    bool getChecked();

    protected:

    bool checked;
    std::string checkedAnimation;
    std::string font;
    std::string text;
    short fontSize;
};

#endif // WIZUICHECKBOX_H
