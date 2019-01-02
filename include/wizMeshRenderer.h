#ifndef WIZMESHRENDERER_H
#define WIZMESHRENDERER_H

#include "wizRenderer.h"
#include "wizGameEntity.h"
#include "wizMeshEntity.h"
#include "wizMaterial.h"
#include "wizMaterialStage.h"
#include "wizMaterialManager.h"
#include "wizTextureManager.h"
#include "wizLightManager.h"
#include "wizCamera3D.h"
#include "wizRay.h"
#include "wizBoundingBox.h"

#include <vector>
#include <algorithm>

class wizMeshRenderer : public wizRenderer
{
    public:

    wizMeshRenderer();
    wizMeshRenderer(unsigned int _cache);
    ~wizMeshRenderer();

    void applyGlobalSettings();
    void undoGlobalSettings();

    std::vector<wizGameEntity*> findOccludingMeshList(std::vector<wizGameEntity*>& _list, wizGameEntity* _entity, wizCamera3D* _camera, unsigned int _threshold);
    std::vector<wizGameEntity*> findOccludingMeshList(std::vector<wizGameEntity*>& _list, wizGameEntity* _entity, wizCamera3D* _camera, unsigned int _threshold, std::vector<wizGameEntity*> _cache);

    void renderMeshEntity(wizMeshEntity* _entity);
    void renderMeshListCommon(std::vector<wizGameEntity*>& _list);
    void renderMeshListUnique(std::vector<wizGameEntity*>& _list);

    unsigned int getBatches();
    unsigned int getVertices();
    unsigned int getTriangles();
    bool getCached();

    void lock();
    void unlock();

    protected:

    void disposeBatches();
    void disposeVBOs();

    void resetBatch(std::string _material);
    void batchMesh(wizMeshEntity* _entity);
    void compileBatch(std::string _material);

    unsigned int cache;
    std::vector<unsigned int> order;
    unsigned int batches;
    std::map<std::string, GLfloat*> batchVertex;
    std::map<std::string, GLubyte*> batchColour;
    std::map<std::string, GLfloat**> batchTexture;
    std::map<std::string, GLushort*> batchIndex;
    std::map<std::string, unsigned int> batchVertices;
    std::map<std::string, unsigned int> batchIndices;
    std::map<std::string, GLuint> vboIndex;
    std::map<std::string, GLuint> vboVertex;
    std::map<std::string, GLuint> vboColour;
    std::map<std::string, GLuint*> vboTexture;
    std::map<std::string, bool> vboCompiled;
    std::vector<wizMeshEntity*> lastList;
    std::vector<wizGameEntity*> lastListAlt;
    unsigned int renderedVertices;
    unsigned int renderedTriangles;
    bool cached;
    bool locked;

    std::map<std::string, std::vector<wizMeshEntity*> > batch;
    std::map<std::string, std::map<std::string, std::vector<wizMeshEntity*> > > batch2;

    std::vector<std::string> materialList;
};

#endif // WIZMESHRENDERER_H
