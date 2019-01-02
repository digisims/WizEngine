#ifndef WIZMESHMANAGER_H
#define WIZMESHMANAGER_H

#include "wizMesh.h"

#include <map>

class wizMeshManager
{
    public:

    static void initialize();
    static void destroy();

    static void addMesh(std::string _id, wizMesh* _mesh);
    static wizMesh* getMesh(std::string _id);
    static void removeMesh(std::string _id);

    protected:

    static std::map<std::string, wizMesh*> meshMap;
};

#endif // WIZMESHMANAGER_H
