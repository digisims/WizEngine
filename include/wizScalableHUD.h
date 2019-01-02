#ifndef WIZSCALABLEHUD_H
#define WIZSCALABLEHUD_H

#include "wizSpriteEntity.h"
#include "wizSpriteRenderer.h"
#include "wizUtility.h"

#include <map>
#include <vector>
#include <string>

class wizScalableHUD
{
    public:

    static void render(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, wizSpriteRenderer* _renderer);
    static void batch(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, wizSpriteRenderer* _renderer);
    static void lock();
    static void unlock();
    static void flush(wizSpriteRenderer* _renderer);

    protected:

    static std::map<std::string, std::vector<wizSpriteEntity*> > map;
    static std::vector<wizSpriteEntity*> list;
    static bool locked;
};

#endif // WIZSCALABLEHUD_H
