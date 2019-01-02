#include "wizMenuSimple.h"

wizMenuSimple::wizMenuSimple(wizRenderer* _renderer) : wizMenu(_renderer)
{
}

wizMenuSimple::~wizMenuSimple()
{
}

void wizMenuSimple::addItem(wizMenuItem* _item)
{
    itemList.push_back(_item);

    float totalHeight = 0;

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        totalHeight += itemList[i]->getHeight();
    }

    totalHeight += (itemList.size()-1) * 10;

    float sy = 120 - totalHeight / 2;

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        itemList[i]->setX(160-itemList[i]->getWidth());
        itemList[i]->setY(sy);

        sy += itemList[i]->getHeight() + 10;
    }

    setSelected(itemList[0]);
}

void wizMenuSimple::nextItem()
{
    selectNextItem();
}

void wizMenuSimple::previousItem()
{
    selectPreviousItem();
}
