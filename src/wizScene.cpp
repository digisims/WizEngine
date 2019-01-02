#include "wizScene.h"

wizScene::wizScene(std::string _filename)
{
    load(_filename);
}

wizScene::~wizScene()
{
    for (unsigned int i=0; i<entityList.size(); i++)
    {
        if (entityList[i]!=NULL)
        {
            delete entityList[i];
        }
    }
}

std::vector<wizMeshEntity*> wizScene::getMeshEntities()
{
    return entityList;
}

void wizScene::load(std::string _filename)
{
    if (_filename.find(".scn")!=std::string::npos)
    {
        // text scene

        std::ifstream scn(_filename.c_str());
        unsigned int objects = 1;
        unsigned int objectCount = 0;

        while (!scn.eof())
        {
            std::string data;

            scn >> data;

            std::vector<std::string> tokens = wizUtility::splitString(data, '=');

            if (tokens.size()>0)
            {
                if (tokens[0].compare("OBJECTS")==0)
                {
                   objects = atoi(tokens[1].c_str());
                }
                else if (tokens[0].compare("OBJECT")==0)
                {
                    std::string id = tokens[1];
                    std::string material = "";
                    unsigned int vertices = 0;
                    unsigned int textures = 0;
                    unsigned int triangles = 0;
                    GLfloat* vertexBuffer = NULL;
                    GLfloat** textureBuffer = NULL;
                    GLushort* indexBuffer = NULL;

                    while (!scn.eof() && tokens[0].compare("END")!=0)
                    {
                        scn >> data;

                        if (data.compare("END")==0) break;

                        tokens = wizUtility::splitString(data, '=');

                        if (tokens[0].compare("MATERIAL")==0)
                        {
                            material = tokens[1];
                        }
                        else if (tokens[0].compare("VERTEX")==0)
                        {
                            vertices = atoi(tokens[1].c_str());
                            vertexBuffer = new GLfloat[vertices * 3];

                            for (unsigned int i=0; i<vertices; i++)
                            {
                                scn >> data;
                                tokens = wizUtility::splitString(data, ';');
                                vertexBuffer[i*3] = atof(tokens[0].c_str());
                                vertexBuffer[i*3+1] = atof(tokens[1].c_str());
                                vertexBuffer[i*3+2] = atof(tokens[2].c_str());
                            }
                        }
                        else if (tokens[0].compare("TEXTURE")==0)
                        {
                            textures = atoi(tokens[1].c_str());
                            unsigned int count = atoi(tokens[2].c_str());
                            textureBuffer = new GLfloat*[textures];

                            for (unsigned int i=0; i<textures; i++)
                            {
                                textureBuffer[i] = new GLfloat[count * 2];
                            }

                            for (unsigned int i=0; i<textures; i++)
                            {
                                for (unsigned int j=0; j<count; j++)
                                {
                                    scn >> data;
                                    tokens = wizUtility::splitString(data, ';');
                                    textureBuffer[i][j*2] = atof(tokens[0].c_str());
                                    textureBuffer[i][j*2+1] = atof(tokens[1].c_str());
                                }
                            }
                        }
                        else if (tokens[0].compare("TRIANGLES")==0)
                        {
                            triangles = atoi(tokens[1].c_str());
                            indexBuffer = new GLushort[triangles * 3];

                            for (unsigned int i=0; i<triangles; i++)
                            {
                                scn >> data;
                                tokens = wizUtility::splitString(data, ';');
                                indexBuffer[i*3] = atoi(tokens[0].c_str());
                                indexBuffer[i*3+1] = atoi(tokens[1].c_str());
                                indexBuffer[i*3+2] = atoi(tokens[2].c_str());
                            }
                        }
                    }

                    wizMaterial* materialObject = NULL;

                    if (wizMaterialManager::getMaterial(material)==NULL)
                    {
                        materialObject = new wizMaterial(material);
                        wizMaterialManager::addMaterial(material, materialObject);
                    }
                    else
                    {
                        materialObject = wizMaterialManager::getMaterial(material);
                    }

                    wizMesh* mesh = new wizMesh();
                    mesh->setTextureBuffer(textureBuffer, textures);
                    mesh->setIndexBuffer(indexBuffer, triangles);
                    wizMeshAnimation* animation = new wizMeshAnimation();
                    animation->setLoopable(false);
                    wizMeshFrame* frame = new wizMeshFrame();
                    frame->setTime(0);
                    frame->setVertexBuffer(vertexBuffer, vertices);
                    frame->calculateBoundingBox();
                    animation->addFrame(frame);
                    mesh->addAnimation("default", animation);
                    wizMeshManager::addMesh(id, mesh);

                    wizMeshEntity* entity = new wizMeshEntity();
                    entity->setMaterial(material);
                    entity->setMesh(id);
                    entity->setAnimation("default");
                    entity->setFrame(0);
                    entity->setStatic(true);

                    entityList.push_back(entity);

                    objectCount++;

                    wizProgress::updateProgress(objectCount / (float)objects);

                    if (objectCount >= objects)
                    {
                        break;
                    }
                }
            }
        }

        scn.close();
    }
    else
    {
        // compiled scene

        std::fstream scn(_filename.c_str(), std::ios::binary|std::ios::in);
        unsigned int objects = 0;
        scn.read((char*)&objects, sizeof(unsigned int));
        unsigned int objectCount = 0;

        while (!scn.eof())
        {
            char* _tmp1 = new char[64];
            for (unsigned int i=0; i<64; i++) _tmp1[i]=0;
            scn.read(_tmp1, sizeof(char) * 64);
            if (_tmp1[0]==(char)0)
            {
                break;
            }
            char* _tmp2 = new char[128];
            scn.read(_tmp2, sizeof(char) * 128);

            unsigned int vertices = 0;
            unsigned int textures = 0;
            unsigned int triangles = 0;
            GLfloat* vertexBuffer = NULL;
            GLfloat** textureBuffer = NULL;
            GLushort* indexBuffer = NULL;

            scn.read((char*)&vertices, sizeof(unsigned int));

            vertexBuffer = new GLfloat[vertices*3];
            scn.read((char*)vertexBuffer, sizeof(GLfloat)*vertices*3);

            scn.read((char*)&textures, sizeof(unsigned int));
            unsigned int count = 0;
            scn.read((char*)&count, sizeof(unsigned int));

            textureBuffer = new GLfloat*[textures];

            if (count>0)
            {
                for (unsigned int i=0; i<textures; i++)
                {
                    textureBuffer[i] = new GLfloat[count*2];
                    scn.read((char*)textureBuffer[i], sizeof(GLfloat)*count*2);
                }
            }

            scn.read((char*)&triangles, sizeof(unsigned int));
            indexBuffer = new GLushort[triangles*3];
            scn.read((char*)indexBuffer, sizeof(GLushort)*triangles*3);

            std::string id = "";

            for (unsigned int i=0; i<64; i++)
            {
                if (_tmp1[i]==(char)0) break;
                id += _tmp1[i];
            }

            std::string material = "";

            for (unsigned int i=0; i<128; i++)
            {
                if (_tmp2[i]==(char)0) break;
                material += _tmp2[i];
            }

            wizMaterial* materialObject = NULL;

            if (wizMaterialManager::getMaterial(material)==NULL)
            {
                materialObject = new wizMaterial(material);
                wizMaterialManager::addMaterial(material, materialObject);
            }
            else
            {
                materialObject = wizMaterialManager::getMaterial(material);
            }

            wizMesh* mesh = new wizMesh();
            mesh->setTextureBuffer(textureBuffer, textures);
            mesh->setIndexBuffer(indexBuffer, triangles);
            wizMeshAnimation* animation = new wizMeshAnimation();
            animation->setLoopable(false);
            wizMeshFrame* frame = new wizMeshFrame();
            frame->setTime(0);
            frame->setVertexBuffer(vertexBuffer, vertices);
            frame->calculateBoundingBox();
            animation->addFrame(frame);
            mesh->addAnimation("default", animation);
            wizMeshManager::addMesh(id, mesh);

            wizMeshEntity* entity = new wizMeshEntity();
            entity->setMaterial(material);
            entity->setMesh(id);
            entity->setAnimation("default");
            entity->setFrame(0);
            entity->setStatic(true);
            entity->update();
            entity->updateBoundingBox();

            entityList.push_back(entity);

            objectCount++;

            wizProgress::updateProgress(objectCount / (float)objects);
        }

        scn.close();
    }
}
