#include "wizFont.h"
#include <fstream>
#include <iostream>

wizFont::wizFont(std::string _texture, std::string _data)
{
    vboVertexBuffer=0;
    vboTextureBuffer=0;

    gap = 2;
    fast = true;
    texture = _texture;

    wizTextureManager::loadTexture(texture);

    std::ifstream inp(_data.c_str());
    std::string line;

    inp >> width;
    inp >> height;

    for (unsigned int i=0; i<256; i++)
    {
        dims.push_back(new GLshort[2]);
    }

    for (unsigned int i=0; i<256; i++)
    {
        inp >> line;

        std::cout << line;

        std::vector<std::string> tokens = wizUtility::splitString(line, '=');
        std::vector<std::string> tokens2 = wizUtility::splitString(tokens[1], ';');

        int idx = atoi(tokens[0].c_str());
        int w = atoi(tokens2[0].c_str());
        int h = atoi(tokens2[1].c_str());

        dims[idx][0] = w;
        dims[idx][1] = h;
    }

    inp.close();

    initialize();
}

wizFont::~wizFont()
{
    if (immediateVertexBuffer!=NULL) delete[] immediateVertexBuffer;
    if (immediateTextureBuffer!=NULL) delete[] immediateTextureBuffer;
    if (batchVertexBuffer!=NULL) delete[] batchVertexBuffer;
    if (batchTextureBuffer!=NULL) delete[] batchTextureBuffer;

    for (unsigned int i=0; i<textureBuffer.size(); i++)
    {
        if (textureBuffer[i]!=NULL) delete[] textureBuffer[i];
    }

    for (unsigned int i=0; i<dims.size(); i++)
    {
        delete[] dims[i];
    }
}

void wizFont::setGap(int _gap)
{
    gap = _gap;
}

void wizFont::initialize()
{
    maxDim.setX(-1);
    maxDim.setY(-1);

    for (unsigned int i=0; i<dims.size(); i++)
    {
        if (dims[i][0]>maxDim.getX())
        {
            maxDim.setX(dims[i][0]);
        }

        if (dims[i][1]>maxDim.getY())
        {
            maxDim.setY(dims[i][1]);
        }
    }

    for (unsigned int i=0; i<256; i++)
    {
        int x1 = i % 16;
        int y1 = i / 16;
        float tx1 = x1 / 16.0f;
        float ty1 = y1 / 16.0f;
        float tx2 = tx1 + dims[i][0] / (float)width;
        float ty2 = ty1 + dims[i][1] / (float)height;

        GLfloat* tmpBuffer = new GLfloat[6 * 2];

        tmpBuffer[0] = tx1;
        tmpBuffer[1] = ty1;
        tmpBuffer[2] = tx2;
        tmpBuffer[3] = ty1;
        tmpBuffer[4] = tx2;
        tmpBuffer[5] = ty2;

        tmpBuffer[6] = tx2;
        tmpBuffer[7] = ty2;
        tmpBuffer[8] = tx1;
        tmpBuffer[9] = ty2;
        tmpBuffer[10] = tx1;
        tmpBuffer[11] = ty1;

        textureBuffer.push_back(tmpBuffer);
    }

    batchVertexBuffer = new GLshort[1024 * 6];
    batchTextureBuffer = new GLfloat[1024 * 6];
    immediateVertexBuffer = new GLshort[1024 * 6];
    immediateTextureBuffer = new GLfloat[1024 * 6];
}

void wizFont::setFastRender(bool _fast)
{
    fast = _fast;
}

