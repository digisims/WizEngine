#include "wizPointLight.h"

wizPointLight::wizPointLight()
{
    ambient = NULL;
    diffuse = NULL;
    specular = NULL;
    position = NULL;
}

void wizPointLight::applySettings()
{
    glEnable(GL_LIGHT0 + idx);
    glLightfv(GL_LIGHT0 + idx, GL_AMBIENT, ambient->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_DIFFUSE, diffuse->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_SPECULAR, specular->getArray());
    glLightfv(GL_LIGHT0 + idx, GL_POSITION, position->getArray());
}
