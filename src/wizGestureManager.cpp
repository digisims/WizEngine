#include "wizGestureManager.h"

wizVector2 wizGestureManager::start;
wizVector2 wizGestureManager::stop;
bool wizGestureManager::capturing;
bool wizGestureManager::matched;
wizGestureObject* wizGestureManager::matchedGesture;
std::vector<wizVector2> wizGestureManager::history;
std::map<std::string, wizGestureObject*> wizGestureManager::gestureMap;

void wizGestureManager::initialize()
{
    capturing = false;
    matched = false;

    history.clear();
}

void wizGestureManager::destroy()
{
    std::map<std::string, wizGestureObject*>::iterator i;

    for (i = gestureMap.begin(); i!=gestureMap.end(); i++)
    {
        delete i->second;
    }
}

wizGestureObject* wizGestureManager::getGesture(std::string _id)
{
    if (gestureMap.find(_id) != gestureMap.end())
    {
        return gestureMap[_id];
    }

    return NULL;
}

void wizGestureManager::addGesture(std::string _id, wizGestureObject* _gesture)
{
    wizGestureObject* gesture = getGesture(_id);

    if (gesture==NULL)
    {
        gestureMap[_id] = _gesture;
    }
}

void wizGestureManager::removeGesture(std::string _id)
{
    wizGestureObject* gesture = getGesture(_id);

    if (gesture!=NULL)
    {
        gestureMap.erase(gestureMap.find(_id));
    }
}

void wizGestureManager::startCapture()
{
    matched = false;
    matchedGesture = NULL;
    capturing = true;
    history.clear();

    wizVector2 position = wizInputManager::getTouchPosition();

    start.setX(position.getX());
    start.setY(position.getY());
    stop.setX(position.getX());
    stop.setY(position.getY());
}

void wizGestureManager::stopCapture()
{
    capturing = false;
}

void wizGestureManager::update()
{
    if (wizInputManager::isClicked())
    {
        if (!capturing)
        {
            startCapture();
        }
        else
        {
            wizVector2 position = wizInputManager::getTouchPosition();

            history.push_back(wizVector2(position.getX(), position.getY()));

            if (position.getX() < start.getX()) start.setX(position.getX());
            if (position.getX() > start.getX()) start.setX(position.getX());
            if (position.getY() < stop.getY()) stop.setY(position.getY());
            if (position.getY() > stop.getY()) stop.setY(position.getY());
        }
    }
    else
    {
        if (capturing)
        {
            stopCapture();
            match();
        }
    }
}

void wizGestureManager::match()
{
    matched = false;

    int w = (int)(stop.getX() - start.getX() + 1);
    int h = (int)(stop.getY() - start.getY() + 1);
    int cw = w / 3;
    int ch = h / 3;

    std::string string = "";
    int last = -1;

    for (unsigned int i=0; i<history.size(); i++)
    {
        int x = (int)(history[i].getX() - start.getX()) / cw;
        if (x<0) x = 0;
        if (x>2) x = 2;

        int y = (int)(history[i].getY() - start.getY()) / ch;
        if (y<0) y = 0;
        if (y>2) y = 2;

        int cell = x + y * 3;

        if (last != cell)
        {
            string += (char)('0' + cell);
        }
    }

    int min = 32768;
    matchedGesture = NULL;

    std::map<std::string, wizGestureObject*>::iterator i;

    for (i = gestureMap.begin(); i!=gestureMap.end(); i++)
    {
        int score = i->second->calculateScore(string);

        if (score < min)
        {
            min = score;
            matchedGesture = i->second;
        }
    }
}

bool wizGestureManager::wasMatched()
{
    return matched;
}

wizGestureObject* wizGestureManager::getMatchedGesture()
{
    return matchedGesture;
}
