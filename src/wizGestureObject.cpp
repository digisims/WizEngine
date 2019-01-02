#include "wizGestureObject.h"

wizGestureObject::wizGestureObject(std::string _pattern)
{
    setPattern(_pattern);
}

void wizGestureObject::setPattern(std::string _pattern)
{
    pattern = _pattern;
}

std::string wizGestureObject::getPattern()
{
    return pattern;
}

int wizGestureObject::calculateScore(std::string _pattern)
{
    int** dist = new int*[pattern.length()+1];

    for (unsigned int i=0; i<pattern.length()+1; i++)
    {
        dist[i] = new int[_pattern.length()+1];
    }

    for (unsigned int i = 0; i <= pattern.length(); i++)
    {
        dist[i][0] = i;
    }

    for (unsigned int i = 0; i <= _pattern.length(); i++)
    {
        dist[0][i] = i;
    }

    for (unsigned int j = 1; j <= _pattern.length(); j++)
    {
        for (unsigned int i = 1; i <= pattern.length(); i++)
        {
            if (pattern[i] == _pattern[j])
            {
                dist[i][j] = dist[i - 1][j - 1];
            }
            else
            {
                dist[i][j] = wizUtility::wizUtility::min(wizUtility::wizUtility::min(dist[i - 1][j] + 1, dist[i][j - 1] + 1), dist[i - 1][j - 1] + 1);
            }
        }
    }

    int score = dist[pattern.length()][_pattern.length()];

    for (unsigned int i=0; i<pattern.length()+1; i++)
    {
        delete[] dist[i];
    }

    return score;
}
