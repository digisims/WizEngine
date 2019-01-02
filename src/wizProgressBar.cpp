#include "wizProgressBar.h"

wizProgressBar::wizProgressBar(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, float _spd)
{
    entity = new wizSpriteEntity();

    animationSpeed = _spd;
    tx = 0;
    x = _x;
    y = _y;
    w = _w;
    h = _h;

    entity->setSheet(_sheet);
    entity->setSprite(_sprite);
    entity->setAnimation(_animation);
    entity->setFrame(_frame);
    entity->setAlpha(_a);
    entity->initialize();

    setProgress(0);
}

wizProgressBar::~wizProgressBar()
{
    if (entity!=NULL)
    {
        delete entity;
    }
}

void wizProgressBar::render(wizSpriteRenderer* _renderer)
{
    _renderer->renderSpriteEntity(entity);
}

void wizProgressBar::update(float _delta)
{
    tx += animationSpeed * _delta;
}

void wizProgressBar::setProgress(float _progress)
{
    wizSpriteFrame* frameObject = entity->getFrameObject();
    wizVector2 size = frameObject->getActualSize();

    progress = _progress;

    float scaledWidth = w * progress;

    entity->getVertexBuffer()[0] = (short)x;
    entity->getVertexBuffer()[1] = (short)y;
    entity->getVertexBuffer()[2] = (short)(x + scaledWidth);
    entity->getVertexBuffer()[3] = (short)y;
    entity->getVertexBuffer()[4] = (short)(x + scaledWidth);
    entity->getVertexBuffer()[5] = (short)(y + h);

    entity->getVertexBuffer()[6] = (short)(x + scaledWidth);
    entity->getVertexBuffer()[7] = (short)(y + h);
    entity->getVertexBuffer()[8] = (short)x;
    entity->getVertexBuffer()[9] = (short)(y + h);
    entity->getVertexBuffer()[10] = (short)x;
    entity->getVertexBuffer()[11] = (short)y;

    entity->getTextureBuffer()[0] = tx;
    entity->getTextureBuffer()[1] = 0;
    entity->getTextureBuffer()[2] = tx + scaledWidth / size.getX();
    entity->getTextureBuffer()[3] = 0;
    entity->getTextureBuffer()[4] = tx + scaledWidth / size.getX();
    entity->getTextureBuffer()[5] = 1;

    entity->getTextureBuffer()[6] = tx + scaledWidth / size.getX();
    entity->getTextureBuffer()[7] = 1;
    entity->getTextureBuffer()[8] = tx;
    entity->getTextureBuffer()[9] = 1;
    entity->getTextureBuffer()[10] = tx;
    entity->getTextureBuffer()[11] = 0;

    entity->transform(true);
}

float wizProgressBar::getProgress()
{
    return progress;
}
