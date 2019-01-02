#ifndef WIZMENUITEMTEXT_H
#define WIZMENUITEMTEXT_H

#include "wizFont.h"
#include "wizVector2.h"
#include "wizMenuItem.h"
#include "wizScalableHUD.h"
#include "wizFont.h"
#include "wizFontManager.h"
#include "wizSpritesheetManager.h"
#include "wizSpriteEntity.h"

#include <string>

class wizMenuItemText : public wizMenuItem
{
    public:

    wizMenuItemText(unsigned int _id);
    virtual ~wizMenuItemText();

    void setSprite(std::string _sheet, std::string _sprite, std::string _baseAnimation, std::string _selectedAnimation, unsigned int _frame);
    void setFont(std::string _font);
    void setText(std::string _text);
    void setPosition(wizVector2 _position);
    void setSize(wizVector2 _size);
    void setScale(wizVector2 _scale);
    void setX(float _x);
    void setY(float _y);
    void setWidth(float _w);
    void setHeight(float _h);
    std::string getFont();
    std::string getText();
    wizVector2 getPosition();
    wizVector2 getSize();
    wizVector2 getScale();
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
    std::string font;
    std::string text;
    wizVector2 position;
    wizVector2 size;
    wizVector2 scale;
    wizSpriteEntity* entity;
};

#endif // WIZMENUITEMTEXT_H

