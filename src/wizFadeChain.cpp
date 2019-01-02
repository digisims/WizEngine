#include "wizFadeChain.h"

wizFadeChain::wizFadeChain()
{
    active = -1;
}

wizFadeChain::~wizFadeChain()
{
}

void wizFadeChain::addEffect(wizFadeEffect* _effect)
{
    list.push_back(_effect);
}

bool wizFadeChain::isDone()
{
    return active == -1;
}

int wizFadeChain::getActive()
{
    return active;
}

void wizFadeChain::start()
{
    if (active == -1) active = 0;
}

void wizFadeChain::stop()
{
    active = -1;
}

void wizFadeChain::render()
{
    if (active != -1)
    {
        list[active]->render();
    }
}

void wizFadeChain::update(float _dt)
{
    if (active != -1)
    {
        list[active]->update(_dt);

        if (list[active]->isDone())
        {
            active++;
            int count = list.size();
            if (active>=count)
            {
                stop();
            }
        }
    }
}
