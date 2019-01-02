#include "wizMeshFrame.h"

wizMeshFrame::wizMeshFrame()
{
    tmpVertexBuffer = NULL;
    vertexBuffer = NULL;
    normalBuffer = NULL;
}

void wizMeshFrame::load(std::fstream& _msh)
{
    _msh.read((char*)&time, sizeof(float));
    _msh.read((char*)&vertices, sizeof(unsigned int));
    vertexBuffer = new GLfloat[vertices * 3];
    _msh.read((char*)vertexBuffer, sizeof(GLfloat) * vertices * 3);
    int normals = 0;
    _msh.read((char*)&normals, sizeof(unsigned int));

    if (normals>0)
    {
        normalBuffer = new GLfloat[normals * 3];
        _msh.read((char*)normalBuffer, sizeof(GLfloat) * normals * 3);
    }

    calculateBoundingBox();
}

void wizMeshFrame::load(std::ifstream& _msh)
{

    std::string data;

    time = 1;

    do
    {
        _msh >> data;

        std::vector<std::string> tokens = wizUtility::splitString(data, '=');

        if (tokens.size()>0)
        {
            if (tokens[0].compare("TIMING")==0)
            {
                time = atof(tokens[1].c_str());
            }
            else if (tokens[0].compare("VERTEX")==0)
            {
                vertices = atoi(tokens[1].c_str());

                vertexBuffer = new GLfloat[vertices * 3];

                for (unsigned int i=0; i<vertices; i++)
                {
                    _msh >> data;

                    std::vector<std::string> tokens = wizUtility::splitString(data, ';');

                    vertexBuffer[i*3] = atof(tokens[0].c_str());
                    vertexBuffer[i*3+1] = atof(tokens[1].c_str());
                    vertexBuffer[i*3+2] = atof(tokens[2].c_str());
                }
            }
            else if (data.compare("NORMAL")==0)
            {
                normalBuffer = new GLfloat[vertices * 3];

                for (unsigned int i=0; i<vertices; i++)
                {
                    _msh >> data;

                    std::vector<std::string> tokens = wizUtility::splitString(data, ';');

                    normalBuffer[i*4] = atof(tokens[0].c_str());
                    normalBuffer[i*4+1] = atof(tokens[1].c_str());
                    normalBuffer[i*4+2] = atof(tokens[2].c_str());
                }
            }
        }

        wizProgress::refreshProgress();
    }
    while (data.compare("END")!=0);

    calculateBoundingBox();
}

wizMeshFrame::wizMeshFrame(std::ifstream& _msh)
{
    tmpVertexBuffer = NULL;
    vertexBuffer = NULL;
    normalBuffer = NULL;

    load(_msh);
}

wizMeshFrame::wizMeshFrame(std::fstream& _msh)
{
    tmpVertexBuffer = NULL;
    vertexBuffer = NULL;
    normalBuffer = NULL;

    load(_msh);
}

wizMeshFrame::~wizMeshFrame()
{
    if (tmpVertexBuffer!=NULL) delete[] tmpVertexBuffer;
    if (vertexBuffer!=NULL) delete[] vertexBuffer;
    if (normalBuffer!=NULL) delete[] normalBuffer;
}

void wizMeshFrame::setVertexBuffer(GLfloat* _vertexBuffer, unsigned int _vertices)
{
    vertexBuffer = _vertexBuffer;
    vertices = _vertices;
}

void wizMeshFrame::setNormalBuffer(GLfloat* _normalBuffer)
{
    normalBuffer = _normalBuffer;
}

void wizMeshFrame::setTime(float _time)
{
    time = _time;
}

