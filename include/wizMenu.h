#ifndef WIZMENU_H
#define WIZMENU_H

#include "wizRenderer.h"
#include "wizMenuItem.h"

#include <vector>

class wizMenu
{
    public:

    wizMenu(wizRenderer* _renderer);
    virtual ~wizMenu();

    void setRenderer(wizRenderer* _renderer);
    wizRenderer* getRenderer();

    virtual void addItem(wizMenuItem* _item);
    void setSelected(wizMenuItem* _item);
    wizMenuItem* getSelected();
    wizMenuItem* getNextItem();
    wizMenuItem* getPreviousItem();
    virtual void nextItem() = 0;
    virtual void previousItem() = 0;
    bool hasNext();
    bool hasPrevious();

    virtual void render();
    virtual void update(float _dt);
    virtual bool isAnimating() = 0;

    protected:

    virtual void selectNextItem();
    virtual void selectPreviousItem();

    wizRenderer* renderer;
    std::vector<wizMenuItem*> itemList;
};

#endif // WIZMENU_H
