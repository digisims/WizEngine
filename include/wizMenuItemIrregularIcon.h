#ifndef WIZMENUITEMIRREGULARICON_H
#define WIZMENUITEMIRREGULARICON_H


#include "wizFont.h"
#include "wizVector2.h"
#include "wizMenuItem.h"
#include "wizScalableHUD.h"
#include "wizFont.h"
#include "wizFontManager.h"
#include "wizSpritesheetManager.h"
#include "wizSpriteEntity.h"

#include <string>

class wizMenuItemIrregularIcon : public wizMenuItem
{
    public:

    wizMenuItemIrregularIcon(unsigned int _id);
    virtual ~wizMenuItemIrregularIcon();

    void setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame);
    void setPoints(wizVector2* _position);
    void setSize(wizVector2 _size);
    void setX(float _x);
    void setY(float _y);
    void setWidth(float _w);
    void setHeight(float _h);
    wizVector2* getPoints();
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
    wizVector2* points;
    wizVector2 size;
    wizSpriteEntity* entity;
};


#endif // WIZMENUITEMIRREGULARICON_H
