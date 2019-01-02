#include "wizMenuItemIrregularIcon.h"

wizMenuItemIrregularIcon::wizMenuItemIrregularIcon(unsigned int _id) : wizMenuItem(_id)
{
    sheet = "";
    sprite = "";
    baseAnimation = "";
    selectedAnimation = "";
    time = 0;
    selected = false;
    entity = NULL;
}

wizMenuItemIrregularIcon::~wizMenuItemIrregularIcon()
{
    delete entity;
}

void wizMenuItemIrregularIcon::setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame)
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

void wizMenuItemIrregularIcon::setPoints(wizVector2* _points)
{
    points = _points;
}

void wizMenuItemIrregularIcon::setSize(wizVector2 _size)
{
    size = _size;
}

void wizMenuItemIrregularIcon::setX(float _x)
{
    float dx = _x - points[0].getX();

    for (unsigned int i=0; i<4; i++)
    {
        points[i].setX(points[i].getX() + dx);
    }
}

void wizMenuItemIrregularIcon::setY(float _y)
{
    float dy = _y - points[0].getY();

    for (unsigned int i=0; i<4; i++)
    {
        points[i].setY(points[i].getY() + dy);
    }
}

void wizMenuItemIrregularIcon::setWidth(float _w)
{
    size.setX(_w);
}

void wizMenuItemIrregularIcon::setHeight(float _h)
{
    size.setY(_h);
}

wizVector2* wizMenuItemIrregularIcon::getPoints()
{
    return points;
}

wizVector2 wizMenuItemIrregularIcon::getSize()
{
    return size;
}

void wizMenuItemIrregularIcon::render()
{
    if (sheet.length()>0 && sprite.length()>0 && baseAnimation.length()>0 && selectedAnimation.length()>0)
    {
        renderer->applyGlobalSettings();
        entity->setAnimation(selected ? selectedAnimation : baseAnimation);
        entity->extract();
        entity->getVertexBuffer()[0] = (short)points[0].getX();
        entity->getVertexBuffer()[1] = (short)points[0].getY();
        entity->getVertexBuffer()[2] = (short)points[1].getX();
        entity->getVertexBuffer()[3] = (short)points[1].getY();
        entity->getVertexBuffer()[4] = (short)points[2].getX();
        entity->getVertexBuffer()[5] = (short)points[2].getY();
        entity->getVertexBuffer()[6] = (short)points[2].getX();
        entity->getVertexBuffer()[7] = (short)points[2].getY();
        entity->getVertexBuffer()[8] = (short)points[3].getX();
        entity->getVertexBuffer()[9] = (short)points[3].getY();
        entity->getVertexBuffer()[10] = (short)points[0].getX();
        entity->getVertexBuffer()[11] = (short)points[0].getY();
        ((wizSpriteRenderer*)renderer)->renderSpriteEntity(entity);
        renderer->undoGlobalSettings();
    }
}

void wizMenuItemIrregularIcon::update(float _dt)
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

float wizMenuItemIrregularIcon::getX()
{
    return points[0].getX();
}

float wizMenuItemIrregularIcon::getY()
{
    return points[0].getY();
}

float wizMenuItemIrregularIcon::getWidth()
{
    return size.getX();
}

float wizMenuItemIrregularIcon::getHeight()
{
    return size.getY();
}
