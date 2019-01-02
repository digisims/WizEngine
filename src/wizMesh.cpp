#include "wizMesh.h"

wizMesh::wizMesh()
{
    colourBuffer = NULL;
    textureBuffer = NULL;
    indexBuffer = NULL;
}

wizMesh::wizMesh(std::string _filename)
{
    if (_filename.find(".msh")!=std::string::npos)
    {
        std::ifstream msh(_filename.c_str());

        int animations = 0;
        int animationCount = 0;

        while (!msh.eof())
        {
            std::string data;

            msh >> data;

            std::vector<std::string> tokens = wizUtility::splitString(data, '=');

            if (tokens.size()>0)
            {
                if (tokens[0].compare("ANIMATIONS")==0)
                {
                    animations = atoi(tokens[1].c_str());
                }
                else if (tokens[0].compare("ANIMATION")==0)
                {
                    std::string name = tokens[1];

                    wizProgress::updateProgress(animationCount / (float)animations);

                    wizMeshAnimation* animation = new wizMeshAnimation(msh);

                    addAnimation(name, animation);
                    animationCount++;
                }
                else if (tokens[0].compare("INDEX")==0)
                {
                    triangles = atoi(tokens[1].c_str());

                    indexBuffer = new GLushort[triangles * 3];

                    for (unsigned int i=0; i<triangles; i++)
                    {
                        msh >> data;

                        std::vector<std::string> tokens = wizUtility::splitString(data, ';');

                        indexBuffer[i*3] = atoi(tokens[0].c_str());
                        indexBuffer[i*3+1] = atoi(tokens[1].c_str());
                        indexBuffer[i*3+2] = atoi(tokens[2].c_str());
                    }
                }
                else if (tokens[0].compare("COLOUR")==0)
                {
                    vertices = atoi(tokens[1].c_str());

                    colourBuffer = new GLubyte[vertices * 4];

                    for (unsigned int i=0; i<vertices; i++)
                    {
                        msh >> data;

                        std::vector<std::string> tokens = wizUtility::splitString(data, ';');

                        colourBuffer[i*4] = atoi(tokens[0].c_str());
                        colourBuffer[i*4+1] = atoi(tokens[1].c_str());
                        colourBuffer[i*4+2] = atoi(tokens[2].c_str());
                        colourBuffer[i*4+3] = atoi(tokens[3].c_str());
                    }
                }
                else if (tokens[0].compare("TEXTURE")==0)
                {
                    textures = atoi(tokens[1].c_str());
                    vertices = atoi(tokens[2].c_str());

                    textureBuffer = new GLfloat*[textures];

                    for (unsigned int i=0; i<textures; i++)
                    {
                        textureBuffer[i] = new GLfloat[vertices*2];

                        for (unsigned int j=0; j<vertices; j++)
                        {
                            msh >> data;

                            std::vector<std::string> tokens = wizUtility::splitString(data, ';');

                            textureBuffer[i][j*2] = atof(tokens[0].c_str());
                            textureBuffer[i][j*2+1] = atof(tokens[1].c_str());
                        }
                    }
                }
            }

            wizProgress::refreshProgress();
        }

        msh.close();
    }
    else
    {
        std::fstream msh(_filename.c_str(), std::ios::binary|std::ios::in);

        msh.read((char*)&textures, sizeof(unsigned int));
        msh.read((char*)&vertices, sizeof(unsigned int));

        textureBuffer = new GLfloat*[textures];

        for (unsigned int i=0; i<textures; i++)
        {
            textureBuffer[i] = new GLfloat[vertices*2];

            msh.read((char*)textureBuffer[i], sizeof(GLfloat)*vertices*2);
        }

        unsigned int colours = 0;

        msh.read((char*)&colours, sizeof(unsigned int));

        if (colours>0)
        {
            colourBuffer = new GLubyte[colours*4];

            msh.read((char*)colourBuffer, sizeof(GLubyte)*colours*4);
        }

        msh.read((char*)&triangles, sizeof(unsigned int));

        indexBuffer = new GLushort[triangles*3];

        msh.read((char*)indexBuffer, sizeof(GLushort) * triangles * 3);

        unsigned int animations = 0;

        msh.read((char*)&animations, sizeof(unsigned int));

        for (unsigned int i=0; i<animations; i++)
        {
            char* name = new char[32];
            msh.read(name, sizeof(char) * 32);

            std::string strName = "";

            for (unsigned int j=0; j<32; j++)
            {
                if (name[j] == (char)0)
                {
                    break;
                }

                strName += name[j];
            }

            wizMeshAnimation* animation = new wizMeshAnimation(msh);
            addAnimation(strName, animation);

            wizProgress::updateProgress(i / (float)animations);
        }

        msh.close();
    }
}

