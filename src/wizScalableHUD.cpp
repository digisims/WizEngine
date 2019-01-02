#include "wizScalableHUD.h"

std::map<std::string, std::vector<wizSpriteEntity*> > wizScalableHUD::map;
std::vector<wizSpriteEntity*> wizScalableHUD::list;
bool wizScalableHUD::locked=false;

void wizScalableHUD::render(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, wizSpriteRenderer* _renderer)
{
    std::string id = _sheet + "_" + _sprite + "_" + _animation + "_" + wizUtility::intToString(_frame) + "_" + wizUtility::intToString(_x) + "_" + wizUtility::intToString(_y) + "_" + wizUtility::intToString(_w) + "_" + wizUtility::intToString(_h);

    if (map.find(id)!=map.end())
    {
        _renderer->renderSpriteList(map[id]);
    }
    else
    {
        std::vector<wizSpriteEntity*> tmp;

        for (unsigned int i=0; i<9; i++)
        {
            wizSpriteEntity* entity = new wizSpriteEntity();

            entity->setSheet(_sheet);
            entity->setSprite(_sprite + wizUtility::intToString((int)i));
            entity->setAnimation(_animation);
            entity->setFrame(_frame);
            entity->initialize();

            tmp.push_back(entity);
        }

        //top-left
        tmp[0]->setPosition(wizVector2(0, 0));
        //top-middle
        tmp[1]->setPosition(wizVector2(tmp[0]->getPosition().getX() + tmp[0]->getSize().getX(), 0));
        tmp[1]->setSize(wizVector2(_w - tmp[0]->getSize().getX() - tmp[2]->getSize().getX(), tmp[1]->getSize().getY()));
        //top-right
        tmp[2]->setPosition(wizVector2(tmp[1]->getPosition().getX() + tmp[1]->getSize().getX(), 0));

        //middle-left
        tmp[3]->setPosition(wizVector2(0, tmp[0]->getSize().getY()));
        tmp[3]->setSize(wizVector2(tmp[3]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[6]->getSize().getY()));
        //middle-middle
        tmp[4]->setPosition(wizVector2(tmp[3]->getPosition().getX() + tmp[3]->getSize().getX(), tmp[1]->getSize().getY()));
        tmp[4]->setSize(wizVector2(_w - tmp[0]->getSize().getX() - tmp[2]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[6]->getSize().getY()));
        //middle-right
        tmp[5]->setPosition(wizVector2(_w - tmp[5]->getSize().getX(), tmp[0]->getSize().getY()));
        tmp[5]->setSize(wizVector2(tmp[5]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[8]->getSize().getY()));

        //bottom-left
        tmp[6]->setPosition(wizVector2(0, _h - tmp[6]->getSize().getY()));
        //bottom-middle
        tmp[7]->setPosition(wizVector2(tmp[6]->getPosition().getX() + tmp[6]->getSize().getX(), _h - tmp[7]->getSize().getY()));
        tmp[7]->setSize(wizVector2(_w - tmp[6]->getSize().getX() - tmp[8]->getSize().getX(), tmp[7]->getSize().getY()));
        //bottom-right
        tmp[8]->setPosition(wizVector2(tmp[7]->getPosition().getX() + tmp[7]->getSize().getX(), _h - tmp[8]->getSize().getY()));

        for (unsigned int i=0; i<9; i++)
        {
            tmp[i]->setPosition(tmp[i]->getPosition().add(wizVector2(_x, _y)));
            tmp[i]->extract();
            tmp[i]->setPosition(wizVector2(0, 0));
            tmp[i]->setAngle(0);
            tmp[i]->setAlpha(_a);
        }

        map[id] = tmp;

        _renderer->renderSpriteList(map[id]);
    }
}

