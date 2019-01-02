#ifndef WIZBLOBSHADOWRENDERER_H
#define WIZBLOBSHADOWRENDERER_H

#include "wizBlob.h"
#include "wizVector3.h"
#include "wizGameEntity.h"
#include "wizMeshEntity.h"
#include "wizTriangle.h"
#include "wizTextureManager.h"
#include "wizMaterialManager.h"

#include <vector>

class wizBlobShadowRenderer
{
    public:

    wizBlobShadowRenderer();
    virtual ~wizBlobShadowRenderer();

    void applyGlobalSettings();
    void undoGlobalSettings();

    void renderBlob(wizVector3 _position, wizBlob* _blob, wizGameEntity* _entity, std::vector<wizGameEntity*>& _list);
    void renderBlob(wizVector3 _position, wizBlob* _blob, wizGameEntity* _entity, std::vector<wizGameEntity*>& _list, std::vector<std::string> _skip);

    protected:

    GLushort* indexBuffer;
    GLfloat* textureBuffer;
    GLfloat* vertexBuffer;
};

#endif // WIZBLOBSHADOWRENDERER_H
