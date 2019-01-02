#include "wizSpriteEntity.h"

wizSpriteEntity::wizSpriteEntity()
{
    angle = 0;
    size = wizVector2(-1, -1);
    position = wizVector2(0, 0);
    transformedVertexBuffer = new GLshort[6 * 2];
    vertexBuffer = new GLshort[6 * 2];
    textureBuffer = new GLfloat[6 * 2];
    colourBuffer = NULL;
    needUpdate = false;
}

wizSpriteEntity::~wizSpriteEntity()
{
    if (transformedVertexBuffer!=NULL) delete[] transformedVertexBuffer;
    if (vertexBuffer!=NULL) delete[] vertexBuffer;
    if (colourBuffer!=NULL) delete[] colourBuffer;
    if (textureBuffer!=NULL) delete[] textureBuffer;
}

std::string wizSpriteEntity::getID()
{
    return sheet + "_" + sprite + "_" + animation + "_" + wizUtility::intToString(frame) + "_" + (colourBuffer != NULL ? "1" : "0");
}

wizSpriteFrame* wizSpriteEntity::getFrameObject()
{
    return wizSpriteSheetManager::getSpriteSheet(sheet)->getSprite(sprite)->getAnimation(animation)->getFrame(frame);
}

void wizSpriteEntity::initialize()
{
    wizSpriteFrame* obj = getFrameObject();
    wizVector2 _position = obj->getPosition();
    wizVector2 _size = obj->getSize();
    wizVector2 _actualSize = obj->getActualSize();

    if (size.getX()<0 || size.getY()<0)
    {
        size = _actualSize;
    }

    vertexBuffer[0] = 0;
    vertexBuffer[1] = 0;
    vertexBuffer[2] = (short)size.getX();
    vertexBuffer[3] = 0;
    vertexBuffer[4] = (short)size.getX();
    vertexBuffer[5] = (short)size.getY();

    vertexBuffer[6] = (short)size.getX();
    vertexBuffer[7] = (short)size.getY();
    vertexBuffer[8] = 0;
    vertexBuffer[9] = (short)size.getY();
    vertexBuffer[10] = 0;
    vertexBuffer[11] = 0;

    textureBuffer[0] = _position.getX();
    textureBuffer[1] = _position.getY();
    textureBuffer[2] = _position.getX() + _size.getX();
    textureBuffer[3] = _position.getY();
    textureBuffer[4] = _position.getX() + _size.getX();
    textureBuffer[5] = _position.getY() + _size.getY();

    textureBuffer[6] = _position.getX() + _size.getX();
    textureBuffer[7] = _position.getY() + _size.getY();
    textureBuffer[8] = _position.getX();
    textureBuffer[9] = _position.getY() + _size.getY();
    textureBuffer[10] = _position.getX();
    textureBuffer[11] = _position.getY();

    extracted = false;
    transform();
}

void wizSpriteEntity::extract()
{
    wizSpriteFrame* obj = getFrameObject();
    wizVector2 _position = obj->getPosition();
    wizVector2 _size = obj->getSize();
    wizVector2 _actualSize = obj->getActualSize();

    if (size.getX()<0 || size.getY()<0)
    {
        size = _actualSize;
    }

    vertexBuffer[0] = (short)(position.getX() + 0);
    vertexBuffer[1] = (short)(position.getY() + 0);
    vertexBuffer[2] = (short)(position.getX() + size.getX());
    vertexBuffer[3] = (short)(position.getY() + 0);
    vertexBuffer[4] = (short)(position.getX() + size.getX());
    vertexBuffer[5] = (short)(position.getY() + size.getY());

    vertexBuffer[6] = (short)(position.getX() + size.getX());
    vertexBuffer[7] = (short)(position.getY() + size.getY());
    vertexBuffer[8] = (short)(position.getX() + 0);
    vertexBuffer[9] = (short)(position.getY() + size.getY());
    vertexBuffer[10] = (short)(position.getX() + 0);
    vertexBuffer[11] = (short)(position.getY() + 0);

    textureBuffer[0] = _position.getX();
    textureBuffer[1] = _position.getY();
    textureBuffer[2] = _position.getX() + _size.getX();
    textureBuffer[3] = _position.getY();
    textureBuffer[4] = _position.getX() + _size.getX();
    textureBuffer[5] = _position.getY() + _size.getY();

    textureBuffer[6] = _position.getX() + _size.getX();
    textureBuffer[7] = _position.getY() + _size.getY();
    textureBuffer[8] = _position.getX();
    textureBuffer[9] = _position.getY() + _size.getY();
    textureBuffer[10] = _position.getX();
    textureBuffer[11] = _position.getY();

    extracted = true;
    transform(true);
}