void wizScalableHUD::batch(std::string _sheet, std::string _sprite, std::string _animation, unsigned int _frame, int _x, int _y, int _w, int _h, float _a, wizSpriteRenderer* _renderer)
{
    if (locked) return;

    std::string id = _sheet + "_" + _sprite + "_" + _animation + "_" + wizUtility::intToString(_frame) + "_" + wizUtility::intToString(_x) + "_" + wizUtility::intToString(_y) + "_" + wizUtility::intToString(_w) + "_" + wizUtility::intToString(_h);

    if (map.find(id)!=map.end())
    {
        for (unsigned int i=0; i<map[id].size(); i++)
        {
            list.push_back(map[id][i]);
        }
    }
    else
    {
        std::vector<wizSpriteEntity*> tmp;

        for (unsigned int i=0; i<9; i++)
        {
            wizSpriteEntity* entity = new wizSpriteEntity();

            entity->setSheet(_sheet);
            entity->setSprite(_sprite + wizUtility::intToString((int)i));
            entity->setAnimation(_animation);
            entity->setFrame(_frame);
            entity->initialize();

            tmp.push_back(entity);
        }

        //top-left
        tmp[0]->setPosition(wizVector2(0, 0));
        //top-middle
        tmp[1]->setPosition(wizVector2(tmp[0]->getPosition().getX() + tmp[0]->getSize().getX(), 0));
        tmp[1]->setSize(wizVector2(_w - tmp[0]->getSize().getX() - tmp[2]->getSize().getX(), tmp[1]->getSize().getY()));
        //top-right
        tmp[2]->setPosition(wizVector2(tmp[1]->getPosition().getX() + tmp[1]->getSize().getX(), 0));

        //middle-left
        tmp[3]->setPosition(wizVector2(0, tmp[0]->getSize().getY()));
        tmp[3]->setSize(wizVector2(tmp[3]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[6]->getSize().getY()));
        //middle-middle
        tmp[4]->setPosition(wizVector2(tmp[3]->getPosition().getX() + tmp[3]->getSize().getX(), tmp[1]->getSize().getY()));
        tmp[4]->setSize(wizVector2(_w - tmp[0]->getSize().getX() - tmp[2]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[6]->getSize().getY()));
        //middle-right
        tmp[5]->setPosition(wizVector2(_w - tmp[5]->getSize().getX(), tmp[0]->getSize().getY()));
        tmp[5]->setSize(wizVector2(tmp[5]->getSize().getX(), _h - tmp[0]->getSize().getY() - tmp[8]->getSize().getY()));

        //bottom-left
        tmp[6]->setPosition(wizVector2(0, _h - tmp[6]->getSize().getY()));
        //bottom-middle
        tmp[7]->setPosition(wizVector2(tmp[6]->getPosition().getX() + tmp[6]->getSize().getX(), _h - tmp[7]->getSize().getY()));
        tmp[7]->setSize(wizVector2(_w - tmp[6]->getSize().getX() - tmp[8]->getSize().getX(), tmp[7]->getSize().getY()));
        //bottom-right
        tmp[8]->setPosition(wizVector2(tmp[7]->getPosition().getX() + tmp[7]->getSize().getX(), _h - tmp[8]->getSize().getY()));

        for (unsigned int i=0; i<9; i++)
        {
            tmp[i]->setPosition(tmp[i]->getPosition().add(wizVector2(_x, _y)));
            tmp[i]->extract();
            tmp[i]->setPosition(wizVector2(0, 0));
            tmp[i]->setAngle(0);
            tmp[i]->setAlpha(_a);
        }

        map[id] = tmp;

        for (unsigned int i=0; i<map[id].size(); i++)
        {
            list.push_back(map[id][i]);
        }
    }
}

void wizScalableHUD::flush(wizSpriteRenderer* _renderer)
{
    _renderer->renderSpriteList(list);
    if (!locked)
    {
        list.clear();
    }
}

void wizScalableHUD::lock()
{
    locked = true;
}

void wizScalableHUD::unlock()
{
    locked = false;
    list.clear();
}
