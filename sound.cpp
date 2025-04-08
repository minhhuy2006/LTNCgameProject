#include "sound.h"
using namespace std;

Sound::Sound(const char* shootPath) {
    shootSound = Mix_LoadWAV(shootPath);
    if (!shootSound) {
        cout << "Không tìm thấy shoot.wav " << Mix_GetError() << endl;
    }
}
void Sound::playShootSound() {
    if (shootSound) {
        Mix_PlayChannel(-1, shootSound, 0);
    }
}
Sound::~Sound() {
    if (shootSound) {
        Mix_FreeChunk(shootSound);
    }
}
