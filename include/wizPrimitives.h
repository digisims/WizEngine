#ifndef WIZPRIMITIVES_H
#define WIZPRIMITIVES_H

#include "wizVector2.h"
#include "wizColour.h"

class wizPrimitives
{
    public:

    wizPrimitives();
    wizPrimitives(unsigned int _cache);
    virtual ~wizPrimitives();

    void applyGlobalSettings();
    void undoGlobalSettings();

    void drawRectangle(wizVector2 _position, wizVector2 _size, wizColour _colour, float _angle = 0);
    void drawTriangle(wizVector2 _v1, wizVector2 _v2, wizVector2 _v3, wizColour _colour, float _angle = 0);
    void drawNGon(wizVector2 _position, wizVector2 _size, wizColour _colour, unsigned int _detail, float _angle = 0);
    void drawPolygon(wizVector2* _v, unsigned int _vertices, wizColour _colour, float _angle = 0);

    void batchRectangle(wizVector2 _position, wizVector2 _size, wizColour _colour, float _angle = 0);
    void batchTriangle(wizVector2 _v1, wizVector2 _v2, wizVector2 _v3, wizColour _colour, float _angle = 0);
    void batchNGon(wizVector2 _position, wizVector2 _size, wizColour _colour, unsigned int _detail, float _angle = 0);
    void batchPolygon(wizVector2* _v, unsigned int _vertices, wizColour _colour, float _angle = 0);

    void lock();
    void unlock();
    void flush();

    void enableBlending(unsigned int _src, unsigned int _dst);
    void disableBlending();

    protected:

    void rotate(unsigned int _start, unsigned int _stop, float _x, float _y, float _angle);

    GLushort* indexBuffer;
    GLfloat* vertexBuffer;
    GLubyte* colourBuffer;
    unsigned int indices;
    unsigned int vertices;
    unsigned int colours;
    bool locked;
};

#endif // WIZPRIMITIVES_H