void wizFont::applySettings()
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    if (fast)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);//GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    else
    {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
    }
    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, wizTextureManager::getTexture(texture));
	glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void wizFont::undoSettings()
{
    #ifndef WIN32
    glActiveTexture(GL_TEXTURE0);
    glClientActiveTexture(GL_TEXTURE0);
    #endif
    glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if (fast)
    {
        glDisable(GL_BLEND);
    }
    else
    {
        glDisable(GL_ALPHA_TEST);
    }
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

void wizFont::renderText(std::string _text, GLshort _x, GLshort _y)
{
    unsigned int icount1 = 0;
    unsigned int icount2 = 0;

    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = _y;
        immediateVertexBuffer[icount1++] = (_x + dims[idx][0]);
        immediateVertexBuffer[icount1++] = _y;
        immediateVertexBuffer[icount1++] = (_x + dims[idx][0]);
        immediateVertexBuffer[icount1++] = (_y + dims[idx][1]);

        immediateVertexBuffer[icount1++] = (_x + dims[idx][0]);
        immediateVertexBuffer[icount1++] = (_y + dims[idx][1]);
        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = (_y + dims[idx][1]);
        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = _y;

        memcpy((char*)&immediateTextureBuffer[icount2], textureBuffer[idx], 6 * 2 * sizeof(GLfloat));
        icount2 += 12;

        _x += dims[idx][0] + gap;
    }

    glVertexPointer(2, GL_SHORT, 0, immediateVertexBuffer);
    glTexCoordPointer(2, GL_FLOAT, 0, immediateTextureBuffer);
    glDrawArrays(GL_TRIANGLES, 0, _text.length() * 6);
}

void wizFont::renderScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h)
{
    unsigned int icount1 = 0;
    unsigned int icount2 = 0;

    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = _y;
        immediateVertexBuffer[icount1++] = (_x + _w);
        immediateVertexBuffer[icount1++] = _y;
        immediateVertexBuffer[icount1++] = (_x + _w);
        immediateVertexBuffer[icount1++] = (_y + _h);

        immediateVertexBuffer[icount1++] = (_x + _w);
        immediateVertexBuffer[icount1++] = (_y + _h);
        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = (_y + _h);
        immediateVertexBuffer[icount1++] = _x;
        immediateVertexBuffer[icount1++] = _y;

        memcpy((char*)&immediateTextureBuffer[icount2], textureBuffer[idx], 6 * 2 * sizeof(GLfloat));
        icount2 += 12;

        _x += (GLshort)(dims[idx][0] * (_w / maxDim.getX()) + gap * (_w / maxDim.getX()));
    }

    glVertexPointer(2, GL_SHORT, 0, immediateVertexBuffer);
    glTexCoordPointer(2, GL_FLOAT, 0, immediateTextureBuffer);
    glDrawArrays(GL_TRIANGLES, 0, _text.length() * 6);
}

void wizFont::flush()
{
    bool same = locked || currentList.size() == lastList.size();

    if (!locked && same)
    {
        for (unsigned int i=0; i<currentList.size(); i++)
        {
            if (lastList[i].compare(currentList[i])!=0 || !lastListPosition[i].equals(currentListPosition[i]) || !lastListScale[i].equals(currentListScale[i]))
            {
                same = false;
                break;
            }
        }
    }

    if (!same)
    {
        count1 = 0;
        count2 = 0;

        for (unsigned int i=0; i<currentList.size(); i++)
        {
            if (currentListScale[i].getX()>-1 && currentListScale[i].getY()>-1)
            {
                _batchScaledText(currentList[i], (short)currentListPosition[i].getX(), (short)currentListPosition[i].getY(), (short)currentListScale[i].getX(), (short)currentListScale[i].getY());
            }
            else
            {
                _batchText(currentList[i], (short)currentListPosition[i].getX(), (short)currentListPosition[i].getY());
            }
        }
    }

    if (locked)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboVertexBuffer);
        glVertexPointer(2, GL_SHORT, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, vboTextureBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, NULL);
        glDrawArrays(GL_TRIANGLES, 0, count1 / 2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        glVertexPointer(2, GL_SHORT, 0, batchVertexBuffer);
        glTexCoordPointer(2, GL_FLOAT, 0, batchTextureBuffer);
        glDrawArrays(GL_TRIANGLES, 0, count1 / 2);
    }

    if (!locked)
    {
        lastList = currentList;
        lastListPosition = currentListPosition;
        lastListScale = currentListScale;

        currentList.clear();
        currentListPosition.clear();
        currentListScale.clear();
    }
}

void wizFont::batchText(std::string _text, GLshort _x, GLshort _y)
{
    if (locked) return;

    currentList.push_back(_text);
    currentListPosition.push_back(wizVector2(_x, _y));
    currentListScale.push_back(wizVector2(-1, -1));
}

