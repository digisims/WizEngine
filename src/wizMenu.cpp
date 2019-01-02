#include "wizMenu.h"

wizMenu::wizMenu(wizRenderer* _renderer)
{
    renderer = _renderer;
}

wizMenu::~wizMenu()
{
}

void wizMenu::setRenderer(wizRenderer* _renderer)
{
    renderer = _renderer;
}

wizRenderer* wizMenu::getRenderer()
{
    return renderer;
}

void wizMenu::addItem(wizMenuItem* _item)
{
    _item->setRenderer(renderer);
    itemList.push_back(_item);
}

wizMenuItem* wizMenu::getSelected()
{
    for (unsigned int i=0; i<itemList.size(); i++)
    {
        if (itemList[i]->getSelected())
        {
            return itemList[i];
        }
    }

    return NULL;
}

void wizMenu::render()
{
    for (unsigned int i=0; i<itemList.size(); i++)
    {
        itemList[i]->render();
    }
}

void wizMenu::update(float _dt)
{
    for (unsigned int i=0; i<itemList.size(); i++)
    {
        itemList[i]->update(_dt);
    }
}

void wizMenu::setSelected(wizMenuItem* _item)
{
    for (unsigned int i=0; i<itemList.size(); i++)
    {
        itemList[i]->setSelected(false);
    }

    if (_item!=NULL)
    {
        _item->setSelected(true);
    }
}

wizMenuItem* wizMenu::getPreviousItem()
{
    wizMenuItem* selected = getSelected();
    unsigned int idx = 0;

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        if (itemList[i] == selected)
        {
            if (i>0)
            {
                idx = i-1;
            }
            else
            {
                idx = itemList.size()-1;
            }
        }
    }

    return itemList[idx];
}

wizMenuItem* wizMenu::getNextItem()
{
    wizMenuItem* selected = getSelected();
    unsigned int idx = 0;

    for (unsigned int i=0; i<itemList.size(); i++)
    {
        if (itemList[i] == selected)
        {
            if (i<itemList.size()-1)
            {
                idx = i+1;
            }
            else
            {
                idx = 0;
            }
        }
    }

    return itemList[idx];
}

void wizMenu::selectNextItem()
{
    setSelected(getNextItem());
}

void wizMenu::selectPreviousItem()
{
    setSelected(getPreviousItem());
}

bool wizMenu::hasNext()
{
    return getSelected()!=NULL && getSelected()!=itemList[itemList.size()-1];
}

bool wizMenu::hasPrevious()
{
    return getSelected()!=NULL && getSelected()!=itemList[0];
}
