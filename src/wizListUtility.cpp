#include "wizListUtility.h"

std::vector<wizGameEntity*> wizListUtility::difference(std::vector<wizGameEntity*>& _a, std::vector<wizGameEntity*>& _b)
{
    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<_a.size(); i++)
    {
        bool found = false;

        for (unsigned int j=0; j<_b.size(); j++)
        {
            if (_a[i] == _b[j])
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            list.push_back(_a[i]);
        }
    }

    return list;
}

std::vector<wizGameEntity*> wizListUtility::combine(std::vector<wizGameEntity*>& _a, std::vector<wizGameEntity*>& _b)
{
    std::vector<wizGameEntity*> list;

    for (unsigned int i=0; i<_a.size(); i++)
    {
        list.push_back(_a[i]);
    }

    for (unsigned int i=0; i<_b.size(); i++)
    {
        if (find(list.begin(), list.end(), _b[i])==list.end())
        {
            list.push_back(_b[i]);
        }
    }

    return list;
}
