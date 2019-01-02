#include "wizMeshManager.h"

std::map<std::string, wizMesh*> wizMeshManager::meshMap;

void wizMeshManager::initialize()
{
}

void wizMeshManager::destroy()
{
    std::map<std::string, wizMesh*>::iterator i;

    for (i=meshMap.begin(); i!=meshMap.end(); i++)
    {
        delete i->second;
    }
}

void wizMeshManager::addMesh(std::string _id, wizMesh* _mesh)
{
    if (getMesh(_id)==NULL)
    {
        meshMap[_id] = _mesh;
    }
}

wizMesh* wizMeshManager::getMesh(std::string _id)
{
    if (meshMap.find(_id)!=meshMap.end())
    {
        return meshMap[_id];
    }

    return NULL;
}

void wizMeshManager::removeMesh(std::string _id)
{
    if (getMesh(_id)!=NULL)
    {
        meshMap.erase(meshMap.find(_id));
    }
}
