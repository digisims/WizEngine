#include "wizMenuSlide.h"

wizMenuSlide::wizMenuSlide(wizRenderer* _renderer) : wizMenu(_renderer)
{
    damping = 1;
    initialAcceleration = 1;
    speed = 1;
    endTime = -1;
    toSelect = NULL;
    position = wizVector2(160, 120);
    renderer = _renderer;
    orientation = MENU_ORIENTATION_HORIZONTAL;
}

wizMenuSlide::~wizMenuSlide()
{
}

void wizMenuSlide::setOrientation(unsigned int _orientation)
{
    orientation = _orientation;
}

void wizMenuSlide::setPosition(wizVector2 _position)
{
    position = _position;
}

void wizMenuSlide::setSpeed(float _speed)
{
    speed = _speed;
}

void wizMenuSlide::setAcceleration(float _acceleration)
{
    initialAcceleration = _acceleration;
}

void wizMenuSlide::setDamping(float _damping)
{
    damping = _damping;
}

unsigned int wizMenuSlide::getOrientation()
{
    return orientation;
}

wizVector2 wizMenuSlide::getPosition()
{
    return position;
}

float wizMenuSlide::getSpeed()
{
    return speed;
}

float wizMenuSlide::getAcceleration()
{
    return initialAcceleration;
}

float wizMenuSlide::getDamping()
{
    return damping;
}

void wizMenuSlide::addItem(wizMenuItem* _item)
{
    itemList.push_back(_item);
    if (orientation == MENU_ORIENTATION_HORIZONTAL)
    {
        float x = position.getX() + (itemList.size()-1) * 320;
        coord.push_back(wizVector2(x, position.getY()));
    }
    else
    {
        float y = position.getY() + (itemList.size()-1) * 240;
        coord.push_back(wizVector2(position.getX(), y));
    }
    endCoord.push_back(coord[coord.size()-1]);

    itemList[itemList.size()-1]->setRenderer(renderer);
    itemList[itemList.size()-1]->setX(coord[coord.size()-1].getX() - _item->getWidth()/2);
    itemList[itemList.size()-1]->setY(coord[coord.size()-1].getY() - _item->getHeight()/2);

    setSelected(itemList[0]);
}

void wizMenuSlide::nextItem()
{
    if (getSelected() == itemList[itemList.size()-1])
    {
        return;
    }

    time = 0;
    acceleration = initialAcceleration;
    endTime = speed;
    toSelect = getNextItem();

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        if (orientation == MENU_ORIENTATION_HORIZONTAL)
        {
            endCoord[i].setX(endCoord[i].getX()-320);
        }
        else
        {
            endCoord[i].setY(endCoord[i].getY()-240);
        }
    }

    setSelected(NULL);
}

void wizMenuSlide::previousItem()
{
    if (getSelected() == itemList[0])
    {
        return;
    }

    time = 0;
    acceleration = initialAcceleration;
    endTime = speed;
    toSelect = getPreviousItem();

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        if (orientation == MENU_ORIENTATION_HORIZONTAL)
        {
            endCoord[i].setX(endCoord[i].getX()+320);
        }
        else
        {
            endCoord[i].setY(endCoord[i].getY()+240);
        }
    }

    setSelected(NULL);
}

bool wizMenuSlide::isAnimating()
{
    return endTime >= 0;
}

void wizMenuSlide::update(float _dt)
{
    acceleration *= damping;

    if (acceleration < 1) acceleration = 1;

    if (endTime>0)
    {
        time += speed * acceleration * _dt;

        if (time>=endTime)
        {
            time = endTime;
            endTime = -1;

            for (unsigned int i=0; i<itemList.size(); i++)
            {
                coord[i] = endCoord[i];
                itemList[i]->setX(coord[i].getX() - itemList[i]->getWidth()/2);
                itemList[i]->setY(coord[i].getY() - itemList[i]->getHeight()/2);
            }

            setSelected(toSelect);
        }
        else
        {
            float ratio = time/endTime;

            for (unsigned int i=0; i<itemList.size(); i++)
            {
                itemList[i]->setX(coord[i].getX() * (1-ratio) + endCoord[i].getX() * ratio - itemList[i]->getWidth()/2);
                itemList[i]->setY(coord[i].getY() * (1-ratio) + endCoord[i].getY() * ratio - itemList[i]->getHeight()/2);
            }
        }
    }
}
