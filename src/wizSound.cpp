#include "wizSound.h"

int wizSound::musicVolume;
int wizSound::sampleVolume;
int wizSound::musicLimit;
int wizSound::sampleLimit;
int wizSound::musicCount;
int wizSound::sampleCount;
int wizSound::lastMusicAdded;
int wizSound::lastSampleAdded;

std::map<std::string, int> wizSound::musicMap;
std::map<std::string, int> wizSound::sampleMap;

void wizSound::initialize()
{
    initialize(DEFAULT_MUSIC_SPACE, DEFAULT_SAMPLE_SPACE, DEFAULT_MUSIC_VOLUME, DEFAULT_SAMPLE_VOLUME);
}

void wizSound::initialize(int _musicSpace, int _sampleSpace, int _musicVolume, int _sampleVolume)
{
    musicCount = 0;
    sampleCount = 0;
    musicLimit = _musicSpace;
    sampleLimit = _sampleSpace;

    g_cSound.CreateSound();
    g_cSound.AllocateMusicSpace(_musicSpace);
    g_cSound.AllocateChunkSpace(_sampleSpace);
    setMusicVolume(_musicVolume);
    g_cSound.SetChunkVolume((char)_sampleVolume);
}

void wizSound::destroy()
{
    for (int i = 0; i < wizSound::musicCount; i++)
    {
        g_cSound.DeleteMusic(i);
    }

    for (int i = 0; i < sampleCount; i++)
    {
        g_cSound.DeleteChunk(i);
    }

    g_cSound.DestroySound();
}

void wizSound::setMusicVolume(int _volume)
{
    musicVolume = _volume;
    if (musicVolume < 0) musicVolume = 0;
    if (musicVolume > 128) musicVolume = 128;

    g_cSound.SetMusicVolume((char)_volume);
}

void wizSound::setSampleVolume(int _volume)
{
    sampleVolume = _volume;
    if (sampleVolume < 0) sampleVolume = 0;
    if (sampleVolume > 128) sampleVolume = 128;

    g_cSound.SetChunkVolume((char)_volume);
}

int wizSound::getMusicVolume()
{
    return musicVolume;
}

int wizSound::getSampleVolume()
{
    return sampleVolume;
}

int wizSound::loadMusic(std::string _filename)
{
    if (musicMap.find(_filename) != musicMap.end())
    {
        return musicMap[_filename];
    }

    lastMusicAdded++;
    if (lastMusicAdded >= musicLimit - 1) lastMusicAdded = 0;

    if (musicCount > musicLimit - 1)
    {
        std::map<std::string, int>::iterator i;

        for (i = musicMap.begin(); i != musicMap.end(); i++)
        {
            if (i->second == lastMusicAdded)
            {
                musicMap.erase(musicMap.find(i->first));
                break;
            }
        }

        g_cSound.DeleteMusic(lastMusicAdded);
        g_cSound.LoadMusicFromBinary(lastMusicAdded, 0, (char*)_filename.c_str());
        musicMap[_filename] = lastMusicAdded;
        return lastMusicAdded;
    }
    else
    {
        g_cSound.LoadMusicFromBinary(musicCount, 0, (char*)_filename.c_str());
        musicMap[_filename] = musicCount;
        musicCount++;
        return musicCount - 1;
    }
}

int wizSound::loadSample(std::string _filename)
{
    if (sampleMap.find(_filename) != sampleMap.end())
    {
        return sampleMap[_filename];
    }

    lastSampleAdded++;
    if (lastSampleAdded >= sampleLimit - 1) lastSampleAdded = 0;

    if (sampleCount > sampleLimit - 1)
    {
        std::map<std::string, int>::iterator i;

        for (i = sampleMap.begin(); i != sampleMap.end(); i++)
        {
            if (i->second == lastSampleAdded)
            {
                sampleMap.erase(sampleMap.find(i->first));
                break;
            }
        }

        g_cSound.DeleteChunk(lastSampleAdded);
        g_cSound.LoadChunkFromBinary(lastSampleAdded, 0, (char*)_filename.c_str());
        sampleMap[_filename] = lastSampleAdded;
        return lastSampleAdded;
    }
    else
    {
        g_cSound.LoadChunkFromBinary(sampleCount, 0, (char*)_filename.c_str());
        sampleMap[_filename] = sampleCount;
        sampleCount++;
        return sampleCount-1;
    }
}

