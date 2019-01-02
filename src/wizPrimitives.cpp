#include "wizPrimitives.h"

wizPrimitives::wizPrimitives()
{
    indexBuffer = new GLushort[65535];
    vertexBuffer = new GLfloat[65535];
    colourBuffer = new GLubyte[65535];
    indices = 0;
    vertices = 0;
    colours = 0;
    locked = false;
}

wizPrimitives::wizPrimitives(unsigned int _cache)
{
    indexBuffer = new GLushort[_cache];
    vertexBuffer = new GLfloat[_cache];
    colourBuffer = new GLubyte[_cache];
    indices = 0;
    vertices = 0;
    colours = 0;
    locked = false;
}

wizPrimitives::~wizPrimitives()
{
    if (indexBuffer != NULL) delete[] indexBuffer;
    if (vertexBuffer != NULL) delete[] vertexBuffer;
    if (colourBuffer != NULL) delete[] colourBuffer;
}

void wizPrimitives::applyGlobalSettings()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
}

void wizPrimitives::undoGlobalSettings()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void wizPrimitives::rotate(unsigned int _start, unsigned int _stop, float _x, float _y, float _angle)
{
    float cosf = cos(_angle);
    float sinf = sin(_angle);

    for (unsigned int i=_start; i<=_stop; i+=2)
    {
        float tx = vertexBuffer[i] - _x;
        float ty = vertexBuffer[i+1] - _y;
        vertexBuffer[i] = tx*cosf-ty*sinf+_x;
        vertexBuffer[i+1] = ty*cosf+tx*sinf+_y;
    }
}

void wizPrimitives::drawNGon(wizVector2 _position, wizVector2 _size, wizColour _colour, unsigned int _detail, float _angle)
{
    float angle = 0;
    float angleInc = 2 * 3.141592f / _detail;

    for (unsigned int i=0; i<_detail; i++)
    {
        float x1 = _position.getX();
        float y1 = _position.getY();
        float x2 = x1 + cos(angle)*_size.getX();
        float y2 = y1 + sin(angle)*_size.getY();
        float x3 = x1 + cos(angle+angleInc)*_size.getX();
        float y3 = y1 + sin(angle+angleInc)*_size.getY();

        angle += angleInc;

        vertexBuffer[i*6] = x1;
        vertexBuffer[i*6+1] = y1;
        vertexBuffer[i*6+2] = x2;
        vertexBuffer[i*6+3] = y2;
        vertexBuffer[i*6+4] = x3;
        vertexBuffer[i*6+5] = y3;
    }

    if (fabs(_angle)>0.01f)
    {
        rotate(0, _detail*6-1, _position.getX(), _position.getY(), _angle);
    }

    for (unsigned int i=0; i<_detail*3; i++)
    {
        colourBuffer[i*4] = _colour.getURed();
        colourBuffer[i*4+1] = _colour.getUGreen();
        colourBuffer[i*4+2] = _colour.getUBlue();
        colourBuffer[i*4+3] = _colour.getUAlpha();
    }

    glVertexPointer(2, GL_FLOAT, 0, vertexBuffer);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
    glDrawArrays(GL_TRIANGLES, 0, _detail * 6);
}

void wizPrimitives::drawRectangle(wizVector2 _position, wizVector2 _size, wizColour _colour, float _angle)
{
    vertexBuffer[0] = _position.getX();
    vertexBuffer[1] = _position.getY();
    vertexBuffer[2] = _position.getX() + _size.getX();
    vertexBuffer[3] = _position.getY();
    vertexBuffer[4] = _position.getX() + _size.getX();
    vertexBuffer[5] = _position.getY() + _size.getY();
    vertexBuffer[6] = _position.getX();
    vertexBuffer[7] = _position.getY() + _size.getY();

    if (fabs(_angle)>0.01f)
    {
        rotate(0, 7, _position.getX() + _size.getX() / 2, _position.getY() + _size.getY() / 2, _angle);
    }

    for (unsigned int i=0; i<4; i++)
    {
        colourBuffer[i*4+0] = _colour.getURed();
        colourBuffer[i*4+1] = _colour.getUGreen();
        colourBuffer[i*4+2] = _colour.getUBlue();
        colourBuffer[i*4+3] = _colour.getUAlpha();
    }

    indexBuffer[0] = 0;
    indexBuffer[1] = 1;
    indexBuffer[2] = 2;
    indexBuffer[3] = 2;
    indexBuffer[4] = 3;
    indexBuffer[5] = 0;

    glVertexPointer(2, GL_FLOAT, 0, vertexBuffer);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indexBuffer);
}

