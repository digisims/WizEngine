#ifndef WIZCAMERA3D_H
#define WIZCAMERA3D_H

#include "wizCamera.h"
#include "wizVector3.h"
#include "wizFrustum.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

#include <math.h>

#define PI 3.14159628

class wizCamera3D : public wizCamera
{
    public:

    wizCamera3D(float _fov, float _near, float _far);
    wizCamera3D(int _width, int _height, float _fov, float _near, float _far);
    virtual ~wizCamera3D();

    virtual void move(float _speed);
    virtual void rotate(float _deltaRoll, float _deltaPitch, float _deltaHeading);
    void setPosition(wizVector3 _position);
    void setDirection(wizVector3 _direction);
    void setModelviewMatrix(float* _matrix);
    void setRoll(float _roll);
    void setPitch(float _pitch);
    void setHeading(float _heading);
    wizVector3 getPosition();
    wizVector3 getDirection();
    float getRoll();
    float getPitch();
    float getHeading();

    void setModelIdentity();
    wizVector3 getModelUp();
    wizVector3 getModelDirection();
    wizVector3 getModelRight();
    void setModelUp(wizVector3 _up);
    void setModelDirection(wizVector3 _direction);
    void setModelRight(wizVector3 _right);
    void setLocation(wizVector3 _location);
    void lookAt(wizVector3 _eye, wizVector3 _up, wizVector3 _at);

    void applySettings();
    void undoSettings();

    wizFrustum* getFrustum();
    float* getProjectionMatrix();
    float* getModelviewMatrix();

    protected:

    void calculateProjectionMatrix();
    void update();

    int width;
    int height;
    bool refresh;
    bool custom;
    float fov;
    float nearZ;
    float farZ;
    float roll;
    float pitch;
    float heading;
    float* modelviewMatrix;
    float* projectionMatrix;
    wizVector3 direction;
    wizVector3 eye;
    wizFrustum* frustum;

    static wizVector3 up;
};

#endif // WIZCAMERA3D_H