wizMesh::~wizMesh()
{
    std::map<std::string, wizMeshAnimation*>::iterator i;

    for (i = animationMap.begin(); i != animationMap.end(); i++)
    {
        delete i->second;
    }

    if (colourBuffer!=NULL) delete[] colourBuffer;
    if (indexBuffer!=NULL) delete[] indexBuffer;
    if (textureBuffer!=NULL)
    {
        delete[] textureBuffer;
    }
}

void wizMesh::addAnimation(std::string _id, wizMeshAnimation* _animation)
{
    if (getAnimation(_id)==NULL)
    {
        animationMap[_id] = _animation;
    }
}

void wizMesh::removeAnimation(std::string _id)
{
    if (getAnimation(_id)!=NULL)
    {
        animationMap.erase(animationMap.find(_id));
    }
}

wizMeshAnimation* wizMesh::getAnimation(std::string _id)
{
    if (animationMap.find(_id) != animationMap.end())
    {
        return animationMap[_id];
    }

    return NULL;
}

void wizMesh::setColourBuffer(GLubyte* _colourBuffer)
{
    colourBuffer = _colourBuffer;
}

void wizMesh::setTextureBuffer(GLfloat** _textureBuffer, unsigned int _textures)
{
    textureBuffer = _textureBuffer;
    textures = _textures;
}

void wizMesh::setIndexBuffer(GLushort* _indexBuffer, unsigned int _triangles)
{
    indexBuffer = _indexBuffer;
    triangles = _triangles;
}

GLubyte* wizMesh::getColourBuffer()
{
    return colourBuffer;
}

GLfloat** wizMesh::getTextureBuffer()
{
    return textureBuffer;
}

GLushort* wizMesh::getIndexBuffer()
{
    return indexBuffer;
}

unsigned int wizMesh::getVertices()
{
    return vertices;
}

unsigned int wizMesh::getTriangles()
{
    return triangles;
}

unsigned int wizMesh::getTextures()
{
    return textures;
}

void wizMesh::center()
{
    for (std::map<std::string, wizMeshAnimation*>::iterator i = animationMap.begin(); i!=animationMap.end(); i++)
    {
        for (unsigned int j=0; j<i->second->getFrameCount(); j++)
        {
            wizMeshFrame* frameObject = i->second->getFrame(j);

            float x = 0;
            float y = 0;
            float z = 0;
            float count = 0;

            for (unsigned int k=0; k<frameObject->getVertices(); k++)
            {
                x += frameObject->getVertexBuffer()[k*3];
                y += frameObject->getVertexBuffer()[k*3+1];
                z += frameObject->getVertexBuffer()[k*3+2];
                count++;
            }

            x/=count;
            y/=count;
            z/=count;

            for (unsigned int k=0; k<frameObject->getVertices(); k++)
            {
                frameObject->getVertexBuffer()[k*3]-= x;
                frameObject->getVertexBuffer()[k*3+1]-=y;
                frameObject->getVertexBuffer()[k*3+2]-=z;
            }
        }
    }
}
