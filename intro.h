#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

using namespace std;

class Intro {
private:
    SDL_Texture* introTexture;
    SDL_Rect rect;
public:
    Intro(SDL_Renderer* renderer, const char* introPath);
    ~Intro();
    void render(SDL_Renderer* renderer);
    bool waitForInput();
};

#endif // INTRO_H_INCLUDED
