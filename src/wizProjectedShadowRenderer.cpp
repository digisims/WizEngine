#include "wizProjectedShadowRenderer.h"

float wizProjectedShadowRenderer::s[4] = { 1, 0, 0, 0 };
float wizProjectedShadowRenderer::t[4] = { 0, 1, 0, 0 };
float wizProjectedShadowRenderer::q[4] = { 0, 0, 1, 0 };
float wizProjectedShadowRenderer::r[4] = { 0, 0, 0, 1 };

wizProjectedShadowRenderer::wizProjectedShadowRenderer()
{
    width = 64;
    height = 64;
    texture = 0;
    fov = 60;
    nearZ = 0.1f;
    farZ = 1000.0f;
    camera = NULL;
    textureMatrix = new float[16];
}

wizProjectedShadowRenderer::~wizProjectedShadowRenderer()
{
    if (texture!=0)
    {
        glDeleteTextures(1, &texture);
    }

    delete[] textureMatrix;
}

void wizProjectedShadowRenderer::setWidth(int _width)
{
    width = _width;
}

void wizProjectedShadowRenderer::setHeight(int _height)
{
    height = _height;
}

void wizProjectedShadowRenderer::setFOV(float _fov)
{
    fov = _fov;
}

void wizProjectedShadowRenderer::setNearZ(float _nearZ)
{
    nearZ = _nearZ;
}

void wizProjectedShadowRenderer::setFarZ(float _farZ)
{
    farZ = _farZ;
}

void wizProjectedShadowRenderer::setPosition(wizVector3 _position)
{
    position = _position;
}

void wizProjectedShadowRenderer::setDirection(wizVector3 _direction)
{
    direction = _direction;
}

int wizProjectedShadowRenderer::getWidth()
{
    return width;
}

int wizProjectedShadowRenderer::getHeight()
{
    return height;
}

float wizProjectedShadowRenderer::getFOV()
{
    return fov;
}

float wizProjectedShadowRenderer::getNearZ()
{
    return nearZ;
}

float wizProjectedShadowRenderer::getFarZ()
{
    return farZ;
}

wizVector3 wizProjectedShadowRenderer::getPosition()
{
    return position;
}

wizVector3 wizProjectedShadowRenderer::getDirection()
{
    return direction;
}

void wizProjectedShadowRenderer::startRenderToTexture()
{
    if (texture == 0)
    {
        GLubyte* data = new GLubyte[width * height * 4];
        memset(data, 0, width * height * 4);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        delete[] data;
    }

    if (camera == NULL)
    {
        camera = new wizCamera3D(width, height, fov, nearZ, farZ);
        //camera->setDirection(direction);
        camera->setPosition(position);
        camera->setHeading(-90);
    }

    glViewport(0, 0, width, height);
    camera->applySettings();
}

void wizProjectedShadowRenderer::setCamera(wizCamera3D* _camera)
{
    camera = _camera;
}

void wizProjectedShadowRenderer::stopRenderToTexture()
{
    camera->undoSettings();
    glViewport(0, 0, DGE_DISPLAY_DEFAULT_WIDTH, DGE_DISPLAY_DEFAULT_HEIGHT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
}

void wizProjectedShadowRenderer::renderToTexture(wizGameEntity* _entity)
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    startRenderToTexture();

    glEnableClientState(GL_VERTEX_ARRAY);
    wizMeshEntity* entity = (wizMeshEntity*)_entity;
    entity->prepareVertexBuffer();
    entity->render();
    glDisableClientState(GL_VERTEX_ARRAY);

    stopRenderToTexture();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void wizProjectedShadowRenderer::render(wizGameEntity* _entity, std::vector<wizGameEntity*>& _list)
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

    textureMatrix[0] = s[0];
    textureMatrix[1] = t[0];
    textureMatrix[2] = q[0];
    textureMatrix[3] = r[0];

    textureMatrix[4] = s[1];
    textureMatrix[5] = t[1];
    textureMatrix[6] = q[1];
    textureMatrix[7] = r[1];

    textureMatrix[8] = s[2];
    textureMatrix[9] = t[2];
    textureMatrix[10] = q[2];
    textureMatrix[11] = r[2];

    textureMatrix[12] = s[3];
    textureMatrix[13] = t[3];
    textureMatrix[14] = q[3];
    textureMatrix[15] = r[3];

    glMatrixMode(GL_TEXTURE);
    glLoadMatrixf(textureMatrix);
    glMatrixMode(GL_MODELVIEW);

    for (unsigned int i=0; i<_list.size(); i++)
    {
        if (_list[i]!=_entity)
        {
            wizMeshEntity* entity = (wizMeshEntity*)_list[i];

            entity->prepareVertexBuffer();
            glTexCoordPointer(3, GL_FLOAT, 0, entity->getVertexBuffer());
            entity->render();
        }
    }

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
