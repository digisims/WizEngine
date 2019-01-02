#ifndef WIZMENUITEMICON_H
#define WIZMENUITEMICON_H

#include "wizFont.h"
#include "wizVector2.h"
#include "wizMenuItem.h"
#include "wizScalableHUD.h"
#include "wizFont.h"
#include "wizFontManager.h"
#include "wizSpritesheetManager.h"
#include "wizSpriteEntity.h"

#include <string>

class wizMenuItemIcon : public wizMenuItem
{
    public:

    wizMenuItemIcon(unsigned int _id);
    virtual ~wizMenuItemIcon();

    void setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame);
    void setPosition(wizVector2 _position);
    void setSize(wizVector2 _size);
    void setX(float _x);
    void setY(float _y);
    void setWidth(float _w);
    void setHeight(float _h);
    wizVector2 getPosition();
    wizVector2 getSize();
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    void render();
    void update(float _dt);

    protected:

    std::string sheet;
    std::string sprite;
    std::string baseAnimation;
    std::string selectedAnimation;
    float time;
    unsigned int frame;
    wizVector2 position;
    wizVector2 size;
    wizSpriteEntity* entity;
};

#endif // WIZMENUITEMICON_H
