#include "wizCamera3D.h"
#include <fstream>

wizVector3 wizCamera3D::up = wizVector3(0, 1, 0);

wizCamera3D::wizCamera3D(float _fov, float _near, float _far)
{
    width = DGE_DISPLAY_DEFAULT_WIDTH;
    height = DGE_DISPLAY_DEFAULT_HEIGHT;
    fov = _fov;
    nearZ = _near;
    farZ = _far;
    roll = 0;
    pitch = 0;
    heading = 0;
    custom = false;

    modelviewMatrix = new float[16];
    projectionMatrix = new float[16];

    calculateProjectionMatrix();

    frustum = new wizFrustum(nearZ, farZ);
    refresh = true;

    direction.setZ(1);
}

wizCamera3D::wizCamera3D(int _width, int _height, float _fov, float _near, float _far)
{
    width = _width;
    height = _height;
    fov = _fov;
    nearZ = _near;
    farZ = _far;
    roll = 0;
    pitch = 0;
    heading = 0;
    custom = false;

    modelviewMatrix = new float[16];
    projectionMatrix = new float[16];

    calculateProjectionMatrix();

    frustum = new wizFrustum(nearZ, farZ);
    refresh = true;

    direction.setZ(1);
}

wizCamera3D::~wizCamera3D()
{
}

void wizCamera3D::update()
{
    if (custom)
    {
        /*wizVector3 zaxis = direction.normalize();
        wizVector3 xaxis = up.cross(zaxis).normalize();
        wizVector3 yaxis = zaxis.cross(xaxis);

        modelviewMatrix[0] = xaxis.getX();
        modelviewMatrix[1] = yaxis.getX();
        modelviewMatrix[2] = zaxis.getX();
        modelviewMatrix[3] = 0;

        modelviewMatrix[4] = xaxis.getY();
        modelviewMatrix[5] = yaxis.getY();
        modelviewMatrix[6] = zaxis.getY();
        modelviewMatrix[7] = 0;

        modelviewMatrix[8] = xaxis.getZ();
        modelviewMatrix[9] = yaxis.getZ();
        modelviewMatrix[10] = zaxis.getZ();
        modelviewMatrix[11] = 0;

        modelviewMatrix[12] = 0;
        modelviewMatrix[13] = 0;
        modelviewMatrix[14] = 0;
        modelviewMatrix[15] = 1;*/
    }
    else
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrix);
    }
    frustum->update(modelviewMatrix, projectionMatrix);
}

void wizCamera3D::move(float _speed)
{
    eye.setX(eye.getX() + direction.getX() * _speed);
    eye.setY(eye.getY() + direction.getY() * _speed);
    eye.setZ(eye.getZ() + direction.getZ() * _speed);

    refresh = true;
}

void wizCamera3D::rotate(float _deltaRoll, float _deltaPitch, float _deltaHeading)
{
    roll += _deltaRoll;
    pitch += _deltaPitch;
    heading += _deltaHeading;

    if (roll < -180)
    {
        roll += 360;
    }
    else if (roll >= 180)
    {
        roll -= 360;
    }

    if (pitch < -180)
    {
        pitch += 360;
    }
    else if (pitch >= 180)
    {
        pitch -= 360;
    }

    if (heading < 0)
    {
        heading += 360;
    }
    else if (heading >= 360)
    {
        heading -= 360;
    }

    float cheading = cos(heading * PI / 180);
    float sheading = sin(heading * PI / 180);
    float cpitch = cos(pitch * PI / 180);
    float spitch = sin(pitch * PI / 180);

    direction.setX(sheading * cpitch);
    direction.setZ(-cheading * cpitch);
    direction.setY(spitch);

    custom = false;
    refresh = true;
}

void wizCamera3D::setPosition(wizVector3 _position)
{
    eye = _position;
    refresh = true;
}

void wizCamera3D::setDirection(wizVector3 _direction)
{
    direction = _direction;
    custom = true;
    refresh = true;
}

void wizCamera3D::setRoll(float _roll)
{
    roll = _roll;

    float cheading = cos(heading * PI / 180);
    float sheading = sin(heading * PI / 180);
    float cpitch = cos(pitch * PI / 180);
    float spitch = sin(pitch * PI / 180);

    direction.setX(sheading * cpitch);
    direction.setZ(-cheading * cpitch);
    direction.setY(spitch);

    refresh = true;
}

