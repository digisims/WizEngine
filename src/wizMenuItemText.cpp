#include "wizMenuItemText.h"

wizMenuItemText::wizMenuItemText(unsigned int _id) : wizMenuItem(_id)
{
    scale = wizVector2(-1, -1);
    sheet = "";
    sprite = "";
    baseAnimation = "";
    selectedAnimation = "";
    time = 0;
    selected = false;
    entity = NULL;
}

wizMenuItemText::~wizMenuItemText()
{
    delete entity;
}

void wizMenuItemText::setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame)
{
    sheet = _sheet;
    sprite = _sprite;
    baseAnimation = _baseAnimation;
    selectedAnimation = _selectedAnimation;
    frame = _frame;

    entity = new wizSpriteEntity();
    entity->setSheet(sheet);
    entity->setSprite(sprite);
    entity->setAnimation(baseAnimation);
    entity->setFrame(frame);
}

void wizMenuItemText::setFont(std::string _font)
{
    font = _font;
}

void wizMenuItemText::setText(std::string _text)
{
    text = _text;
}

void wizMenuItemText::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizMenuItemText::setSize(wizVector2 _size)
{
    size = _size;
    entity->setSize(size);
}

void wizMenuItemText::setScale(wizVector2 _scale)
{
    scale = _scale;
}

void wizMenuItemText::setX(float _x)
{
    position.setX(_x);
}

void wizMenuItemText::setY(float _y)
{
    position.setY(_y);
}

void wizMenuItemText::setWidth(float _w)
{
    size.setX(_w);
    entity->setSize(size);
}

void wizMenuItemText::setHeight(float _h)
{
    size.setY(_h);
    entity->setSize(size);
}

std::string wizMenuItemText::getFont()
{
    return font;
}

std::string wizMenuItemText::getText()
{
    return text;
}

wizVector2 wizMenuItemText::getPosition()
{
    return position;
}

wizVector2 wizMenuItemText::getSize()
{
    return size;
}

wizVector2 wizMenuItemText::getScale()
{
    return scale;
}

void wizMenuItemText::render()
{
    if (sheet.length()>0 && sprite.length()>0 && baseAnimation.length()>0 && selectedAnimation.length()>0)
    {
        renderer->applyGlobalSettings();
        entity->setAnimation(selected ? selectedAnimation : baseAnimation);
        entity->setPosition(position);
        ((wizSpriteRenderer*)renderer)->renderSpriteEntity(entity);
        renderer->undoGlobalSettings();
    }
    wizFont* fontObject = wizFontManager::getFont(font);
    fontObject->applySettings();
    if (scale.getX()>-1 && scale.getY()>-1)
    {
        wizVector2 dim = fontObject->measureScaledText(text, scale.getX(), scale.getY());
        fontObject->renderScaledText(text, position.getX()+size.getX()/2-dim.getX()/2, position.getY()+size.getY()/2-dim.getY()/2, scale.getX(), scale.getY());
    }
    else
    {
        wizVector2 dim = fontObject->measureText(text);
        fontObject->renderText(text, position.getX()+size.getX()/2-dim.getX()/2, position.getY()+size.getY()/2-dim.getY()/2);
    }
    fontObject->undoSettings();
}

void wizMenuItemText::update(float _dt)
{
    time += _dt;

    wizSpriteAnimation* animationObject = wizSpriteSheetManager::getSpriteSheet(sheet)->getSprite(sprite)->getAnimation(selected ? selectedAnimation : baseAnimation);
    wizSpriteFrame* frameObject = wizSpriteSheetManager::getSpriteSheet(sheet)->getSprite(sprite)->getAnimation(selected ? selectedAnimation : baseAnimation)->getFrame(frame);

    float nextTime = frameObject->getTime();

    if (time >= nextTime)
    {
        time -= nextTime;
        frame++;

        if (frame >= (unsigned int)animationObject->getFrameCount() && animationObject->getLoopable())
        {
            frame = 0;
        }
    }
}

float wizMenuItemText::getX()
{
    return position.getX();
}

float wizMenuItemText::getY()
{
    return position.getY();
}

float wizMenuItemText::getWidth()
{
    return size.getX();
}

float wizMenuItemText::getHeight()
{
    return size.getY();
}
