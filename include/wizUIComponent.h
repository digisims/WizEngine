#ifndef WIZUICOMPONENT_H
#define WIZUICOMPONENT_H

#include "wizVector2.h"
#include "wizInputManager.h"
#include "wizSpriteSheetManager.h"
#include "wizSpriteRenderer.h"
#include "wizUITouchEvent.h"
#include "wizUIButtonEvent.h"

#include <string>
#include <vector>

class wizUIComponent
{
    public:

    wizUIComponent();
    wizUIComponent(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, wizVector2 _position, wizVector2 _size);
    virtual ~wizUIComponent();

    void setParent(wizUIComponent* _parent);
    wizUIComponent* getParent();

    void addComponent(wizUIComponent* _component);
    std::vector<wizUIComponent*> getChildren();
    wizUIComponent* getNextSibling();
    wizUIComponent* getPreviousSibling();

    void addTouchDragEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchDownEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchUpEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchClickEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchDoubleClickEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchEnterEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addTouchLeaveEvent(void (*event)(wizUIComponent*, wizUITouchEvent*));
    void addButtonDownEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*));
    void addButtonUpEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*));
    void addButtonPressEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*));

    virtual void render();
    virtual bool update(float _dt);

    void setMovable(bool _movable);
    bool getMovable();

    void activate();

    protected:

    static bool isPointInsideRectangle(wizVector2 _point, wizVector2 _topLeft, wizVector2 _size);

    unsigned int id;
    bool dragging;
    bool isScalable;
    bool isMovable;
    std::string sheet;
    std::string sprite;
    std::string animation;
    std::string defaultAnimation;
    std::string touchOverAnimation;
    std::string activatedAnimation;
    wizVector2 position;
    wizVector2 size;
    wizSpriteRenderer* renderer;
    wizUIComponent* parent;
    std::vector<wizUIComponent*> children;
    std::vector<wizSpriteEntity*> entityList;

    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchDragHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchDownHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchUpHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchClickHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchDoubleClickHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchEnterHandlers;
    std::vector<void (*)(wizUIComponent*, wizUITouchEvent*)> touchLeaveHandlers;
    std::vector<void (*)(wizUIComponent*, wizUIButtonEvent*)> buttonDownHandlers;
    std::vector<void (*)(wizUIComponent*, wizUIButtonEvent*)> buttonUpHandlers;
    std::vector<void (*)(wizUIComponent*, wizUIButtonEvent*)> buttonPressHandlers;
};

#endif // WIZUICOMPONENT_H