int wizSound::loadMusic(std::string _filename, char* _stream, int _length)
{
    if (musicMap.find(_filename) != musicMap.end())
    {
        return musicMap[_filename];
    }

    lastMusicAdded++;
    if (lastMusicAdded >= musicLimit - 1) lastMusicAdded = 0;

    if (musicCount > musicLimit - 1)
    {
        std::map<std::string, int>::iterator i;

        for (i = musicMap.begin(); i != musicMap.end(); i++)
        {
            if (i->second == lastMusicAdded)
            {
                musicMap.erase(musicMap.find(i->first));
                break;
            }
        }

        g_cSound.DeleteMusic(lastMusicAdded);
        g_cSound.LoadMusicFromMemory(lastMusicAdded, 0, _stream, _length);
        musicMap[_filename] = lastMusicAdded;
        return lastMusicAdded;
    }
    else
    {
        g_cSound.LoadMusicFromMemory(musicCount, 0, _stream, _length);
        musicMap[_filename] = musicCount;
        musicCount++;
        return musicCount - 1;
    }
}

int wizSound::loadSample(std::string _filename, char* _stream, int _length)
{
    if (sampleMap.find(_filename) != sampleMap.end())
    {
        return sampleMap[_filename];
    }

    lastSampleAdded++;
    if (lastSampleAdded >= sampleLimit - 1) lastSampleAdded = 0;

    if (sampleCount > sampleLimit - 1)
    {
        std::map<std::string, int>::iterator i;

        for (i = sampleMap.begin(); i != sampleMap.end(); i++)
        {
            if (i->second == lastSampleAdded)
            {
                sampleMap.erase(sampleMap.find(i->first));
                break;
            }
        }

        g_cSound.DeleteChunk(lastSampleAdded);
        g_cSound.LoadChunkFromMemory(lastSampleAdded, 0, _stream, _length);
        sampleMap[_filename] = lastSampleAdded;
        return lastSampleAdded;
    }
    else
    {
        g_cSound.LoadChunkFromMemory(sampleCount, 0, _stream, _length);
        sampleMap[_filename] = sampleCount;
        sampleCount++;
        return sampleCount - 1;
    }
}

void wizSound::playMusic(std::string _filename, bool _loop)
{
    int id = findMusicID(_filename);

    if (id != -1)
    {
        g_cSound.PlayMusic(id, _loop ? 1 : 0);
    }
}

void wizSound::playSample(std::string _filename)
{
    int id = findSampleID(_filename);

    if (id != -1)
    {
        g_cSound.PlayImportChunk(id);
    }
}

void wizSound::stopMusic()
{
    g_cSound.StopMusic();
}

void wizSound::resumeMusic()
{
    g_cSound.ResumeMusic();
}

void wizSound::pauseMusic()
{
    g_cSound.PauseMusic();
}

void wizSound::stopSample(std::string _filename)
{
    int id = findSampleID(_filename);

    if (id != -1)
    {
        g_cSound.StopImportChunk(id);
    }
}

int wizSound::findMusicID(std::string _filename)
{
    if (musicMap.find(_filename) != musicMap.end())
    {
        return musicMap[_filename];
    }
    else
    {
        return -1;
    }
}

int wizSound::findSampleID(std::string _filename)
{
    if (sampleMap.find(_filename) != sampleMap.end())
    {
        return sampleMap[_filename];
    }
    else
    {
        return -1;
    }
}
