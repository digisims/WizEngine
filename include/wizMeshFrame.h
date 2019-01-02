#ifndef WIZMESHFRAME_H
#define WIZMESHFRAME_H

#include "wizUtility.h"
#include "wizGameEntity.h"
#include "wizBoundingBox.h"
#include "wizProgress.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"
#include "DGE_Render.h"
#include "DGE_SurfaceManager.h"

#include <string>
#include <fstream>

class wizMeshFrame
{
    public:

    wizMeshFrame();
    wizMeshFrame(std::ifstream& _msh);
    wizMeshFrame(std::fstream& _msh);
    virtual ~wizMeshFrame();

    void setVertexBuffer(GLfloat* _vertexBuffer, unsigned int _vertices);
    void setNormalBuffer(GLfloat* _normalBuffer);
    void setTime(float _time);
    GLfloat* getVertexBuffer();
    GLfloat* getAnimatedVertexBuffer(GLfloat* _vertexBuffer, float _time);
    GLfloat* getNormalBuffer();
    unsigned int getVertices();
    float getTime();

    void calculateNormals(unsigned int _textures, GLushort* _indexBuffer);
    void calculateBoundingBox();
    wizBoundingBox getBoundingBox();

    protected:

    void load(std::ifstream& _msh);
    void load(std::fstream& _msh);

    unsigned int vertices;
    GLfloat* vertexBuffer;
    GLfloat* tmpVertexBuffer;
    GLfloat* normalBuffer;
    wizBoundingBox bbox;
    float time;
    float lastTime;
};

#endif // WIZMESHFRAME_H