void wizPrimitives::drawTriangle(wizVector2 _v1, wizVector2 _v2, wizVector2 _v3, wizColour _colour, float _angle)
{
    vertexBuffer[0] = _v1.getX();
    vertexBuffer[1] = _v1.getY();
    vertexBuffer[2] = _v2.getX();
    vertexBuffer[3] = _v2.getY();
    vertexBuffer[4] = _v3.getX();
    vertexBuffer[5] = _v3.getY();

    if (fabs(_angle)>0.01f)
    {
        wizVector2 center = _v1.add(_v2).add(_v3).mul(1/3.0f);
        rotate(0, 5, center.getX(), center.getY(), _angle);
    }

    for (unsigned int i=0; i<3; i++)
    {
        colourBuffer[i*4+0] = _colour.getURed();
        colourBuffer[i*4+1] = _colour.getUGreen();
        colourBuffer[i*4+2] = _colour.getUBlue();
        colourBuffer[i*4+3] = _colour.getUAlpha();
    }

    indexBuffer[0] = 0;
    indexBuffer[1] = 1;
    indexBuffer[2] = 2;

    glVertexPointer(2, GL_FLOAT, 0, vertexBuffer);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, indexBuffer);
}

void wizPrimitives::drawPolygon(wizVector2* _v, unsigned int _vertices, wizColour _colour, float _angle)
{
    for (unsigned int i=0; i<_vertices; i++)
    {
        vertexBuffer[i*2] = _v[i].getX();
        vertexBuffer[i*2+1] = _v[i].getY();
    }

    if (fabs(_angle)>0.01f)
    {
        float cx = 0;
        float cy = 0;
        for (unsigned int i=0; i<_vertices; i+=2)
        {
            cx += vertexBuffer[i*2];
            cy += vertexBuffer[i*2+1];
        }
        cx /= _vertices;
        cy /= _vertices;
        rotate(0, _vertices*2-1, cx, cy, _angle);
    }

    for (unsigned int i=0; i<_vertices-2; i++)
    {
        indexBuffer[i*3] = i*2;
        indexBuffer[i*3+1] = i*2+1;
        indexBuffer[i*3+2] = i*2+2;
    }

    for (unsigned int i=0; i<_vertices; i++)
    {
        colourBuffer[i*4+0] = _colour.getURed();
        colourBuffer[i*4+1] = _colour.getUGreen();
        colourBuffer[i*4+2] = _colour.getUBlue();
        colourBuffer[i*4+3] = _colour.getUAlpha();
    }

    glVertexPointer(2, GL_FLOAT, 0, vertexBuffer);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
    glDrawElements(GL_TRIANGLES, (_vertices-2)*3, GL_UNSIGNED_SHORT, indexBuffer);
}

void wizPrimitives::batchNGon(wizVector2 _position, wizVector2 _size, wizColour _colour, unsigned int _detail, float _angle)
{
    if (locked) return;

    float angle = 0;
    float angleInc = 2 * 3.141592f / _detail;

    unsigned int start = vertices;

    for (unsigned int i=0; i<_detail; i++)
    {
        float x1 = _position.getX();
        float y1 = _position.getY();
        float x2 = x1 + cos(angle)*_size.getX();
        float y2 = y1 + sin(angle)*_size.getY();
        float x3 = x1 + cos(angle+angleInc)*_size.getX();
        float y3 = y1 + sin(angle+angleInc)*_size.getY();

        angle += angleInc;

        vertexBuffer[vertices++] = x1;
        vertexBuffer[vertices++] = y1;
        vertexBuffer[vertices++] = x2;
        vertexBuffer[vertices++] = y2;
        vertexBuffer[vertices++] = x3;
        vertexBuffer[vertices++] = y3;

        indexBuffer[indices++] = start;
        indexBuffer[indices++] = start+1;
        indexBuffer[indices++] = start+2;
    }

    if (fabs(_angle)>0.01f)
    {
        rotate(start, vertices-1, _position.getX(), _position.getY(), _angle);
    }

    for (unsigned int i=0; i<_detail*3; i++)
    {
        colourBuffer[colours++] = _colour.getURed();
        colourBuffer[colours++] = _colour.getUGreen();
        colourBuffer[colours++] = _colour.getUBlue();
        colourBuffer[colours++] = _colour.getUAlpha();
    }
}

