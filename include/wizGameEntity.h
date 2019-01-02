#ifndef WIZGAMEENTITY_H
#define WIZGAMEENTITY_H

#include "wizUtility.h"

#include <string>

class wizGameEntity
{
    public:

    wizGameEntity();
    virtual ~wizGameEntity();

    void setStatic(bool _static);
    bool getStatic();

    virtual std::string getID();

    virtual void update(float _dt);

    virtual void applyTransformations();
    virtual void undoTransformations();

    virtual void render();

    protected:

    virtual void initialize();

    bool isStatic;
};

#endif // WIZGAMEENTITY_H
