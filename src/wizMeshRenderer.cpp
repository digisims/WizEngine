#include "wizMeshRenderer.h"

wizMeshRenderer::wizMeshRenderer()
{
    cache = 65535;
}

wizMeshRenderer::wizMeshRenderer(unsigned int _cache)
{
    cache = _cache;
}

void wizMeshRenderer::disposeBatches()
{
    std::map<std::string, GLfloat* >::iterator i;
    for (i=batchVertex.begin(); i!=batchVertex.end(); i++)
    {
        delete i->second;
    }
    std::map<std::string, GLushort* >::iterator j;
    for (j=batchIndex.begin(); j!=batchIndex.end(); j++)
    {
        delete j->second;
    }
    std::map<std::string, GLubyte* >::iterator k;
    for (k=batchColour.begin(); k!=batchColour.end(); k++)
    {
        delete k->second;
    }
    std::map<std::string, GLfloat** >::iterator l;
    for (l=batchTexture.begin(); l!=batchTexture.end(); l++)
    {
        delete[] l->second;
    }
}

void wizMeshRenderer::disposeVBOs()
{
    std::map<std::string, GLuint>::iterator i;
    for (i=vboVertex.begin(); i!=vboVertex.end(); i++)
    {
        glDeleteBuffers(1, &i->second);
    }
    std::map<std::string, GLuint>::iterator j;
    for (j=vboIndex.begin(); j!=vboIndex.end(); j++)
    {
        glDeleteBuffers(1, &j->second);
    }
    std::map<std::string, GLuint>::iterator k;
    for (k=vboColour.begin(); k!=vboColour.end(); k++)
    {
        glDeleteBuffers(1, &k->second);
    }
    std::map<std::string, GLuint*>::iterator l;
    for (l=vboTexture.begin(); l!=vboTexture.end(); l++)
    {
        for (unsigned int m=0; m<sizeof(l->second)/sizeof(GLuint); m++)
        {
            if (l->second[m]!=0)
            {
                glDeleteBuffers(1, &l->second[m]);
            }
        }
        delete[] l->second;
    }
}

wizMeshRenderer::~wizMeshRenderer()
{
    disposeBatches();
    disposeVBOs();
}

void wizMeshRenderer::applyGlobalSettings()
{
	glEnableClientState(GL_VERTEX_ARRAY);

	renderedVertices = 0;
	renderedTriangles = 0;
}

void wizMeshRenderer::undoGlobalSettings()
{
	glDisableClientState(GL_VERTEX_ARRAY);
}

unsigned int wizMeshRenderer::getVertices()
{
    return renderedVertices;
}

unsigned int wizMeshRenderer::getTriangles()
{
    return renderedTriangles;
}

void wizMeshRenderer::resetBatch(std::string _material)
{
    batchVertices[_material] = 0;
    batchIndices[_material] = 0;
}

