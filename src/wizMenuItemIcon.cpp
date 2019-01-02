#include "wizMenuItemIcon.h"

wizMenuItemIcon::wizMenuItemIcon(unsigned int _id) : wizMenuItem(_id)
{
    sheet = "";
    sprite = "";
    baseAnimation = "";
    selectedAnimation = "";
    time = 0;
    selected = false;
    entity = NULL;
}

wizMenuItemIcon::~wizMenuItemIcon()
{
    delete entity;
}

void wizMenuItemIcon::setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame)
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

void wizMenuItemIcon::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizMenuItemIcon::setSize(wizVector2 _size)
{
    size = _size;
    entity->setSize(size);
}

void wizMenuItemIcon::setX(float _x)
{
    position.setX(_x);
}

void wizMenuItemIcon::setY(float _y)
{
    position.setY(_y);
}

void wizMenuItemIcon::setWidth(float _w)
{
    size.setX(_w);
    entity->setSize(size);
}

void wizMenuItemIcon::setHeight(float _h)
{
    size.setY(_h);
    entity->setSize(size);
}

wizVector2 wizMenuItemIcon::getPosition()
{
    return position;
}

wizVector2 wizMenuItemIcon::getSize()
{
    return size;
}

void wizMenuItemIcon::render()
{
    if (sheet.length()>0 && sprite.length()>0 && baseAnimation.length()>0 && selectedAnimation.length()>0)
    {
        renderer->applyGlobalSettings();
        entity->setAnimation(selected ? selectedAnimation : baseAnimation);
        entity->setPosition(position);
        ((wizSpriteRenderer*)renderer)->renderSpriteEntity(entity);
        renderer->undoGlobalSettings();
    }
}

void wizMenuItemIcon::update(float _dt)
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

float wizMenuItemIcon::getX()
{
    return position.getX();
}

float wizMenuItemIcon::getY()
{
    return position.getY();
}

float wizMenuItemIcon::getWidth()
{
    return size.getX();
}

float wizMenuItemIcon::getHeight()
{
    return size.getY();
}
