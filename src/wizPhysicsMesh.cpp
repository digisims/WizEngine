#include "wizPhysicsMesh.h"

wizPhysicsMesh::wizPhysicsMesh()
{
    transformationMatrix = NULL;
    invTransformationMatrix = NULL;
}

wizPhysicsMesh::wizPhysicsMesh(wizBoundingBox _bbox, float* _matrix, float* _invMatrix)
{
    bbox = _bbox;
    transformationMatrix = _matrix;
    invTransformationMatrix = _invMatrix;
}

wizPhysicsMesh::~wizPhysicsMesh()
{
}

wizBoundingBox wizPhysicsMesh::getBoundingBox()
{
    return bbox;
}

wizVector3 wizPhysicsMesh::getCenter()
{
    return (getTransformedVertex(0).add(getTransformedVertex(6))).mul(0.5f);
}

wizVector3 wizPhysicsMesh::getVertex(unsigned int _idx)
{
    return bbox.getVertex(_idx);
}

wizVector3 wizPhysicsMesh::getTransformedVertex(unsigned int _idx)
{
    return bbox.getVertex(_idx).mul(transformationMatrix);
}
