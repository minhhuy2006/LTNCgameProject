#include "time.h"
#include <SDL.h>
using namespace std;
Time::Time() {
    startTime = SDL_GetTicks();
    pausedDuration = 0;
    paused = false;
}
void Time::reset() {
    startTime = SDL_GetTicks();
    pausedDuration = 0;
    paused = false;
}
int Time::getRemainingTime() {
    if (paused) {
        return TOTAL_TIME - (pauseStart - startTime - pausedDuration) / 1000;
    }
    Uint32 now = SDL_GetTicks();
    return TOTAL_TIME - (now - startTime - pausedDuration) / 1000;
}
bool Time::isTimeUp() {
    return getRemainingTime() <= 0;
}
void Time::pause() {
    if (!paused) {
        paused = true;
        pauseStart = SDL_GetTicks();
    }
}
void Time::resume() {
    if (paused) {
        pausedDuration += SDL_GetTicks() - pauseStart;
        paused = false;
    }
}
