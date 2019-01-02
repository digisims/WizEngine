#ifndef WIZSOUND_H
#define WIZSOUND_H

#include "DGE_Sound.h"

#include <map>
#include <string>

class wizSound
{
    public:

    static const int DEFAULT_MUSIC_SPACE = 12;
    static const int DEFAULT_SAMPLE_SPACE = 64;
    static const int DEFAULT_MUSIC_VOLUME = 100;
    static const int DEFAULT_SAMPLE_VOLUME = 100;

    static void initialize();
    static void initialize(int _musicSpace, int _sampleSpace, int _musicVolume, int _sampleVolume);
    static void destroy();

    static void setMusicVolume(int _volume);
    static void setSampleVolume(int _volume);
    static int getMusicVolume();
    static int getSampleVolume();

    static int loadMusic(std::string _filename);
    static int loadSample(std::string _filename);
    static int loadMusic(std::string _filename, char* _stream, int _length);
    static int loadSample(std::string _filename, char* _stream, int _length);

    static void playMusic(std::string _filename, bool _loop);
    static void playSample(std::string _filename);
    static void stopMusic();
    static void resumeMusic();
    static void pauseMusic();
    static void stopSample(std::string _filename);

    protected:

    static int findMusicID(std::string _filename);
    static int findSampleID(std::string _filename);

    static int musicVolume;
    static int sampleVolume;
    static int musicLimit;
    static int sampleLimit;
    static int musicCount;
    static int sampleCount;
    static int lastMusicAdded;
    static int lastSampleAdded;

    static std::map<std::string, int> musicMap;
    static std::map<std::string, int> sampleMap;
};

#endif // WIZSOUND_H
