#include "wizProjector.h"

wizProjector::wizProjector(wizCamera3D* _camera)
{
    camera = _camera;

    textureMatrix = new float[16];
    tmp = new float[16];

    update();
}

wizProjector::~wizProjector()
{
    delete textureMatrix;
    delete tmp;
}

void wizProjector::update()
{
    wizMatrix::mul(biasMatrix, camera->getProjectionMatrix(), tmp);
    wizMatrix::mul(tmp, camera->getModelviewMatrix(), textureMatrix);
}
