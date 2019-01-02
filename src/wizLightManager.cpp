#include "wizLightManager.h"

std::vector<wizLight*> wizLightManager::lightList;
std::vector<unsigned int> wizLightManager::order;

void wizLightManager::initialize()
{
}

void wizLightManager::destroy()
{
    for (unsigned int i=0; i<lightList.size(); i++)
    {
        delete lightList[i];
    }
}

void wizLightManager::applyGlobalSettings()
{
    if (lightList.size()>0)
    {
        glEnable(GL_LIGHTING);
        glShadeModel(GL_SMOOTH);
    }
}

void wizLightManager::undoGlobalSettings()
{
    if (lightList.size()>0)
    {
        glDisable(GL_LIGHTING);
    }
}

std::string wizLightManager::applySettings(wizVector3 _position)
{
    if (lightList.size()==0) return "";

    order.clear();
    std::vector<float> distance;

    for (unsigned int i=0; i<lightList.size(); i++)
    {
        float d = _position.sub(*lightList[i]->getPosition()).length();

        order.push_back(distance.size());
        distance.push_back(d);
    }

    for (unsigned int i=0; i<distance.size(); i++)
    {
        for (unsigned int j=i+1; j<distance.size(); j++)
        {
            if (distance[order[j]]<distance[order[i]])
            {
                unsigned int tmp = order[j];
                order[j] = order[i];
                order[i] = tmp;
            }
        }
    }

    std::string id = "";

    for (unsigned int j=0; j<(unsigned int)wizUtility::min(wizLightManager::MAX_LIGHTS, distance.size()); j++)
    {
        lightList[order[j]]->setIndex(j);
        lightList[order[j]]->applySettings();
        id += wizUtility::intToString(order[j]);
    }

    return id;
}

void wizLightManager::undoSettings()
{
    if (lightList.size()==0) return;

    for (unsigned int j=0; j<(unsigned int)wizUtility::min(wizLightManager::MAX_LIGHTS, order.size()); j++)
    {
        lightList[order[j]]->undoSettings();
    }
}

void wizLightManager::addLight(wizLight* _light)
{
    lightList.push_back(_light);
}

wizLight* wizLightManager::getLight(unsigned int _idx)
{
    return lightList[_idx];
}

void wizLightManager::removeLight(unsigned int _idx)
{
    lightList.erase(lightList.begin()+_idx);
}

unsigned int wizLightManager::getLights()
{
    return lightList.size();
}
