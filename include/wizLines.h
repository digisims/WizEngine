#ifndef WIZLINES_H
#define WIZLINES_H

class wizLines
{
    public:

    wizLines();
    wizLines(unsigned int _cache);
    virtual ~wizLines();

    void applyGlobalSettings();
    void undoGlobalSettings();

    void drawLine(wizVector2 _start, wizVector2 _end, wizColour _colour, float _angle = 0);

    void batchLine(wizVector2 _start, wizVector2 _end, wizColour _colour, float _angle = 0);

    void lock();
    void unlock();
    void flush();

    void enableBlending(unsigned int _src, unsigned int _dst);
    void disableBlending();

    protected:

    void rotate(unsigned int _start, unsigned int _stop, float _x, float _y, float _angle);

    GLfloat* vertexBuffer;
    GLubyte* colourBuffer;
    unsigned int vertices;
    unsigned int colours;
    bool locked;
};

#endif // WIZLINES_H
