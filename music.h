#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <SDL_mixer.h>
#include <iostream>

using namespace std;

class Music {
private:
    Mix_Music* music;
public:
    Music(const char* filePath);
    ~Music();
    void play(int loops = -1);
    void stop();
    void pause();
    void resume();
    bool isPlaying();
};

#endif // MUSIC_H_INCLUDED
