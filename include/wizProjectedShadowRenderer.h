#ifndef WIZPROJECTEDSHADOWRENDERER_H
#define WIZPROJECTEDSHADOWRENDERER_H

#include "wizGameEntity.h"
#include "wizMeshEntity.h"
#include "wizVector3.h"
#include "wizCamera3D.h"

#include <vector>

class wizProjectedShadowRenderer
{
    public:

    wizProjectedShadowRenderer();
    virtual ~wizProjectedShadowRenderer();

    void setWidth(int _width);
    void setHeight(int _height);
    void setFOV(float _fov);
    void setNearZ(float _nearZ);
    void setFarZ(float _farZ);
    void setPosition(wizVector3 _position);
    void setDirection(wizVector3 _direction);
    int getWidth();
    int getHeight();
    float getFOV();
    float getNearZ();
    float getFarZ();
    wizVector3 getPosition();
    wizVector3 getDirection();
    void setCamera(wizCamera3D* _camera);

    void renderToTexture(wizGameEntity* _entity);
    void render(wizGameEntity* _entity, std::vector<wizGameEntity*>& _list);

    protected:

    void startRenderToTexture();
    void stopRenderToTexture();

    int width;
    int height;
    float fov;
    float nearZ;
    float farZ;
    float* textureMatrix;
    wizCamera3D* camera;
    wizVector3 position;
    wizVector3 direction;
    GLuint texture;

    static float s[4];
    static float t[4];
    static float q[4];
    static float r[4];
};

#endif // WIZPROJECTEDSHADOWRENDERER_H
