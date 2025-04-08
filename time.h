#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#pragma once
#include <SDL.h>
using namespace std;

class Time {
public:
    Time();
    void reset();
    int getRemainingTime();
    bool isTimeUp();
    void pause();
    void resume();

private:
    Uint32 startTime;
    Uint32 pauseStart;
    Uint32 pausedDuration;
    bool paused;
    const int TOTAL_TIME = 90;
};


#endif // TIME_H_INCLUDED
