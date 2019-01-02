#include "wizGameEntity.h"

wizGameEntity::wizGameEntity()
{
    isStatic = false;
}

wizGameEntity::~wizGameEntity()
{
}

void wizGameEntity::setStatic(bool _static)
{
    isStatic = _static;
}

bool wizGameEntity::getStatic()
{
    return isStatic;
}

void wizGameEntity::update(float _dt)
{

}

std::string wizGameEntity::getID()
{
    return "";
}

void wizGameEntity::applyTransformations()
{

}

void wizGameEntity::undoTransformations()
{

}

void wizGameEntity::render()
{

}

void wizGameEntity::initialize()
{

}