void wizPrimitives::batchRectangle(wizVector2 _position, wizVector2 _size, wizColour _colour, float _angle)
{
    if (locked) return;

    unsigned int start = vertices;

    vertexBuffer[vertices++] = _position.getX();
    vertexBuffer[vertices++] = _position.getY();
    vertexBuffer[vertices++] = _position.getX() + _size.getX();
    vertexBuffer[vertices++] = _position.getY();
    vertexBuffer[vertices++] = _position.getX() + _size.getX();
    vertexBuffer[vertices++] = _position.getY() + _size.getY();
    vertexBuffer[vertices++] = _position.getX();
    vertexBuffer[vertices++] = _position.getY() + _size.getY();

    if (fabs(_angle)>0.01f)
    {
        rotate(start, vertices-1, _position.getX() + _size.getX()/2, _position.getY() + _size.getY()/2, _angle);
    }

    for (unsigned int i=0; i<vertices; i++)
    {
        colourBuffer[colours++] = _colour.getURed();
        colourBuffer[colours++] = _colour.getUGreen();
        colourBuffer[colours++] = _colour.getUBlue();
        colourBuffer[colours++] = _colour.getUAlpha();
    }

    indexBuffer[indices++] = start;
    indexBuffer[indices++] = start+1;
    indexBuffer[indices++] = start+2;
    indexBuffer[indices++] = start+2;
    indexBuffer[indices++] = start+3;
    indexBuffer[indices++] = start;
}

void wizPrimitives::batchTriangle(wizVector2 _v1, wizVector2 _v2, wizVector2 _v3, wizColour _colour, float _angle)
{
    unsigned int start = vertices;

    vertexBuffer[vertices++] = _v1.getX();
    vertexBuffer[vertices++] = _v1.getY();
    vertexBuffer[vertices++] = _v2.getX();
    vertexBuffer[vertices++] = _v2.getY();
    vertexBuffer[vertices++] = _v3.getX();
    vertexBuffer[vertices++] = _v3.getY();

    if (fabs(_angle)>0.01f)
    {
        wizVector2 center = _v1.add(_v2).add(_v3).mul(1/3.0f);
        rotate(start, vertices-1, center.getX(), center.getY(), _angle);
    }

    for (unsigned int i=0; i<3; i++)
    {
        colourBuffer[colours++] = _colour.getURed();
        colourBuffer[colours++] = _colour.getUGreen();
        colourBuffer[colours++] = _colour.getUBlue();
        colourBuffer[colours++] = _colour.getUAlpha();
    }

    indexBuffer[indices++] = start;
    indexBuffer[indices++] = start+1;
    indexBuffer[indices++] = start+2;
}

void wizPrimitives::batchPolygon(wizVector2* _v, unsigned int _vertices, wizColour _colour, float _angle)
{
    unsigned int start = vertices;

    for (unsigned int i=0; i<_vertices; i++)
    {
        vertexBuffer[vertices++] = _v[i].getX();
        vertexBuffer[vertices++] = _v[i].getY();
    }

    if (fabs(_angle)>0.01f)
    {
        float cx = 0;
        float cy = 0;
        for (unsigned int i=0; i<_vertices; i+=2)
        {
            cx += vertexBuffer[i*2];
            cy += vertexBuffer[i*2+1];
        }
        cx /= _vertices;
        cy /= _vertices;
        rotate(start, vertices-1, cx, cy, _angle);
    }

    for (unsigned int i=0; i<_vertices-2; i++)
    {
        indexBuffer[indices++] = start + i*2;
        indexBuffer[indices++] = start + i*2+1;
        indexBuffer[indices++] = start + i*2+2;
    }

    for (unsigned int i=0; i<_vertices; i++)
    {
        colourBuffer[colours++] = _colour.getURed();
        colourBuffer[colours++] = _colour.getUGreen();
        colourBuffer[colours++] = _colour.getUBlue();
        colourBuffer[colours++] = _colour.getUAlpha();
    }
}

void wizPrimitives::flush()
{
    glVertexPointer(2, GL_FLOAT, 0, vertexBuffer);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
    glDrawElements(GL_TRIANGLES, indices, GL_UNSIGNED_SHORT, indexBuffer);

    if (!locked)
    {
        vertices=0;
        indices=0;
        colours=0;
    }
}

void wizPrimitives::enableBlending(unsigned int _src, unsigned int _dst)
{
    glEnable(GL_BLEND);
    glBlendFunc(_src, _dst);
}

void wizPrimitives::disableBlending()
{
    glDisable(GL_BLEND);
}
