#ifndef WIZMENUITEM_H
#define WIZMENUITEM_H

#include "wizRenderer.h"

#include <string>

class wizMenuItem
{
    public:

    wizMenuItem(unsigned int _id);
    virtual ~wizMenuItem();

    void setID(unsigned int _id);
    void setAlpha(float _alpha);
    void setSelected(bool _selected);
    void setRenderer(wizRenderer* _renderer);
    virtual void setX(float _x) = 0;
    virtual void setY(float _y) = 0;
    virtual void setWidth(float _w) = 0;
    virtual void setHeight(float _h) = 0;
    virtual float getX() = 0;
    virtual float getY() = 0;
    virtual float getWidth() = 0;
    virtual float getHeight() = 0;
    unsigned int getID();
    float getAlpha();
    bool getSelected();

    virtual void render() = 0;
    virtual void update(float _dt) = 0;

    protected:

    bool selected;
    float alpha;
    unsigned int id;
    wizRenderer* renderer;
};

#endif // WIZMENUITEM_H
