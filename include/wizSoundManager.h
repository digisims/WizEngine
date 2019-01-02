#ifndef wizSoundManager_H
#define wizSoundManager_H

#include "SDL.h"
#include "SDL_mixer.h"

#include <map>
#include <string>
#include <vector>

class wizSoundManager
{
    public:

    static void initialize();
    static void destroy();

    static void callback(int _channel);

    static std::vector<std::string> getSampleList();

    static Mix_Chunk* loadSample(std::string _filename);
    static Mix_Chunk* findSample(std::string _filename);
    static void setSampleVolume(std::string _filename, int _volume);
    static int getSampleVolume(std::string _filename);
    static void playSample(std::string _filename);
    static void stopSample(std::string _filename);
    static void resumeSample(std::string _filename);
    static void pauseSample(std::string _filename);
    static bool isSamplePlaying(std::string _filename);

    static Mix_Music* loadMusic(std::string _filename);
    static Mix_Music* findMusic(std::string _filename);
    static void setMusicVolume(int _volume);
    static int getMusicVolume();
    static void playMusic(std::string _filename, bool _loop);
    static void stopMusic();
    static void resumeMusic();
    static void pauseMusic();
    static bool isMusicPlaying();

    protected:

    static int musicVolume;
    static std::map<std::string, int> volumeMap;
    static std::map<std::string, Mix_Music*> musicMap;
    static std::map<std::string, Mix_Chunk*> sampleMap;
    static std::map<std::string, int> channelMap;
};

void channelDoneCallback(int channel);

#endif // wizSoundManager_H
