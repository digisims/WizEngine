#include "wizUIComponent.h"

wizUIComponent::wizUIComponent()
{

}

wizUIComponent::wizUIComponent(wizSpriteRenderer* _renderer, bool _isScalable, std::string _sheet, std::string _sprite, std::string _defaultAnimation, std::string _touchOverAnimation, std::string _activatedAnimation, wizVector2 _position, wizVector2 _size)
{
    isScalable = _isScalable;
    sheet = _sheet;
    sprite = _sprite;
    animation = _defaultAnimation;
    defaultAnimation = _defaultAnimation;
    touchOverAnimation = _touchOverAnimation;
    activatedAnimation = _activatedAnimation;
    position = _position;
    size = _size;
    renderer = _renderer;
    parent = NULL;
    isMovable = false;
    dragging = false;
    id = 0;

    if (isScalable)
    {
        for (unsigned int i=0; i<9; i++)
        {
            wizSpriteEntity* entity = new wizSpriteEntity();
            entity->setSheet(sheet);
            entity->setSprite(sprite+"_"+wizUtility::intToString(i));
            entity->setAnimation(animation);
            entity->setFrame(0);

            entityList.push_back(entity);
        }
    }
    else
    {
        wizSpriteEntity* entity = new wizSpriteEntity();
        entity->setSheet(sheet);
        entity->setSprite(sprite);
        entity->setAnimation(animation);
        entity->setFrame(0);

        entityList.push_back(entity);
    }
}

wizUIComponent::~wizUIComponent()
{
    for (unsigned int i=0; i<children.size(); i++)
    {
        delete children[i];
    }

    for (unsigned int i=0; i<entityList.size(); i++)
    {
        delete entityList[i];
    }
}

void wizUIComponent::render()
{
    renderer->applyGlobalSettings();
    renderer->renderSpriteList(entityList);
    renderer->undoGlobalSettings();

    for (unsigned int i=0; i<children.size(); i++)
    {
        glTranslatef(position.getX(), position.getY(), 0);
        children[i]->render();
        glTranslatef(-position.getX(), -position.getY(), 0);
    }
}

bool wizUIComponent::isPointInsideRectangle(wizVector2 _point, wizVector2 _topLeft, wizVector2 _size)
{
    return !(_point.getX() < _topLeft.getX() || _point.getY() < _topLeft.getY() || _point.getX() > _topLeft.getX() + _size.getX() || _point.getY() > _topLeft.getY() + _size.getY());
}

bool wizUIComponent::update(float _dt)
{
    for (unsigned int i=0; i<children.size(); i++)
    {
        if (children[i]->update(_dt))
        {
            return true;
        }
    }

    wizVector2 point = wizInputManager::getTouchPosition();

    if (wizInputManager::isDoubleClicked() && isPointInsideRectangle(point, position, size))
    {
        animation = activatedAnimation;
        dragging = false;

        for (unsigned int i=0; i<touchDoubleClickHandlers.size(); i++)
        {
            touchDoubleClickHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
        }

        return true;
    }
    else if (wizInputManager::isClicked() && isPointInsideRectangle(point, position, size))
    {
        animation = activatedAnimation;
        dragging = false;

        for (unsigned int i=0; i<touchClickHandlers.size(); i++)
        {
            touchClickHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
        }

        return true;
    }
    else if (wizInputManager::isTouched())
    {
        wizVector2 previousPoint = wizInputManager::getPreviousTouchPosition();

        if (isPointInsideRectangle(point, position, size))
        {
            animation = touchOverAnimation;

            bool previousDragging = dragging;
            dragging = true;

            for (unsigned int i=0; i<touchDownHandlers.size(); i++)
            {
                touchDownHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
            }

            if (previousDragging && dragging)
            {
                for (unsigned int i=0; i<touchDragHandlers.size(); i++)
                {
                    touchDragHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
                }
            }

            return true;
        }
        else
        {
            animation = defaultAnimation;
        }

        if (!isPointInsideRectangle(previousPoint, position, size) && isPointInsideRectangle(point, position, size))
        {
            for (unsigned int i=0; i<touchEnterHandlers.size(); i++)
            {
                touchEnterHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
            }

            return true;
        }
        else if (isPointInsideRectangle(previousPoint, position, size) && !isPointInsideRectangle(point, position, size))
        {
            for (unsigned int i=0; i<touchLeaveHandlers.size(); i++)
            {
                touchLeaveHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
            }

            return true;
        }
    }
    else if (!wizInputManager::isTouched())
    {
        animation = defaultAnimation;
        dragging = false;

        for (unsigned int i=0; i<touchUpHandlers.size(); i++)
        {
            touchUpHandlers[i](this, new wizUITouchEvent(wizInputManager::getTouchPosition(), wizInputManager::getPreviousTouchPosition()));
        }
    }

    if (wizInputManager::isKeyPressed())
    {
        int key = wizInputManager::getKeyPressed();

        if (wizInputManager::isKeyDown(key))
        {
            for (unsigned int i=0; i<buttonDownHandlers.size(); i++)
            {
                buttonDownHandlers[i](this, new wizUIButtonEvent(key));
            }

            return true;
        }
    }
    else if (wizInputManager::wasKeyPressed())
    {
        int previousKey = wizInputManager::getKeyPressed();

        if (wizInputManager::wasKeyDown(previousKey))
        {
            for (unsigned int i=0; i<buttonPressHandlers.size(); i++)
            {
                buttonPressHandlers[i](this, new wizUIButtonEvent(previousKey));
            }
        }
        else
        {
            for (unsigned int i=0; i<buttonUpHandlers.size(); i++)
            {
                buttonUpHandlers[i](this, new wizUIButtonEvent(previousKey));
            }
        }
    }

    return false;
}

