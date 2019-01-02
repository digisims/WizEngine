#include "wizUICheckBox.h"

wizUICheckBox::wizUICheckBox()
{
}

wizUICheckBox::wizUICheckBox(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _activatedAnimation, std::string _checkedAnimation, std::string _font, std::string _text, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _defaultAnimation, _activatedAnimation, _position, _size)
{
    checked = false;
    checkedAnimation = _checkedAnimation;
    font = _font;
    fontSize = -1;
    text = _text;
}

wizUICheckBox::wizUICheckBox(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _activatedAnimation, std::string _checkedAnimation, std::string _font, short _fontSize, std::string _text, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _defaultAnimation, _activatedAnimation, _position, _size)
{
    checked = false;
    checkedAnimation = _checkedAnimation;
    font = _font;
    fontSize = _fontSize;
    text = _text;
}

wizUICheckBox::~wizUICheckBox()
{
}

void wizUICheckBox::render()
{
    if (checked && animation.compare(activatedAnimation)!=0)
    {
        animation = checkedAnimation;
    }

    renderer->applyGlobalSettings();
    renderer->renderSpriteList(entityList);
    renderer->undoGlobalSettings();

    wizFont* fontObject = wizFontManager::getFont(font);

    if (fontSize>0)
    {
        wizVector2 fontDims = fontObject->measureScaledText(text, fontSize, fontSize);
        fontObject->renderScaledText(text, position.getX() + size.getX() + 5, position.getY()+size.getY()/2-fontDims.getY()/2, (float)fontSize, (float)fontSize);
    }
    else
    {
        wizVector2 fontDims = fontObject->measureText(text);
        fontObject->renderText(text, position.getX() + size.getX() + 5, position.getY()+size.getY()/2-fontDims.getY()/2);
    }

    for (unsigned int i=0; i<children.size(); i++)
    {
        glTranslatef(position.getX(), position.getY(), 0);
        children[i]->render();
        glTranslatef(-position.getX(), -position.getY(), 0);
    }
}

void wizUICheckBox::setChecked(bool _checked)
{
    checked = _checked;
}

bool wizUICheckBox::getChecked()
{
    return checked;
}
