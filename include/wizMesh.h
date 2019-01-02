#ifndef WIZMESH_H
#define WIZMESH_H

#include "wizUtility.h"
#include "wizMeshAnimation.h"
#include "wizGame.h"
#include "wizProgress.h"

#include <map>
#include <string>
#include <vector>
#include <fstream>

class wizMesh
{
    public:

    wizMesh();
    wizMesh(std::string _filename);
    virtual ~wizMesh();

    void addAnimation(std::string _id, wizMeshAnimation* _animation);
    void removeAnimation(std::string _id);
    wizMeshAnimation* getAnimation(std::string _id);

    void setColourBuffer(GLubyte* _colourBuffer);
    void setTextureBuffer(GLfloat** _textureBuffer, unsigned int _textures);
    void setIndexBuffer(GLushort* _indexBuffer, unsigned int _triangles);
    GLubyte* getColourBuffer();
    GLfloat** getTextureBuffer();
    GLushort* getIndexBuffer();

    unsigned int getTriangles();
    unsigned int getTextures();
    unsigned int getVertices();

    void center();

    protected:

    unsigned int triangles;
    unsigned int textures;
    unsigned int vertices;
    std::map<std::string, wizMeshAnimation*> animationMap;
    GLubyte* colourBuffer;
    GLfloat** textureBuffer;
    GLushort* indexBuffer;
};

#endif // WIZMESH_H
