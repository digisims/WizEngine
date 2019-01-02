#include "wizMaterialManager.h"

std::map<std::string, wizMaterial*> wizMaterialManager::materialMap;

void wizMaterialManager::initialize()
{
}

void wizMaterialManager::destroy()
{
    std::map<std::string, wizMaterial*>::iterator i;

    for (i=materialMap.begin(); i!=materialMap.end(); i++)
    {
        delete i->second;
    }
}

void wizMaterialManager::addMaterial(std::string _id, wizMaterial* _material)
{
    if (getMaterial(_id)==NULL)
    {
        materialMap[_id] = _material;
    }
}

wizMaterial* wizMaterialManager::getMaterial(std::string _id)
{
    if (materialMap.find(_id)!=materialMap.end())
    {
        return materialMap[_id];
    }

    return NULL;
}

void wizMaterialManager::removeMaterial(std::string _id)
{
    if (getMaterial(_id)!=NULL)
    {
        materialMap.erase(materialMap.find(_id));
    }
}
