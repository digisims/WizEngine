#include "wizCamera2D.h"

wizCamera2D::wizCamera2D()
{
    eye = new wizVector2();
}

wizCamera2D::~wizCamera2D()
{
    if (eye!=NULL) delete eye;
}

void wizCamera2D::setEye(wizVector2* _eye)
{
    eye = _eye;
}

wizVector2* wizCamera2D::getEye()
{
    return eye;
}

void wizCamera2D::applySettings()
{
    glViewport(0, 0, DGE_DISPLAY_DEFAULT_WIDTH, DGE_DISPLAY_DEFAULT_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    #ifndef WIN32
    glOrthof(0, DGE_DISPLAY_DEFAULT_WIDTH, DGE_DISPLAY_DEFAULT_HEIGHT, 0, -1, 1);
    #endif
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(eye->getX(), eye->getY(), 0);
}

void wizCamera2D::undoSettings()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