GLfloat* wizMeshFrame::getAnimatedVertexBuffer(GLfloat* _vertexBuffer, float _time)
{
    float diff = lastTime - _time;
    lastTime = _time;

    if (tmpVertexBuffer == NULL || diff<-0.01f || diff>0.01f)
    {
        if (tmpVertexBuffer == NULL)
        {
            tmpVertexBuffer = new GLfloat[vertices * 3];
        }

        float r = (time - _time) / time;
        if (r<0) r=0;
        if (r>1) r=1;
        float omr = 1 - r;

        for (unsigned int i=0; i<vertices*3; i++)
        {
            tmpVertexBuffer[i] = vertexBuffer[i] * r + _vertexBuffer[i] * omr;
        }
    }

    return tmpVertexBuffer;
}

GLfloat* wizMeshFrame::getVertexBuffer()
{
    return vertexBuffer;
}

GLfloat* wizMeshFrame::getNormalBuffer()
{
    return normalBuffer;
}

unsigned int wizMeshFrame::getVertices()
{
    return vertices;
}

float wizMeshFrame::getTime()
{
    return time;
}

void wizMeshFrame::calculateNormals(unsigned int _triangles, GLushort* _indexBuffer)
{
    float* faceNormals = new float[_triangles];

    for (unsigned int i=0; i<_triangles; i++)
    {
        unsigned int vi1 = _indexBuffer[i*3]*3;
        unsigned int vi2 = _indexBuffer[i*3+1]*3;
        unsigned int vi3 = _indexBuffer[i*3+2]*3;
        wizVector3 v1(vertexBuffer[vi1], vertexBuffer[vi1+1], vertexBuffer[vi1+2]);
        wizVector3 v2(vertexBuffer[vi2], vertexBuffer[vi2+1], vertexBuffer[vi2+2]);
        wizVector3 v3(vertexBuffer[vi3], vertexBuffer[vi3+1], vertexBuffer[vi3+2]);
        wizVector3 u = v2.sub(v1);
        wizVector3 v = v3.sub(v1);
        wizVector3 n = u.cross(v).normalize();

        faceNormals[i*3] = n.getX();
        faceNormals[i*3+1] = n.getY();
        faceNormals[i*3+2] = n.getZ();
    }

    normalBuffer = new float[vertices];

    for (unsigned int i=0; i<vertices; i++)
    {
        for (unsigned int j=0; j<_triangles; j++)
        {
            if (_indexBuffer[j*3] == i || _indexBuffer[j*3+1]==i || _indexBuffer[j*3+2]==i)
            {
                normalBuffer[i*3] += faceNormals[j*3];
                normalBuffer[i*3+1] += faceNormals[j*3+1];
                normalBuffer[i*3+2] += faceNormals[j*3+2];
            }
        }

        float l = sqrt(normalBuffer[i*3]*normalBuffer[i*3]+normalBuffer[i*3+1]*normalBuffer[i*3+1]+normalBuffer[i*3+2]*normalBuffer[i*3+2]);

        if (l!=0)
        {
            l = 1.0f / l;
            normalBuffer[i*3]*=l;
            normalBuffer[i*3+1]*=l;
            normalBuffer[i*3+2]*=l;
        }
    }
}

void wizMeshFrame::calculateBoundingBox()
{
    float minX = 1000000;
    float minY = 1000000;
    float minZ = 1000000;
    float maxX = -1000000;
    float maxY = -1000000;
    float maxZ = -1000000;

    for (unsigned int i=0; i<vertices; i++)
    {
        if (vertexBuffer[i*3]<minX) minX = vertexBuffer[i*3];
        if (vertexBuffer[i*3+1]<minY) minY = vertexBuffer[i*3+1];
        if (vertexBuffer[i*3+2]<minZ) minZ = vertexBuffer[i*3+2];
        if (vertexBuffer[i*3]>maxX) maxX = vertexBuffer[i*3];
        if (vertexBuffer[i*3+1]>maxY) maxY = vertexBuffer[i*3+1];
        if (vertexBuffer[i*3+2]>maxZ) maxZ = vertexBuffer[i*3+2];
    }

    bbox = wizBoundingBox(wizVector3(minX, minY, minZ), wizVector3(maxX, maxY, maxZ));
}

wizBoundingBox wizMeshFrame::getBoundingBox()
{
    return bbox;
}