void wizSpriteEntity::setAngle(float _angle)
{
    angle = _angle;
}

void wizSpriteEntity::setSize(wizVector2 _size)
{
    size = _size;
    initialize();
    needUpdate = true;
}

void wizSpriteEntity::setPosition(wizVector2 _position)
{
    position = _position;
    needUpdate = true;
}

void wizSpriteEntity::transform(bool _copy)
{
    if (_copy)
    {
        for (unsigned int i=0; i<12; i++)
        {
            transformedVertexBuffer[i] = vertexBuffer[i];
        }
    }
    else
    {
        float cosf = cos(angle);
        float sinf = sin(angle);
        float hw = size.getX() / 2;
        float hh = size.getY() / 2;

        for (unsigned int i=0; i<12; i+=2)
        {
            float tx = vertexBuffer[i] - hw;
            float ty = vertexBuffer[i+1] - hh;

            transformedVertexBuffer[i] = (GLshort)(tx * cosf - ty * sinf + hw + position.getX());
            transformedVertexBuffer[i+1] = (GLshort)(ty * cosf + tx * sinf + hh + position.getY());
        }
    }

    needUpdate = true;
}

float wizSpriteEntity::getAngle()
{
    return angle;
}

wizVector2 wizSpriteEntity::getSize()
{
    return size;
}

wizVector2 wizSpriteEntity::getPosition()
{
    return position;
}

void wizSpriteEntity::update(float _dt)
{
    time += _dt;
    wizSpriteFrame* frameObject = getFrameObject();

    if (time >= frameObject->getTime())
    {
        time -= frameObject->getTime();
        frame++;
        wizSpriteAnimation* animationObject = wizSpriteSheetManager::getSpriteSheet(sheet)->getSprite(sprite)->getAnimation(animation);
        if (frame > animationObject->getFrameCount()-1)
        {
            frame = animationObject->getLoopable() ? 0 : animationObject->getFrameCount()-1;
        }
    }
}

void wizSpriteEntity::setAlpha(float _a)
{
    if (colourBuffer == NULL)
    {
        colourBuffer = new GLubyte[6 * 4];

        for (unsigned int i=0; i < 6 * 4; i++)
        {
            colourBuffer[i] = 255;
        }
    }

    for (unsigned int i=3; i<6*4; i+=4)
    {
        colourBuffer[i] = (unsigned byte)(_a * 255);
    }
}

void wizSpriteEntity::render()
{
    if (needUpdate && !extracted)
    {
        transform();
    }

	glVertexPointer(2, GL_SHORT, 0, transformedVertexBuffer);

    if (colourBuffer != NULL)
    {
        glColorPointer(4, GL_UNSIGNED_BYTE, 0, colourBuffer);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    if (textureBuffer != NULL)
    {
        glTexCoordPointer(2, GL_FLOAT, 0, textureBuffer);
    }

	glDrawArrays(GL_TRIANGLES, 0, 6);

    if (colourBuffer != NULL)
    {
        glDisable(GL_BLEND);
    }

    needUpdate = false;
}

void wizSpriteEntity::setSheet(std::string _sheet)
{
    sheet = _sheet;
}

void wizSpriteEntity::setSprite(std::string _sprite)
{
    sprite = _sprite;
}

void wizSpriteEntity::setAnimation(std::string _animation)
{
    animation = _animation;
}

void wizSpriteEntity::setFrame(int _frame)
{
    frame = _frame;
}

std::string wizSpriteEntity::getSheet()
{
    return sheet;
}

std::string wizSpriteEntity::getSprite()
{
    return sprite;
}

std::string wizSpriteEntity::getAnimation()
{
    return animation;
}

int wizSpriteEntity::getFrame()
{
    return frame;
}

void wizSpriteEntity::setVertexBuffer(GLshort* _vertexBuffer)
{
    vertexBuffer = _vertexBuffer;
}

void wizSpriteEntity::setTextureBuffer(GLfloat* _textureBuffer)
{
    textureBuffer = _textureBuffer;
}

void wizSpriteEntity::setColourBuffer(GLubyte* _colourBuffer)
{
    colourBuffer = _colourBuffer;
}

GLshort* wizSpriteEntity::getTransformedVertexBuffer()
{
    return transformedVertexBuffer;
}

GLshort* wizSpriteEntity::getVertexBuffer()
{
    return vertexBuffer;
}

GLfloat* wizSpriteEntity::getTextureBuffer()
{
    return textureBuffer;
}

GLubyte* wizSpriteEntity::getColourBuffer()
{
    return colourBuffer;
}

bool wizSpriteEntity::needsUpdate()
{
    return needUpdate;
}
