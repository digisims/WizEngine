#include "wizUIButton.h"

wizUIButton::wizUIButton()
{
}

wizUIButton::wizUIButton(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, std::string _font, std::string _text, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _touchOverAnimation, _activatedAnimation, _position, _size)
{
    font = _font;
    fontSize = -1;
    text = _text;
}

wizUIButton::wizUIButton(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, std::string _font, short _fontSize, std::string _text, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _touchOverAnimation, _activatedAnimation, _position, _size)
{
    font = _font;
    fontSize = _fontSize;
    text = _text;
}

wizUIButton::~wizUIButton()
{
}

void wizUIButton::render()
{
    renderer->applyGlobalSettings();
    renderer->renderSpriteList(entityList);
    renderer->undoGlobalSettings();

    wizFont* fontObject = wizFontManager::getFont(font);

    if (fontSize>0)
    {
        wizVector2 fontDims = fontObject->measureScaledText(text, fontSize, fontSize);
        fontObject->renderScaledText(text, position.getX() + size.getX()/2 - fontDims.getX() / 2, position.getY()+size.getY()/2-fontDims.getY()/2, (float)fontSize, (float)fontSize);
    }
    else
    {
        wizVector2 fontDims = fontObject->measureText(text);
        fontObject->renderText(text, position.getX() + size.getX()/2 - fontDims.getX() / 2, position.getY()+size.getY()/2-fontDims.getY()/2);
    }

    for (unsigned int i=0; i<children.size(); i++)
    {
        glTranslatef(position.getX(), position.getY(), 0);
        children[i]->render();
        glTranslatef(-position.getX(), -position.getY(), 0);
    }
}
