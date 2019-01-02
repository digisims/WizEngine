#ifndef WIZFADECHAIN_H
#define WIZFADECHAIN_H

#include "wizFadeEffect.h"

#include <vector>

class wizFadeChain
{
    public:

    wizFadeChain();
    virtual ~wizFadeChain();

    void addEffect(wizFadeEffect* _effect);

    void start();
    void stop();
    bool isDone();
    int getActive();

    void render();
    void update(float _dt);

    protected:

    int active;
    std::vector<wizFadeEffect*> list;
};

#endif // WIZFADECHAIN_H