void wizUIComponent::setMovable(bool _movable)
{
    isMovable = _movable;
}

bool wizUIComponent::getMovable()
{
    return isMovable;
}

void wizUIComponent::activate()
{
    wizInputManager::setTouchPosition(position.add(size.mul(0.5f)));
    animation = touchOverAnimation;
}

void wizUIComponent::setParent(wizUIComponent* _parent)
{
    parent = _parent;
}

wizUIComponent* wizUIComponent::getParent()
{
    return parent;
}

void wizUIComponent::addComponent(wizUIComponent* _component)
{
    _component->setParent(this);
    children.push_back(_component);
}

std::vector<wizUIComponent*> wizUIComponent::getChildren()
{
    return children;
}

wizUIComponent* wizUIComponent::getNextSibling()
{
    if (parent == NULL)
    {
        return NULL;
    }
    else
    {
        std::vector<wizUIComponent*> tmpChildren = parent->getChildren();
        unsigned int size = tmpChildren.size();

        for (unsigned int i=0; i<size; i++)
        {
            if (tmpChildren[i] == this && i<size-1)
            {
                return tmpChildren[i+1];
            }
        }
    }

    return NULL;
}

wizUIComponent* wizUIComponent::getPreviousSibling()
{
    if (parent == NULL)
    {
        return NULL;
    }
    else
    {
        std::vector<wizUIComponent*> tmpChildren = parent->getChildren();
        unsigned int size = tmpChildren.size();

        for (unsigned int i=0; i<size; i++)
        {
            if (tmpChildren[i] == this && i>0)
            {
                return tmpChildren[i-1];
            }
        }
    }

    return NULL;
}

void wizUIComponent::addTouchDragEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchDragHandlers.push_back(event);
}

void wizUIComponent::addTouchDownEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchDownHandlers.push_back(event);
}

void wizUIComponent::addTouchUpEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchUpHandlers.push_back(event);
}

void wizUIComponent::addTouchClickEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchClickHandlers.push_back(event);
}

void wizUIComponent::addTouchDoubleClickEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchDoubleClickHandlers.push_back(event);
}

void wizUIComponent::addTouchEnterEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchEnterHandlers.push_back(event);
}

void wizUIComponent::addTouchLeaveEvent(void (*event)(wizUIComponent*, wizUITouchEvent*))
{
    touchLeaveHandlers.push_back(event);
}

void wizUIComponent::addButtonDownEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*))
{
    buttonDownHandlers.push_back(event);
}

void wizUIComponent::addButtonUpEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*))
{
    buttonUpHandlers.push_back(event);
}

void wizUIComponent::addButtonPressEvent(void (*event)(wizUIComponent*, wizUIButtonEvent*))
{
    buttonPressHandlers.push_back(event);
}
