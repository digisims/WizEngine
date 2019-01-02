#include "wizBlobShadowRenderer.h"

wizBlobShadowRenderer::wizBlobShadowRenderer()
{
    vertexBuffer = new GLfloat[3 * 4];
    textureBuffer = new GLfloat[2 * 4];
    indexBuffer = new GLushort[3 * 2];

    vertexBuffer[0] = -1;
    vertexBuffer[1] = 0;
    vertexBuffer[2] = -1;
    vertexBuffer[3] = 1;
    vertexBuffer[4] = 0;
    vertexBuffer[5] = -1;
    vertexBuffer[6] = 1;
    vertexBuffer[7] = 0;
    vertexBuffer[8] = 1;
    vertexBuffer[9] = -1;
    vertexBuffer[10] = 0;
    vertexBuffer[11] = 1;

    textureBuffer[0] = 0;
    textureBuffer[1] = 0;
    textureBuffer[2] = 1;
    textureBuffer[3] = 0;
    textureBuffer[4] = 1;
    textureBuffer[5] = 1;
    textureBuffer[6] = 0;
    textureBuffer[7] = 1;

    indexBuffer[0] = 0;
    indexBuffer[1] = 1;
    indexBuffer[2] = 2;
    indexBuffer[3] = 2;
    indexBuffer[4] = 3;
    indexBuffer[5] = 0;
}

wizBlobShadowRenderer::~wizBlobShadowRenderer()
{
    delete[] vertexBuffer;
    delete[] textureBuffer;
    delete[] indexBuffer;
}

void wizBlobShadowRenderer::applyGlobalSettings()
{
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ZERO, GL_SRC_COLOR);

    #ifndef WIN32
    glEnableClientState(GL_VERTEX_ARRAY);
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glPushMatrix();
}

void wizBlobShadowRenderer::undoGlobalSettings()
{
    glDisableClientState(GL_VERTEX_ARRAY);
    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
}

void wizBlobShadowRenderer::renderBlob(wizVector3 _position, wizBlob* _blob, wizGameEntity* _entity, std::vector<wizGameEntity*>& _list, std::vector<std::string> _skip)
{
    float initial = 1000000;
    wizVector3 target;

    for (unsigned int i=0; i<8; i++)
    {
        target = ((wizMeshEntity*)_entity)->getBoundingBox().getVertex(i).sub(_position);
        float tmp = target.length();
        if (tmp < initial)
        {
            initial = tmp;
        }
    }

    target = ((wizMeshEntity*)_entity)->getTranslation().sub(_position).normalize();
    wizRay ray = wizRay(_position, target);
    target = target.mul(1000000);

    wizIntersectionPoint ip;
    ip.setDistance(1000000);
    ip.setType(wizIntersectionPoint::POINT_MISS);

    std::string lastMaterial = "";

    for (unsigned int i=0; i<_list.size(); i++)
    {
        wizMeshEntity* listEntity = (wizMeshEntity*)_list[i];

        if (wizBoundingBox::doesRayIntersect(listEntity->getBoundingBox(), ray))
        {
            wizMeshFrame* frame = listEntity->getFrameObject();
            wizMesh* mesh = listEntity->getMeshObject();

            bool flip = wizMaterialManager::getMaterial(listEntity->getMaterial())->getCullSide()==GL_FRONT;

            for (unsigned int j=0; j<mesh->getTriangles(); j++)
            {
                wizIntersectionPoint tmp = wizTriangle::getIntersectionPoint(frame->getVertexBuffer(), mesh->getIndexBuffer(), j, _position, target, flip);

                if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance()<ip.getDistance() && tmp.getDistance()>=initial)
                {
                    lastMaterial = listEntity->getMaterial();
                    ip = tmp;
                    break;
                }
            }
        }
    }

    bool skip = false;

    for (unsigned int i=0; i<_skip.size(); i++)
    {
        if (lastMaterial.find(_skip[i])!=std::string::npos)
        {
            skip = true;
            break;
        }
    }

    if (ip.getType()!=wizIntersectionPoint::POINT_MISS && !skip)
    {
        float ratio = ip.getDistance();
        float min = _blob->getMinimumDistance();
        float max = _blob->getMaximumDistance();
        if (ratio<min) ratio = min;
        ratio = (ratio-min)/(max-min);
        wizVector3 size = _blob->getMaximum().sub(_blob->getMinimum()).mul(ratio);
        wizVector3 point = ip.getPoint();

        glTranslatef(point.getX(), point.getY(), point.getZ());
        glScalef(size.getX(), size.getY(), size.getZ());

        int id = wizTextureManager::getTexture(_blob->getTexture());
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
        glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_SHORT, indexBuffer);
    }
}

void wizBlobShadowRenderer::renderBlob(wizVector3 _position, wizBlob* _blob, wizGameEntity* _entity, std::vector<wizGameEntity*>& _list)
{
    float initial = 1000000;
    wizVector3 target;

    for (unsigned int i=0; i<8; i++)
    {
        target = ((wizMeshEntity*)_entity)->getBoundingBox().getVertex(i).sub(_position);
        float tmp = target.length();
        if (tmp < initial)
        {
            initial = tmp;
        }
    }

    target = ((wizMeshEntity*)_entity)->getTranslation().sub(_position).normalize();
    wizRay ray = wizRay(_position, target);
    target = target.mul(1000000);

    wizIntersectionPoint ip;
    ip.setDistance(1000000);
    ip.setType(wizIntersectionPoint::POINT_MISS);

    std::string lastMaterial = "";

    for (unsigned int i=0; i<_list.size(); i++)
    {
        wizMeshEntity* listEntity = (wizMeshEntity*)_list[i];

        if (wizBoundingBox::doesRayIntersect(listEntity->getBoundingBox(), ray))
        {
            wizMeshFrame* frame = listEntity->getFrameObject();
            wizMesh* mesh = listEntity->getMeshObject();

            bool flip = wizMaterialManager::getMaterial(listEntity->getMaterial())->getCullSide()==GL_FRONT;

            for (unsigned int j=0; j<mesh->getTriangles(); j++)
            {
                wizIntersectionPoint tmp = wizTriangle::getIntersectionPoint(frame->getVertexBuffer(), mesh->getIndexBuffer(), j, _position, target, flip);

                if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance()<ip.getDistance() && tmp.getDistance()>=initial)
                {
                    lastMaterial = listEntity->getMaterial();
                    ip = tmp;
                    break;
                }
            }
        }
    }

    if (ip.getType()!=wizIntersectionPoint::POINT_MISS)
    {
        float ratio = ip.getDistance();
        float min = _blob->getMinimumDistance();
        float max = _blob->getMaximumDistance();
        if (ratio<min) ratio = min;
        ratio = (ratio-min)/(max-min);
        wizVector3 size = _blob->getMaximum().sub(_blob->getMinimum()).mul(ratio);
        wizVector3 point = ip.getPoint();

        glTranslatef(point.getX(), point.getY(), point.getZ());
        glScalef(size.getX(), size.getY(), size.getZ());

        int id = wizTextureManager::getTexture(_blob->getTexture());
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
        glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_SHORT, indexBuffer);
    }
}