void wizMeshRenderer::compileBatch(std::string _material)
{
    if (vboCompiled.find(_material)!=vboCompiled.end() && vboCompiled[_material])
    {
        return;
    }

    wizMaterial* material = wizMaterialManager::getMaterial(_material);

    vboCompiled[_material] = true;

    vboIndex[_material] = 0;
    vboVertex[_material] = 0;
    vboColour[_material] = 0;
    vboTexture[_material] = new GLuint[material->getTextures()];

    glGenBuffers(1, &vboIndex[_material]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex[_material]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batchIndices[_material] * 3 * sizeof(GLushort), batchIndex[_material], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vboVertex[_material]);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertex[_material]);
    glBufferData(GL_ARRAY_BUFFER, batchVertices[_material] * 3 * sizeof(GLfloat), batchVertex[_material], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (material->hasColourBuffer())
    {
        glGenBuffers(1, &vboColour[_material]);
        glBindBuffer(GL_ARRAY_BUFFER, vboColour[_material]);
        glBufferData(GL_ARRAY_BUFFER, batchVertices[_material] * 4 * sizeof(GLubyte), batchColour[_material], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    for (unsigned int i=0; i<material->getTextures(); i++)
    {
        glGenBuffers(1, &vboTexture[_material][i]);
        glBindBuffer(GL_ARRAY_BUFFER, vboTexture[_material][i]);
        glBufferData(GL_ARRAY_BUFFER, batchVertices[_material] * 3 * sizeof(GLfloat), batchTexture[_material][i], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void wizMeshRenderer::batchMesh(wizMeshEntity* _entity)
{
    std::string material = _entity->getMaterial();

    if (batchVertex.find(material)==batchVertex.end())
    {
        batchVertex[material] = new GLfloat[cache];
        batchIndex[material] = new GLushort[cache];
        batchTexture[material] = new GLfloat*[_entity->getMeshObject()->getTextures()];
        batchColour[material] = new GLubyte[cache];

        for (unsigned int i=0; i<_entity->getMeshObject()->getTextures(); i++)
        {
            batchTexture[material][i] = new GLfloat[cache];
        }
        batchVertices[material]=0;
        batchIndices[material]=0;
    }

    wizMeshFrame* frame = _entity->getFrameObject();
    wizMesh* mesh = _entity->getMeshObject();

    memcpy((char*)&batchVertex[material][batchVertices[material]*3], frame->getVertexBuffer(), frame->getVertices()*3*sizeof(GLfloat));
    if (mesh->getColourBuffer()!=NULL)
    {
        memcpy((char*)&batchColour[material][batchVertices[material]*3], mesh->getColourBuffer(), frame->getVertices()*3*sizeof(GLubyte));
    }

    if (mesh->getTextureBuffer()!=NULL)
    {
        for (unsigned int i=0; i<mesh->getTextures(); i++)
        {
            memcpy((char*)&batchTexture[material][i][batchVertices[material]*2], mesh->getTextureBuffer()[i], frame->getVertices()*2*sizeof(GLfloat));
        }
    }
    unsigned int tris = mesh->getTriangles();
    memcpy((char*)&batchIndex[material][batchIndices[material]*3], mesh->getIndexBuffer(), tris*3*sizeof(GLushort));
    tris*=3;
    unsigned int offs = batchIndices[material]*3;
    unsigned int start = batchVertices[material];
    for (unsigned int i=0; i<tris; i++)
    {
        batchIndex[material][offs+i]+=start;
    }

    batchVertices[material]+=frame->getVertices();
    batchIndices[material]+=mesh->getTriangles();
}

void wizMeshRenderer::renderMeshEntity(wizMeshEntity* _entity)
{
    if (wizLightManager::getLights()>0)
    {
        wizLightManager::applyGlobalSettings();

        wizMaterial* material = wizMaterialManager::getMaterial(_entity->getMaterial());
        std::vector<wizMaterialStage*> stages = material->getStages();

        wizLightManager::applySettings(_entity->getBoundingBox().getCenter());

        material->applySettings();

        for (unsigned int i=0; i<stages.size(); i++)
        {
            stages[i]->applySettings();

            if (stages[i]->getColourBuffer()) _entity->prepareColourBuffer();
            if (stages[i]->getTextures()>0) _entity->prepareTextureBuffer(stages[i]->getTextures());

            _entity->prepareVertexBuffer();
            _entity->render();

            stages[i]->undoSettings();
        }

        material->undoSettings();

        wizLightManager::undoSettings();
        wizLightManager::undoGlobalSettings();
    }
    else
    {
        wizMaterial* material = wizMaterialManager::getMaterial(_entity->getMaterial());
        std::vector<wizMaterialStage*> stages = material->getStages();

        material->applySettings();

        for (unsigned int i=0; i<stages.size(); i++)
        {
            stages[i]->applySettings();

            if (stages[i]->getColourBuffer()) _entity->prepareColourBuffer();
            if (stages[i]->getTextures()>0) _entity->prepareTextureBuffer(stages[i]->getTextures());
            _entity->prepareVertexBuffer();

            _entity->render();

            stages[i]->undoSettings();
        }

        material->undoSettings();
    }
}

std::vector<wizGameEntity*> wizMeshRenderer::findOccludingMeshList(std::vector<wizGameEntity*>& _list, wizGameEntity* _entity, wizCamera3D* _camera, unsigned int _threshold)
{
    wizVector3 source = _camera->getPosition();
    wizMeshEntity* entity = (wizMeshEntity*)_entity;
    wizRay centerRay(source, entity->getBoundingBox().getCenter().sub(source).normalize());
    wizRay ray[8];
    wizVector3 target[8];
    float distance[8];
    float fdist = entity->getBoundingBox().getCenter().sub(source).length();

    for (unsigned int i=0; i<8; i++)
    {
        target[i] = entity->getBoundingBox().getVertex(i);
        wizVector3 direction = target[i].sub(source);
        ray[i] = wizRay(source, direction.normalize());
        distance[i] = direction.length();
    }

    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<_list.size(); i++)
    {
        wizMeshEntity* listEntity = (wizMeshEntity*)_list[i];
        wizIntersectionPoint boxIP = wizBoundingBox::getIntersectionPoint(listEntity->getBoundingBox(), centerRay);

        if (listEntity->getVisible() && boxIP.getType() != wizIntersectionPoint::POINT_MISS && boxIP.getDistance() < fdist)
        {
            wizMeshFrame* frame = listEntity->getFrameObject();
            wizMesh* mesh = listEntity->getMeshObject();

            bool flip = wizMaterialManager::getMaterial(listEntity->getMaterial())->getCullSide()==GL_FRONT;

            unsigned int count = 0;

            for (unsigned int k=0; k<8; k++)
            {
                for (unsigned int j=0; j<mesh->getTriangles(); j++)
                {
                    wizIntersectionPoint tmp = wizTriangle::getIntersectionPoint(frame->getVertexBuffer(), mesh->getIndexBuffer(), j, source, target[k], flip);

                    if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance()<distance[k])
                    {
                        count++;
                        break;
                    }
                }

                if (count >= _threshold)
                {
                    break;
                }
            }

            if (count >= _threshold)
            {
                list.push_back(_list[i]);
            }
        }
    }

    return list;
}

std::vector<wizGameEntity*> wizMeshRenderer::findOccludingMeshList(std::vector<wizGameEntity*>& _list, wizGameEntity* _entity, wizCamera3D* _camera, unsigned int _threshold, std::vector<wizGameEntity*> _cache)
{
    wizVector3 source = _camera->getPosition();
    wizMeshEntity* entity = (wizMeshEntity*)_entity;
    wizRay centerRay(source, entity->getBoundingBox().getCenter().sub(source).normalize());
    wizRay ray[8];
    wizVector3 target[8];
    float distance[8];
    float fdist = entity->getBoundingBox().getCenter().sub(source).length();

    for (unsigned int i=0; i<8; i++)
    {
        target[i] = entity->getBoundingBox().getVertex(i);
        wizVector3 direction = target[i].sub(source);
        ray[i] = wizRay(source, direction.normalize());
        distance[i] = direction.length();
    }

    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<_cache.size(); i++)
    {
        wizMeshEntity* cacheEntity = (wizMeshEntity*)_cache[i];
        wizIntersectionPoint boxIP = wizBoundingBox::getIntersectionPoint(cacheEntity->getBoundingBox(), centerRay);

        if (cacheEntity->getVisible() && boxIP.getType() != wizIntersectionPoint::POINT_MISS && boxIP.getDistance() < fdist)
        {
            wizMeshFrame* frame = cacheEntity->getFrameObject();
            wizMesh* mesh = cacheEntity->getMeshObject();

            bool flip = wizMaterialManager::getMaterial(cacheEntity->getMaterial())->getCullSide()==GL_FRONT;

            unsigned int count = 0;

            for (unsigned int k=0; k<8; k++)
            {
                for (unsigned int j=0; j<mesh->getTriangles(); j++)
                {
                    wizIntersectionPoint tmp = wizTriangle::getIntersectionPoint(frame->getVertexBuffer(), mesh->getIndexBuffer(), j, source, target[k], flip);

                    if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance()<distance[k])
                    {
                        count++;
                        break;
                    }
                }

                if (count >= _threshold)
                {
                    break;
                }
            }

            if (count >= _threshold)
            {
                list.push_back(_cache[i]);
            }
        }
    }

    if (list.size()>0)
    {
        return list;
    }

    for (unsigned int i=0; i<_list.size(); i++)
    {
        bool found = false;

        for (unsigned int j=0; j<_cache.size(); j++)
        {
            if (_cache[j] == _list[i])
            {
                found=true;
                break;
            }
        }

        if (!found)
        {
            wizMeshEntity* listEntity = (wizMeshEntity*)_list[i];

            wizIntersectionPoint boxIP = wizBoundingBox::getIntersectionPoint(listEntity->getBoundingBox(), centerRay);

            if (listEntity->getVisible() && boxIP.getType() != wizIntersectionPoint::POINT_MISS && boxIP.getDistance() < fdist)
            {
                wizMeshFrame* frame = listEntity->getFrameObject();
                wizMesh* mesh = listEntity->getMeshObject();

                bool flip = wizMaterialManager::getMaterial(listEntity->getMaterial())->getCullSide()==GL_FRONT;

                unsigned int count = 0;

                for (unsigned int k=0; k<8; k++)
                {
                    for (unsigned int j=0; j<mesh->getTriangles(); j++)
                    {
                        wizIntersectionPoint tmp = wizTriangle::getIntersectionPoint(frame->getVertexBuffer(), mesh->getIndexBuffer(), j, source, target[k], flip);

                        if (tmp.getType()!=wizIntersectionPoint::POINT_MISS && tmp.getDistance()<distance[k])
                        {
                            count++;
                            break;
                        }
                    }

                    if (count >= _threshold)
                    {
                        break;
                    }
                }

                if (count >= _threshold)
                {
                    list.push_back(_list[i]);
                }
            }
        }
    }

    return list;
}

void wizMeshRenderer::renderMeshListCommon(std::vector<wizGameEntity*>& _list)
{
    if (wizLightManager::getLights()>0)
    {
        cached = false;

        batches = 0;

        wizLightManager::applyGlobalSettings();

        std::map<std::string, std::map<std::string, std::vector<wizMeshEntity*> > > batch;

        std::vector<std::string> materialList;

        for (unsigned int i=0; i<_list.size(); i++)
        {
            wizMeshEntity* entity = (wizMeshEntity*)_list[i];

            std::string material = entity->getMaterial();
            std::string id = _list[i]->getID();

            if (batch.find(material) == batch.end())
            {
                materialList.push_back(material);
            }

            if (entity->getVisible())
            {
                batch[material][id].push_back(entity);
            }
        }

        while (order.size() < materialList.size())
        {
            order.push_back(0);
        }

        for (unsigned int i=0; i<materialList.size(); i++)
        {
            order[i] = i;
        }

        for (unsigned int i=0; i<materialList.size(); i++)
        {
            wizMaterial* m1 = wizMaterialManager::getMaterial(materialList[order[i]]);

            for (unsigned int l=i+1; l<materialList.size(); l++)
            {
                wizMaterial* m2 = wizMaterialManager::getMaterial(materialList[order[l]]);

                if (m2->getSortOrder() < m1->getSortOrder())
                {
                    unsigned int tmp = order[l];
                    order[l] = order[i];
                    order[i] = tmp;
                }
            }
        }

        std::map<std::string, std::vector<wizMeshEntity*> >::iterator k;
        int count = 0;

        for (unsigned int j = 0; j<materialList.size(); j++)
        {
            std::string name = materialList[order[j]];

            resetBatch(name);

            wizMaterial* material = wizMaterialManager::getMaterial(name);
            material->applySettings();

            std::vector<wizMaterialStage*> stages = material->getStages();
            std::string lightList = "";

            for (unsigned int l=0; l<stages.size(); l++)
            {
                stages[l]->applySettings();

                for (k = batch[name].begin(); k!=batch[name].end(); k++)
                {
                    wizMeshEntity* entity = batch[name][k->first][0];

                    if (entity->getTransformed() || entity->isAnimating())
                    {
                        if (l==0) count++;
                        entity->prepareVertexBuffer();

                        if (stages[l]->getColourBuffer()) entity->prepareColourBuffer();
                        if (stages[l]->getTextures()>0) entity->prepareTextureBuffer(stages[l]->getTextures());

                        for (unsigned int i=0; i<batch[name][k->first].size(); i++)
                        {
                            wizMeshEntity* entity = (wizMeshEntity*)batch[name][k->first][i];
                            std::string lightID = wizLightManager::applySettings(entity->getBoundingBox().getCenter());

                            if (lightID.compare(lightList)!=0)
                            {
                                entity->render();

                                wizLightManager::undoSettings();

                                renderedVertices += entity->getFrameObject()->getVertices();
                                renderedTriangles += entity->getMeshObject()->getTriangles();
                            }
                            else
                            {
                                batchMesh(entity);
                            }

                            lightList = lightID;
                        }
                    }
                    else
                    {
                        batchMesh(entity);
                    }
                }

                if (batchIndices[name]>0)
                {
                    if (l==0) count++;

                    glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                    if (stages[l]->getColourBuffer())
                    {
                        glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                    }

                    if (stages[l]->getTextures()>0)
                    {
                        for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                        {
                            #ifndef WIN32
                            glActiveTexture(GL_TEXTURE0+z);
                            glClientActiveTexture(GL_TEXTURE0 + z);
                            #endif
                            glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                        }
                    }

                    glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);

                    renderedVertices += batchVertices[name];
                    renderedTriangles += batchIndices[name];
                }

                stages[l]->undoSettings();
            }

            material->undoSettings();
        }

        wizLightManager::undoGlobalSettings();

        batches = count;
    }
    else
    {
        bool same = _list.size() == lastListAlt.size();

        if (!locked && same)
        {
            for (unsigned int i=0; i<_list.size(); i++)
            {
                std::vector<wizGameEntity*>::iterator found = find(lastListAlt.begin(),lastListAlt.end(),_list[i]);

                if (found == lastListAlt.end())
                {
                    same = false;
                    break;
                }
            }
        }

        batches = 0;

        if (!same)
        {
            batch2.clear();

            for (unsigned int i=0; i<_list.size(); i++)
            {
                wizMeshEntity* entity = (wizMeshEntity*)_list[i];

                std::string material = entity->getMaterial();
                std::string id = _list[i]->getID();

                if (batch2.find(material) == batch2.end())
                {
                    materialList.push_back(material);
                }

                if (entity->getVisible())
                {
                    batch2[material][id].push_back(entity);
                }
            }

            while (order.size() < materialList.size())
            {
                order.push_back(0);
            }

            for (unsigned int i=0; i<materialList.size(); i++)
            {
                order[i] = i;
            }

            for (unsigned int i=0; i<materialList.size(); i++)
            {
                wizMaterial* m1 = wizMaterialManager::getMaterial(materialList[order[i]]);

                for (unsigned int l=i+1; l<materialList.size(); l++)
                {
                    wizMaterial* m2 = wizMaterialManager::getMaterial(materialList[order[l]]);

                    if (m2->getSortOrder() < m1->getSortOrder())
                    {
                        unsigned int tmp = order[l];
                        order[l] = order[i];
                        order[i] = tmp;
                    }
                }
            }
        }

        std::map<std::string, std::vector<wizMeshEntity*> >::iterator k;
        int count = 0;
        cached = same;

        if (same)
        {
            for (unsigned int j = 0; j<materialList.size(); j++)
            {
                std::string name = materialList[order[j]];

                wizMaterial* material = wizMaterialManager::getMaterial(name);
                material->applySettings();

                if (locked)
                {
                    compileBatch(name);
                }

                std::vector<wizMaterialStage*> stages = material->getStages();

                for (unsigned int l=0; l<stages.size(); l++)
                {
                    stages[l]->applySettings();

                    for (k = batch2[name].begin(); k!=batch2[name].end(); k++)
                    {
                        wizMeshEntity* entity = batch2[name][k->first][0];

                        if (entity->getTransformed() || entity->isAnimating())
                        {
                            if (l==0) count++;
                            entity->prepareVertexBuffer();

                            if (stages[l]->getColourBuffer()) entity->prepareColourBuffer();
                            if (stages[l]->getTextures()>0) entity->prepareTextureBuffer(stages[l]->getTextures());

                            for (unsigned int i=0; i<batch2[name][k->first].size(); i++)
                            {
                                wizMeshEntity* entity = (wizMeshEntity*)batch2[name][k->first][i];

                                entity->render();

                                renderedVertices += entity->getFrameObject()->getVertices();
                                renderedTriangles += entity->getMeshObject()->getTriangles();
                            }
                        }
                    }

                    if (batchIndices[name]>0)
                    {
                        if (l==0) count++;

                        if (locked)
                        {
                            glBindBuffer(GL_ARRAY_BUFFER, vboVertex[name]);
                            glVertexPointer(3, GL_FLOAT, 0, NULL);

                            if (stages[l]->getColourBuffer())
                            {
                                glBindBuffer(GL_ARRAY_BUFFER, vboColour[name]);
                                glColorPointer(4, GL_UNSIGNED_BYTE, 0, NULL);
                            }

                            if (stages[l]->getTextures()>0)
                            {
                                for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                                {
                                    #ifndef WIN32
                                    glActiveTexture(GL_TEXTURE0+z);
                                    glClientActiveTexture(GL_TEXTURE0 + z);
                                    #endif
                                    glBindBuffer(GL_ARRAY_BUFFER, vboTexture[name][z]);
                                    glTexCoordPointer(2, GL_FLOAT, 0, NULL);
                                }
                            }

                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex[name]);
                            glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, NULL);

                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                        }
                        else
                        {
                            glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                            if (stages[l]->getColourBuffer())
                            {
                                glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                            }

                            if (stages[l]->getTextures()>0)
                            {
                                for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                                {
                                    #ifndef WIN32
                                    glActiveTexture(GL_TEXTURE0+z);
                                    glClientActiveTexture(GL_TEXTURE0 + z);
                                    #endif
                                    glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                                }
                            }

                            glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);
                        }

                        renderedVertices += batchVertices[name];
                        renderedTriangles += batchIndices[name];
                    }

                    stages[l]->undoSettings();
                }

                material->undoSettings();
            }
        }
        else
        {
            for (unsigned int j = 0; j<materialList.size(); j++)
            {
                std::string name = materialList[order[j]];

                resetBatch(name);

                wizMaterial* material = wizMaterialManager::getMaterial(name);
                material->applySettings();

                std::vector<wizMaterialStage*> stages = material->getStages();

                for (unsigned int l=0; l<stages.size(); l++)
                {
                    stages[l]->applySettings();

                    for (k = batch2[name].begin(); k!=batch2[name].end(); k++)
                    {
                        wizMeshEntity* entity = batch2[name][k->first][0];

                        if (entity->getTransformed() || entity->isAnimating())
                        {
                            if (l==0) count++;
                            entity->prepareVertexBuffer();

                            if (stages[l]->getColourBuffer()) entity->prepareColourBuffer();
                            if (stages[l]->getTextures()>0) entity->prepareTextureBuffer(stages[l]->getTextures());

                            for (unsigned int i=0; i<batch2[name][k->first].size(); i++)
                            {
                                wizMeshEntity* entity = batch2[name][k->first][i];

                                entity->render();

                                renderedVertices += entity->getFrameObject()->getVertices();
                                renderedTriangles += entity->getMeshObject()->getTriangles();
                            }
                        }
                        else
                        {
                            batchMesh(entity);
                        }
                    }

                    if (batchIndices[name]>0)
                    {
                        if (l==0) count++;

                        glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                        if (stages[l]->getColourBuffer())
                        {
                            glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                        }

                        if (stages[l]->getTextures()>0)
                        {
                            for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                            {
                                #ifndef WIN32
                                glActiveTexture(GL_TEXTURE0+z);
                                glClientActiveTexture(GL_TEXTURE0 + z);
                                #endif
                                glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                            }
                        }

                        glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);

                        renderedVertices += batchVertices[name];
                        renderedTriangles += batchIndices[name];
                    }

                    stages[l]->undoSettings();
                }

                material->undoSettings();
            }
        }

        batches = count;
    }

    lastListAlt = _list;
}

