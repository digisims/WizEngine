#ifndef WIZTRIANGLE_H
#define WIZTRIANGLE_H

#include "wizIntersectionPoint.h"
#include "wizVector3.h"
#include "wizRay.h"
#include "SDL.h"
#include "DGE_Frame.h"
#include "DGE_Display.h"

class wizTriangle
{
    public:

    static wizIntersectionPoint getIntersectionPoint(GLfloat* _vertexBuffer, GLushort* _indexBuffer, unsigned int _idx, wizRay _ray, bool _flip);
    static wizIntersectionPoint getIntersectionPoint(GLfloat* _vertexBuffer, GLushort* _indexBuffer, unsigned int _idx, wizVector3 _src, wizVector3 _dst, bool _flip);
};

#endif // WIZTRIANGLE_H
