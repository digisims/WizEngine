#ifndef WIZSCENE_H
#define WIZSCENE_H

#include "wizMesh.h"
#include "wizMeshEntity.h"
#include "wizMeshManager.h"
#include "wizMaterialManager.h"
#include "wizUtility.h"
#include "wizGame.h"
#include "wizProgress.h"

#include <string>
#include <vector>
#include <fstream>

class wizScene
{
    public:

    wizScene(std::string _filename);
    virtual ~wizScene();

    std::vector<wizMeshEntity*> getMeshEntities();

    protected:

    void load(std::string _filename);

    std::vector<wizMeshEntity*> entityList;
};

#endif // WIZSCENE_H