void wizFont::_batchText(std::string _text, GLshort _x, GLshort _y)
{
    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = _y;
        batchVertexBuffer[count1++] = (_x + dims[idx][0]);
        batchVertexBuffer[count1++] = _y;
        batchVertexBuffer[count1++] = (_x + dims[idx][0]);
        batchVertexBuffer[count1++] = (_y + dims[idx][1]);

        batchVertexBuffer[count1++] = (_x + dims[idx][0]);
        batchVertexBuffer[count1++] = (_y + dims[idx][1]);
        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = (_y + dims[idx][1]);
        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = _y;

        memcpy((char*)&batchTextureBuffer[count2], textureBuffer[idx], 6 * 2 * sizeof(GLfloat));
        count2 += 12;

        _x += (int)dims[idx][0] + gap;
    }
}

void wizFont::batchScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h)
{
    if (locked) return;

    currentList.push_back(_text);
    currentListPosition.push_back(wizVector2(_x, _y));
    currentListScale.push_back(wizVector2(_w, _h));
}

void wizFont::_batchScaledText(std::string _text, GLshort _x, GLshort _y, GLshort _w, GLshort _h)
{
    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = _y;
        batchVertexBuffer[count1++] = (_x + _w);
        batchVertexBuffer[count1++] = _y;
        batchVertexBuffer[count1++] = (_x + _w);
        batchVertexBuffer[count1++] = (_y + _h);

        batchVertexBuffer[count1++] = (_x + _w);
        batchVertexBuffer[count1++] = (_y + _h);
        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = (_y + _h);
        batchVertexBuffer[count1++] = _x;
        batchVertexBuffer[count1++] = _y;

        memcpy((char*)&batchTextureBuffer[count2], textureBuffer[idx], 6 * 2 * sizeof(GLfloat));
        count2 += 12;

        _x += (GLshort)(dims[idx][0] * (_w / maxDim.getX()) + gap * (_w / maxDim.getX()));
    }
}

wizVector2 wizFont::measureText(std::string _text)
{
    int w = 0;
    int h = (int)dims[0][1];

    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        w += dims[idx][0] + gap;
    }

    return wizVector2(w, h);
}

wizVector2 wizFont::measureScaledText(std::string _text, GLshort _w, GLshort _h)
{
    int w = 0;

    for (unsigned int i=0; i<_text.length(); i++)
    {
        int idx = (int)_text[i];

        w += (int)(dims[idx][0] * (_w / maxDim.getX()) + gap * (_w / maxDim.getX()));
    }

    return wizVector2(w, _h);
}

void wizFont::renderText(std::string _text, float _x, float _y)
{
    renderText(_text, (short)_x, (short)_y);
}

void wizFont::renderScaledText(std::string _text, float _x, float _y, float _w, float _h)
{
    renderScaledText(_text, (short)_x, (short)_y, (short)_w, (short)_h);
}

void wizFont::batchText(std::string _text, float _x, float _y)
{
    batchText(_text, (short)_x, (short)_y);
}

void wizFont::batchScaledText(std::string _text, float _x, float _y, float _w, float _h)
{
    batchScaledText(_text, (short)_x, (short)_y, (short)_w, (short)_h);
}

wizVector2 wizFont::measureScaledText(std::string _text, float _w, float _h)
{
    return measureScaledText(_text, (short)_w, (short)_h);
}

void wizFont::lock()
{
    if (vboVertexBuffer==0)
    {
        glGenBuffers(1, &vboVertexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboVertexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count1 * sizeof(GLushort), batchVertexBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if (vboTextureBuffer==0)
    {
        glGenBuffers(1, &vboTextureBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboTextureBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count1 * sizeof(GLfloat), batchTextureBuffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    locked = true;
}

void wizFont::unlock()
{
    glDeleteBuffers(1, &vboVertexBuffer);
    glDeleteBuffers(1, &vboTextureBuffer);

    vboVertexBuffer=0;
    vboTextureBuffer=0;

    locked = false;
}
