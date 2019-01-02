#ifndef WIZMATERIALMANAGER_H
#define WIZMATERIALMANAGER_H

#include "wizMaterial.h"

class wizMaterialManager
{
    public:

    static void initialize();
    static void destroy();

    static void addMaterial(std::string _id, wizMaterial* _material);
    static wizMaterial* getMaterial(std::string _id);
    static void removeMaterial(std::string _id);

    protected:

    static std::map<std::string, wizMaterial*> materialMap;
};

#endif // WIZMATERIALMANAGER_H
