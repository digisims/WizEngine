#ifndef WIZBLOB_H
#define WIZBLOB_H

#include "wizVector3.h"
#include "wizTextureManager.h"

#include <string>

class wizBlob
{
    public:

    wizBlob(std::string _texture, wizVector3 _minimum, wizVector3 _maximum, float _minimumDistance, float _maximumDistance);
    virtual ~wizBlob();

    std::string getTexture();
    wizVector3 getMinimum();
    wizVector3 getMaximum();
    float getMinimumDistance();
    float getMaximumDistance();

    protected:

    float minimumDistance;
    float maximumDistance;
    std::string texture;
    wizVector3 minimum;
    wizVector3 maximum;
};

#endif // WIZBLOB_H
