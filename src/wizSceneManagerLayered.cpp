#include "wizSceneManagerLayered.h"

wizSceneManagerLayered::wizSceneManagerLayered()
{
}

wizSceneManagerLayered::~wizSceneManagerLayered()
{
}

void wizSceneManagerLayered::addEntity(wizGameEntity* _entity)
{
    if (layerList.size()>0)
    {
        layerList[0].push_back(_entity);
    }
}

void wizSceneManagerLayered::removeEntity(unsigned int _idx)
{
    if (layerList.size()>0)
    {
        layerList[0].erase(layerList[0].begin()+_idx);
    }
}

void wizSceneManagerLayered::clear()
{
    layerList.clear();
}

void wizSceneManagerLayered::addEntity(unsigned int _layer, wizGameEntity* _entity)
{
    while (_layer < layerList.size())
    {
        layerList.push_back(std::vector<wizGameEntity*>());
    }

    layerList[_layer].push_back(_entity);
}

void wizSceneManagerLayered::removeEntity(unsigned int _layer, unsigned int _idx)
{
    if (_layer < layerList.size())
    {
        layerList[_layer].erase(layerList[_layer].begin()+_idx);
    }
}

void wizSceneManagerLayered::clear(unsigned int _layer)
{
    if (_layer < layerList.size())
    {
        layerList[_layer].clear();
    }
}

void wizSceneManagerLayered::construct()
{

}

std::vector<wizGameEntity*> wizSceneManagerLayered::queryAll()
{
    std::vector<wizGameEntity*> visible;

    for (unsigned int i=0; i<layerList.size(); i++)
    {
        visible = mergeLists(visible, layerList[i]);
    }

    return visible;
}

std::vector<wizGameEntity*> wizSceneManagerLayered::queryVisible(wizCamera* _camera)
{
    std::vector<wizGameEntity*> visible;

    for (unsigned int i=0; i<layerList.size(); i++)
    {
        for (unsigned int j=0; j<layerList[i].size(); j++)
        {
            wizSpriteEntity* entity = (wizSpriteEntity*)layerList[i][j];

            if (_camera->isBoxInside(entity->getPosition(), entity->getSize()))
            {
                visible.push_back(entity);
            }
        }
    }

    return visible;
}

std::vector<wizGameEntity*> wizSceneManagerLayered::queryVisibleStatic(wizCamera* _camera)
{
    std::vector<wizGameEntity*> visible;

    for (unsigned int i=0; i<layerList.size(); i++)
    {
        for (unsigned int j=0; j<layerList[i].size(); j++)
        {
            wizSpriteEntity* entity = (wizSpriteEntity*)layerList[i][j];

            if (entity->getStatic() && _camera->isBoxInside(entity->getPosition(), entity->getSize()))
            {
                visible.push_back(entity);
            }
        }
    }

    return visible;
}

std::vector<wizGameEntity*> wizSceneManagerLayered::queryVisibleDynamic(wizCamera* _camera)
{
    std::vector<wizGameEntity*> visible;

    for (unsigned int i=0; i<layerList.size(); i++)
    {
        for (unsigned int j=0; j<layerList[i].size(); j++)
        {
            wizSpriteEntity* entity = (wizSpriteEntity*)layerList[i][j];

            if (!entity->getStatic() && _camera->isBoxInside(entity->getPosition(), entity->getSize()))
            {
                visible.push_back(entity);
            }
        }
    }

    return visible;
}
