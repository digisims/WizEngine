#include "wizSoundManager.h"

int wizSoundManager::musicVolume;
std::map<std::string, int> wizSoundManager::volumeMap;
std::map<std::string, Mix_Music*> wizSoundManager::musicMap;
std::map<std::string, Mix_Chunk*> wizSoundManager::sampleMap;
std::map<std::string, int> wizSoundManager::channelMap;

void wizSoundManager::initialize()
{
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024);
    Mix_AllocateChannels(6);
    Mix_ChannelFinished(channelDoneCallback);
}

void wizSoundManager::destroy()
{
    std::map<std::string, Mix_Chunk*>::iterator i;

    for (i = sampleMap.begin(); i!=sampleMap.end(); i++)
    {
        Mix_FreeChunk(i->second);
    }

    std::map<std::string, Mix_Music*>::iterator j;

    for (j = musicMap.begin(); j!=musicMap.end(); j++)
    {
        Mix_FreeMusic(j->second);
    }

    Mix_CloseAudio();
}

std::vector<std::string> wizSoundManager::getSampleList()
{
    std::vector<std::string> list;
    std::map<std::string, Mix_Chunk*>::iterator i;

    for (i = sampleMap.begin(); i!=sampleMap.end(); i++)
    {
        list.push_back(i->first);
    }

    return list;
}

void wizSoundManager::callback(int _channel)
{
    std::map<std::string, int>::iterator i;

    for (i = channelMap.begin(); i!=channelMap.end(); i++)
    {
        if (i->second == _channel)
        {
            i->second = -1;
        }
    }
}

void channelDoneCallback(int channel)
{
    wizSoundManager::callback(channel);
}

Mix_Chunk* wizSoundManager::loadSample(std::string _filename)
{
    if (findSample(_filename)==NULL)
    {
        Mix_Chunk* chunk = Mix_LoadWAV(_filename.c_str());
        sampleMap[_filename] = chunk;
        channelMap[_filename] = -1;
    }

    return sampleMap[_filename];
}

Mix_Chunk* wizSoundManager::findSample(std::string _filename)
{
    if (sampleMap.find(_filename)!=sampleMap.end())
    {
        return sampleMap[_filename];
    }

    return NULL;
}

void wizSoundManager::setSampleVolume(std::string _filename, int _volume)
{
    Mix_VolumeChunk(findSample(_filename), _volume);
}

int wizSoundManager::getSampleVolume(std::string _filename)
{
    return Mix_VolumeChunk(findSample(_filename), -1);
}

void wizSoundManager::playSample(std::string _filename)
{
    Mix_Chunk* sample = findSample(_filename);

    if (sample==NULL)
    {
        loadSample(_filename);
    }

    int channel = Mix_PlayChannel(-1, findSample(_filename), 0);
    channelMap[_filename] = channel;
}

void wizSoundManager::stopSample(std::string _filename)
{
    if (findSample(_filename)!=NULL && channelMap[_filename]!=-1)
    {
        Mix_HaltChannel(channelMap[_filename]);
    }
}

void wizSoundManager::resumeSample(std::string _filename)
{
    if (findSample(_filename)!=NULL && channelMap[_filename]!=-1)
    {
        Mix_Resume(channelMap[_filename]);
    }
}

void wizSoundManager::pauseSample(std::string _filename)
{
    if (findSample(_filename)!=NULL && channelMap[_filename]!=-1)
    {
        Mix_Pause(channelMap[_filename]);
    }
}

bool wizSoundManager::isSamplePlaying(std::string _filename)
{
    if (findSample(_filename)!=NULL && channelMap[_filename]!=-1)
    {
        return Mix_Playing(channelMap[_filename]);
    }

    return false;
}

Mix_Music* wizSoundManager::loadMusic(std::string _filename)
{
    if (findMusic(_filename)==NULL)
    {
        Mix_Music* music = Mix_LoadMUS(_filename.c_str());
        musicMap[_filename] = music;
    }

    return musicMap[_filename];
}

Mix_Music* wizSoundManager::findMusic(std::string _filename)
{
    if (musicMap.find(_filename)!=musicMap.end())
    {
        return musicMap[_filename];
    }

    return NULL;
}

void wizSoundManager::setMusicVolume(int _volume)
{
    Mix_VolumeMusic(_volume);
}

int wizSoundManager::getMusicVolume()
{
    return Mix_VolumeMusic(-1);
}

void wizSoundManager::playMusic(std::string _filename, bool _loop)
{
    if (findMusic(_filename)==NULL)
    {
        loadMusic(_filename);
    }

    Mix_PlayMusic(musicMap[_filename], _loop ? -1 : 0);
}

void wizSoundManager::stopMusic()
{
    Mix_HaltMusic();
}

void wizSoundManager::resumeMusic()
{
    Mix_ResumeMusic();
}

void wizSoundManager::pauseMusic()
{
    Mix_PauseMusic();
}

bool wizSoundManager::isMusicPlaying()
{
    return Mix_PlayingMusic() != 0;
}