void wizCamera3D::setPitch(float _pitch)
{
    pitch = _pitch;

    float cheading = cos(heading * PI / 180);
    float sheading = sin(heading * PI / 180);
    float cpitch = cos(pitch * PI / 180);
    float spitch = sin(pitch * PI / 180);

    direction.setX(sheading * cpitch);
    direction.setZ(-cheading * cpitch);
    direction.setY(spitch);

    refresh = true;
}

void wizCamera3D::setHeading(float _heading)
{
    heading = _heading;

    float cheading = cos(heading * PI / 180);
    float sheading = sin(heading * PI / 180);
    float cpitch = cos(pitch * PI / 180);
    float spitch = sin(pitch * PI / 180);

    direction.setX(sheading * cpitch);
    direction.setZ(-cheading * cpitch);
    direction.setY(spitch);

    refresh = true;
}

void wizCamera3D::setModelIdentity()
{
    for (unsigned int i=0; i<16; i++)
    {
        modelviewMatrix[i] = 0;
    }
    modelviewMatrix[0] = modelviewMatrix[5] = modelviewMatrix[10] = modelviewMatrix[15] = 1;
}

wizVector3 wizCamera3D::getModelUp()
{
    return wizVector3(modelviewMatrix[1], modelviewMatrix[5], modelviewMatrix[9]);
}

wizVector3 wizCamera3D::getModelDirection()
{
    return wizVector3(modelviewMatrix[2], modelviewMatrix[6], modelviewMatrix[10]);
}

wizVector3 wizCamera3D::getModelRight()
{
    return wizVector3(modelviewMatrix[0], modelviewMatrix[4], modelviewMatrix[8]);
}

void wizCamera3D::setModelUp(wizVector3 _up)
{
    custom = true;
    modelviewMatrix[1] = _up.getX();
    modelviewMatrix[5] = _up.getY();
    modelviewMatrix[9] = _up.getZ();
}

void wizCamera3D::setModelDirection(wizVector3 _direction)
{
    custom = true;
    modelviewMatrix[2] = _direction.getX();
    modelviewMatrix[6] = _direction.getY();
    modelviewMatrix[10] = _direction.getZ();
}

void wizCamera3D::setModelRight(wizVector3 _right)
{
    custom = true;
    modelviewMatrix[0] = _right.getX();
    modelviewMatrix[4] = _right.getY();
    modelviewMatrix[8] = _right.getZ();
}

void wizCamera3D::setLocation(wizVector3 _location)
{
    custom = true;
    modelviewMatrix[12] = _location.getX();
    modelviewMatrix[13] = _location.getY();
    modelviewMatrix[14] = _location.getZ();
}

wizVector3 wizCamera3D::getPosition()
{
    return eye;
}

wizVector3 wizCamera3D::getDirection()
{
    return direction;
}

float wizCamera3D::getRoll()
{
    return roll;
}

float wizCamera3D::getPitch()
{
    return pitch;
}

float wizCamera3D::getHeading()
{
    return heading;
}

void wizCamera3D::calculateProjectionMatrix()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    float size = nearZ * tanf(fov * PI / 180 / 2.0);
    float ratio = width/(float)height;
    #ifndef WIN32
    glFrustumf(-size, size, -size / ratio, size / ratio, nearZ, farZ);
    #endif
    glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);
    glMatrixMode(GL_MODELVIEW);
}

void wizCamera3D::setModelviewMatrix(float* _matrix)
{
    custom = true;
    modelviewMatrix = _matrix;
}

void wizCamera3D::applySettings()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(projectionMatrix);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (!custom)
    {
        glRotatef(roll, 0, 0, 1);
        glRotatef(pitch, -1, 0, 0);
        glRotatef(heading, 0, 1, 0);
        glTranslatef(-eye.getX(), -eye.getY(), -eye.getZ());
    }
    else
    {
        glMultMatrixf(modelviewMatrix);
    }

    if (refresh)
    {
        update();
        refresh = false;
    }
}

void wizCamera3D::undoSettings()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

wizFrustum* wizCamera3D::getFrustum()
{
    return frustum;
}

float* wizCamera3D::getProjectionMatrix()
{
    return projectionMatrix;
}

float* wizCamera3D::getModelviewMatrix()
{
    return modelviewMatrix;
}

void wizCamera3D::lookAt(wizVector3 _eye, wizVector3 _up, wizVector3 _at)
{
    wizVector3 z = _at.sub(_eye).normalize();
    wizVector3 x = up.cross(z).normalize();
    wizVector3 y = z.cross(x).normalize();

    setModelRight(x);
    setModelUp(y);
    setModelDirection(z);
    setLocation(wizVector3(-x.dot(_eye), -y.dot(_eye), -z.dot(_eye)));
}
