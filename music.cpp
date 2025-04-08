#include "Music.h"

Music::Music(const char* filePath){
    music = Mix_LoadMUS(filePath);
    if (!music) {
        cout << "Không thể tải nhạc" << Mix_GetError() << endl;
    }
}

Music::~Music(){
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
}
void Music::play(int loops) {
    if (music) {
        if (Mix_PlayMusic(music, loops) == -1) {
            cout << "Không thể bật nhạc " << Mix_GetError() << endl;
        }
    }
}
void Music::stop(){
    Mix_HaltMusic();
}
void Music::pause() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }
}
void Music::resume(){
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }
}
bool Music::isPlaying(){
    return Mix_PlayingMusic() != 0;
}