void wizMeshRenderer::renderMeshListUnique(std::vector<wizGameEntity*>& _list)
{
    if (wizLightManager::getLights()>0)
    {
        cached = false;

        batches = 0;

        wizLightManager::applyGlobalSettings();

        std::map<std::string, std::vector<wizMeshEntity*> > batch;

        std::vector<std::string> materialList;

        for (unsigned int i=0; i<_list.size(); i++)
        {
            wizMeshEntity* entity = (wizMeshEntity*)_list[i];

            std::string material = entity->getMaterial();

            if (batch.find(material) == batch.end())
            {
                materialList.push_back(material);
            }

            if (entity->getVisible())
            {
                batch[material].push_back(entity);
            }
        }

        while (order.size() < materialList.size())
        {
            order.push_back(0);
        }

        for (unsigned int i=0; i<materialList.size(); i++)
        {
            order[i] = i;
        }

        for (unsigned int i=0; i<materialList.size(); i++)
        {
            wizMaterial* m1 = wizMaterialManager::getMaterial(materialList[order[i]]);

            for (unsigned int l=i+1; l<materialList.size(); l++)
            {
                wizMaterial* m2 = wizMaterialManager::getMaterial(materialList[order[l]]);

                if (m2->getSortOrder() < m1->getSortOrder())
                {
                    unsigned int tmp = order[l];
                    order[l] = order[i];
                    order[i] = tmp;
                }
            }
        }

        int count = 0;

        for (unsigned int j = 0; j<materialList.size(); j++)
        {
            std::string name = materialList[order[j]];

            resetBatch(name);

            wizMaterial* material = wizMaterialManager::getMaterial(name);
            material->applySettings();

            std::vector<wizMaterialStage*> stages = material->getStages();
            std::string lightList = "";

            for (unsigned int l=0; l<stages.size(); l++)
            {
                stages[l]->applySettings();

                for (unsigned int k = 0; k<batch[name].size(); k++)
                {
                    wizMeshEntity* entity = batch[name][k];
                    std::string lightID = wizLightManager::applySettings(entity->getBoundingBox().getCenter());

                    if (entity->getTransformed() || entity->isAnimating() || lightID.compare(lightList)!=0)
                    {
                        if (l==0) count++;
                        entity->prepareVertexBuffer();

                        if (stages[l]->getColourBuffer()) entity->prepareColourBuffer();
                        if (stages[l]->getTextures()>0) entity->prepareTextureBuffer(stages[l]->getTextures());

                        entity->render();

                        wizLightManager::undoSettings();

                        renderedVertices += entity->getFrameObject()->getVertices();
                        renderedTriangles += entity->getMeshObject()->getTriangles();
                    }
                    else
                    {
                        batchMesh(entity);
                    }

                    lightList = lightID;
                }

                if (batchIndices[name]>0)
                {
                    if (l==0) count++;

                    glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                    if (stages[l]->getColourBuffer())
                    {
                        glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                    }

                    if (stages[l]->getTextures()>0)
                    {
                        for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                        {
                            #ifndef WIN32
                            glActiveTexture(GL_TEXTURE0+z);
                            glClientActiveTexture(GL_TEXTURE0 + z);
                            #endif
                            glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                        }
                    }

                    wizLightManager::applySettings(batch[name][0]->getBoundingBox().getCenter());

                    glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);

                    wizLightManager::undoSettings();

                    renderedVertices += batchVertices[name];
                    renderedTriangles += batchIndices[name];
                }

                stages[l]->undoSettings();
            }

            material->undoSettings();
        }

        wizLightManager::undoGlobalSettings();

        batches = count;
    }
    else
    {
        bool same = _list.size() == lastListAlt.size();

        if (!locked && same)
        {
            for (unsigned int i=0; i<_list.size(); i++)
            {
                if (find(lastListAlt.begin(),lastListAlt.end(),_list[i]) == lastListAlt.end())
                {
                    same = false;
                    break;
                }
            }
        }

        batches = 0;

        if (!same)
        {
            batch.clear();
            materialList.clear();

            for (unsigned int i=0; i<_list.size(); i++)
            {
                wizMeshEntity* entity = (wizMeshEntity*)_list[i];

                std::string material = entity->getMaterial();

                if (batch.find(material) == batch.end())
                {
                    materialList.push_back(material);
                }

                if (entity->getVisible())
                {
                    batch[material].push_back(entity);
                }
            }

            while (order.size() < materialList.size())
            {
                order.push_back(0);
            }

            for (unsigned int i=0; i<materialList.size(); i++)
            {
                order[i] = i;
            }

            for (unsigned int i=0; i<materialList.size(); i++)
            {
                wizMaterial* m1 = wizMaterialManager::getMaterial(materialList[order[i]]);

                for (unsigned int l=i+1; l<materialList.size(); l++)
                {
                    wizMaterial* m2 = wizMaterialManager::getMaterial(materialList[order[l]]);

                    if (m2->getSortOrder() < m1->getSortOrder())
                    {
                        unsigned int tmp = order[l];
                        order[l] = order[i];
                        order[i] = tmp;
                    }
                }
            }
        }

        int count = 0;
        cached = same;

        if (same)
        {
            for (unsigned int j = 0; j<materialList.size(); j++)
            {
                std::string name = materialList[order[j]];

                wizMaterial* material = wizMaterialManager::getMaterial(name);
                material->applySettings();

                if (locked)
                {
                    compileBatch(name);
                }

                std::vector<wizMaterialStage*> stages = material->getStages();

                for (unsigned int l=0; l<stages.size(); l++)
                {
                    stages[l]->applySettings();

                    if (batchIndices[name]>0)
                    {
                        if (l==0) count++;

                        if (locked)
                        {
                            glBindBuffer(GL_ARRAY_BUFFER, vboVertex[name]);
                            glVertexPointer(3, GL_FLOAT, 0, NULL);

                            if (stages[l]->getColourBuffer())
                            {
                                glBindBuffer(GL_ARRAY_BUFFER, vboColour[name]);
                                glColorPointer(4, GL_UNSIGNED_BYTE, 0, NULL);
                            }

                            if (stages[l]->getTextures()>0)
                            {
                                for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                                {
                                    #ifndef WIN32
                                    glActiveTexture(GL_TEXTURE0+z);
                                    glClientActiveTexture(GL_TEXTURE0 + z);
                                    #endif
                                    glBindBuffer(GL_ARRAY_BUFFER, vboTexture[name][z]);
                                    glTexCoordPointer(2, GL_FLOAT, 0, NULL);
                                }
                            }

                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex[name]);
                            glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, NULL);

                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                        }
                        else
                        {
                            glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                            if (stages[l]->getColourBuffer())
                            {
                                glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                            }

                            if (stages[l]->getTextures()>0)
                            {
                                for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                                {
                                    #ifndef WIN32
                                    glActiveTexture(GL_TEXTURE0+z);
                                    glClientActiveTexture(GL_TEXTURE0 + z);
                                    #endif
                                    glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                                }
                            }

                            glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);
                        }

                        renderedVertices += batchVertices[name];
                        renderedTriangles += batchIndices[name];
                    }

                    stages[l]->undoSettings();
                }

                material->undoSettings();
            }
        }
        else
        {
            for (unsigned int j = 0; j<materialList.size(); j++)
            {
                std::string name = materialList[order[j]];

                resetBatch(name);

                wizMaterial* material = wizMaterialManager::getMaterial(name);
                material->applySettings();

                std::vector<wizMaterialStage*> stages = material->getStages();

                for (unsigned int l=0; l<stages.size(); l++)
                {
                    stages[l]->applySettings();

                    for (unsigned int k=0; k<batch[name].size(); k++)
                    {
                        wizMeshEntity* entity = batch[name][k];
                        batchMesh(entity);
                    }

                    if (batchIndices[name]>0)
                    {
                        if (l==0) count++;

                        glVertexPointer(3, GL_FLOAT, 0, batchVertex[name]);

                        if (stages[l]->getColourBuffer())
                        {
                            glColorPointer(4, GL_UNSIGNED_BYTE, 0, batchColour[name]);
                        }

                        if (stages[l]->getTextures()>0)
                        {
                            for (unsigned int z=0; z<stages[l]->getTextures(); z++)
                            {
                                #ifndef WIN32
                                glActiveTexture(GL_TEXTURE0+z);
                                glClientActiveTexture(GL_TEXTURE0 + z);
                                #endif
                                glTexCoordPointer(2, GL_FLOAT, 0, batchTexture[name][z]);
                            }
                        }

                        glDrawElements(GL_TRIANGLES, batchIndices[name]*3, GL_UNSIGNED_SHORT, batchIndex[name]);

                        renderedVertices += batchVertices[name];
                        renderedTriangles += batchIndices[name];
                    }

                    stages[l]->undoSettings();
                }

                material->undoSettings();
            }
        }

        batches = count;
    }

    lastListAlt = _list;
}

unsigned int wizMeshRenderer::getBatches()
{
    return batches;
}

bool wizMeshRenderer::getCached()
{
    return cached;
}

void wizMeshRenderer::lock()
{
    locked = true;
}

void wizMeshRenderer::unlock()
{
    locked = false;
}
