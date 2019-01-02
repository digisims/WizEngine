#ifndef WIZPROGRESSBAR_H
#define WIZPROGRESSBAR_H

#include "wizVector2.h"
#include "wizSpriteEntity.h"
#include "wizSpriteRenderer.h"

class wizProgressBar
{
    public:

    wizProgressBar(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, float _spd);
    ~wizProgressBar();

    void setProgress(float _progress);
    float getProgress();

    void render(wizSpriteRenderer* _renderer);
    void update(float _delta);

    protected:

    int x;
    int y;
    int w;
    int h;
    float animationSpeed;
    float tx;
    float progress;
    wizSpriteEntity* entity;
};

#endif // WIZPROGRESSBAR_H
