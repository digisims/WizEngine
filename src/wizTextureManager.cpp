#include "wizTextureManager.h"

std::map<std::string, GLuint> wizTextureManager::glMap;

void wizTextureManager::initialize()
{
}

void wizTextureManager::destroy()
{
    std::map<std::string, GLuint>::iterator j;

    for (j = glMap.begin(); j!=glMap.end(); j++)
    {
        glDeleteTextures(1, &j->second);
    }
}

int wizTextureManager::loadTexture(std::string _filename)
{
    if (glMap.find(_filename) != glMap.end())
    {
        return glMap[_filename];
    }

    if (_filename.find(".ktx")==std::string::npos)
    {
        SDL_Surface* texture = IMG_Load(_filename.c_str());
        int tex_width = texture->w;
        int tex_height = texture->h;

        glMap[_filename] = 0;

        glGenTextures(1, &glMap[_filename]);
        glBindTexture(GL_TEXTURE_2D, glMap[_filename]);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        GLenum internal_format = GL_RGB;
        GLenum img_format = GL_RGB;
        GLenum img_type = GL_UNSIGNED_BYTE;

        switch (texture->format->BitsPerPixel)
        {
            case 32:
                img_format = GL_RGBA;
                img_type = GL_UNSIGNED_BYTE;
                internal_format = GL_RGBA;
                break;
            case 24:
                img_format = GL_RGB;
                img_type = GL_UNSIGNED_BYTE;
                internal_format = GL_RGB;
                break;
            case 16:
                img_format = GL_RGBA;
                img_type = GL_UNSIGNED_SHORT_5_5_5_1;
                internal_format = GL_RGB;
                break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, tex_width, tex_height, 0, img_format, img_type, texture->pixels);

        SDL_FreeSurface(texture);
    }
    else
    {
        std::fstream ktx(_filename.c_str(), std::ios::binary|std::ios::in);

        char header[12];
        unsigned int endiannes;
        unsigned int glType;
        unsigned int glTypeSize;
        unsigned int glFormat;
        unsigned int glInternalFormat;
        unsigned int glBaseInternalFormat;
        unsigned int pixelWidth;
        unsigned int pixelHeight;
        unsigned int pixelDepth;
        unsigned int numberOfArrayElements;
        unsigned int numberOfFaces;
        unsigned int numberOfMipmapLevels;
        unsigned int bytesOfKeyValueData;

        // read header

        ktx.read(header, 12);
        ktx.read((char*)&endiannes, sizeof(unsigned int));
        ktx.read((char*)&glType, sizeof(unsigned int));
        ktx.read((char*)&glTypeSize, sizeof(unsigned int));
        ktx.read((char*)&glFormat, sizeof(unsigned int));
        ktx.read((char*)&glInternalFormat, sizeof(unsigned int));
        ktx.read((char*)&glBaseInternalFormat, sizeof(unsigned int));
        ktx.read((char*)&pixelWidth, sizeof(unsigned int));
        ktx.read((char*)&pixelHeight, sizeof(unsigned int));
        ktx.read((char*)&pixelDepth, sizeof(unsigned int));
        ktx.read((char*)&numberOfArrayElements, sizeof(unsigned int));
        ktx.read((char*)&numberOfFaces, sizeof(unsigned int));
        ktx.read((char*)&numberOfMipmapLevels, sizeof(unsigned int));
        ktx.read((char*)&bytesOfKeyValueData, sizeof(unsigned int));

        // assume no key value data, no mipmaps, no cube faces, single texture

        unsigned int imageSize;

        ktx.read((char*)&imageSize, sizeof(unsigned int));

        char* data = new char[imageSize];

        ktx.read(data, imageSize);

        glMap[_filename] = 0;

        glGenTextures(1, &glMap[_filename]);
        glBindTexture(GL_TEXTURE_2D, glMap[_filename]);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if (glType == GL_UNSIGNED_SHORT_5_5_5_1)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixelWidth, pixelHeight, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
        }
        else if (glType == GL_UNSIGNED_SHORT_5_6_5)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixelWidth, pixelHeight, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, glInternalFormat, pixelWidth, pixelHeight, 0, glFormat, glType, data);
        }

        delete[] data;

        ktx.close();
    }

    return glMap[_filename];
}

int wizTextureManager::getTexture(std::string _filename)
{
    if (glMap.find(_filename) == glMap.end())
    {
        return wizTextureManager::loadTexture(_filename);
    }

    return glMap[_filename];
}

int wizTextureManager::createTexture(std::string _filename, unsigned int _internalFormat, unsigned int _format, unsigned int _width, unsigned int _height)
{
    if (glMap.find(_filename) == glMap.end())
    {
        GLubyte* data = new GLubyte[_width * _height * 4];
        memset(data, 0, _width * _height * 4);
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _format, GL_UNSIGNED_BYTE, data);
        delete[] data;

        return id;
    }
    else
    {
        return (int)glMap[_filename];
    }
}

int wizTextureManager::updateTexture(std::string _filename, unsigned int _format, unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height)
{
    if (glMap.find(_filename) != glMap.end())
    {
        int id = glMap[_filename];

        glBindTexture(GL_TEXTURE_2D, id);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, _format, _x, _y, _width, _height, 0);

        return id;
    }

    return -1;
}
