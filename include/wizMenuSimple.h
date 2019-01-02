#ifndef WIZMENUSIMPLE_H

#define WIZMENUSIMPLE_H
#include "wizMenu.h"
#include "wizRenderer.h"

class wizMenuSimple : public wizMenu
{
    public:

    wizMenuSimple(wizRenderer* _renderer);
    virtual ~wizMenuSimple();

    void addItem(wizMenuItem* _item);
    void nextItem();
    void previousItem();

    protected:

};

#endif // WIZMENUSIMPLE_H
