#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "defs.h"

using namespace std;
class Background {
private:
    SDL_Texture* texture;
    SDL_Rect rect;
public:
    Background(SDL_Renderer* renderer, const char* filePath);
    ~Background();
    void render(SDL_Renderer* renderer);
};

#endif // BACKGROUND_H_INCLUDED
