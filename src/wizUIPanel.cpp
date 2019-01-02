#include "wizUIPanel.h"

wizUIPanel::wizUIPanel()
{
}

wizUIPanel::wizUIPanel(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, wizVector2 _position, wizVector2 _size) : wizUIComponent(_renderer, _isScalable, _sheet, _sprite, _defaultAnimation, _defaultAnimation, _defaultAnimation, _position, _size)
{
}

wizUIPanel::~wizUIPanel()
{
}
