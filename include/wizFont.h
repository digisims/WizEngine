#ifndef WIZFONT_H
#define WIZFONT_H

#include "wizTextureManager.h"
#include "wizVector2.h"
#include "wizUtility.h"
#include "wizGame.h"

#include <string>
#include <vector>
#include <fstream>

class wizFont
{
    public:

    wizFont(std::string _texture, std::string _data);
    virtual ~wizFont();

    void renderText(std::string _text, GLshort _x, GLshort _y);
    void renderScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h);
    void batchText(std::string _text, GLshort _x, GLshort _y);
    void batchScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h);
    void renderText(std::string _text, float _x, float _y);
    void renderScaledText(std::string _text, float _x, float _y, float _w, float _h);
    void batchText(std::string _text, float _x, float _y);
    void batchScaledText(std::string _text, float _x, float _y, float _w, float _h);
    void flush();
    wizVector2 measureText(std::string _text);
    wizVector2 measureScaledText(std::string _text, GLshort _w, GLshort _h);
    wizVector2 measureScaledText(std::string _text, float _w, float _h);
    void setGap(int _gap);

    void setFastRender(bool _fast);

    void applySettings();
    void undoSettings();
    void lock();
    void unlock();

    protected:

    void initialize();
    void _batchText(std::string _text, GLshort _x, GLshort _y);
    void _batchScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h);

    int gap;
    bool fast;
    int width;
    int height;
    wizVector2 maxDim;
    std::string texture;
    std::vector<GLfloat*> textureBuffer;
    std::vector<GLshort*> dims;
    std::vector<std::string> currentList;
    std::vector<wizVector2> currentListPosition;
    std::vector<wizVector2> currentListScale;
    std::vector<std::string> lastList;
    std::vector<wizVector2> lastListPosition;
    std::vector<wizVector2> lastListScale;
    GLuint vboVertexBuffer;
    GLuint vboTextureBuffer;
    GLshort* batchVertexBuffer;
    GLfloat* batchTextureBuffer;
    GLshort* immediateVertexBuffer;
    GLfloat* immediateTextureBuffer;
    unsigned int count1;
    unsigned int count2;
    bool locked;
};

#endif // WIZFONT_H
