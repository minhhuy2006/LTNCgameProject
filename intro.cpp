#include "Intro.h"
#include "defs.h"

Intro::Intro(SDL_Renderer* renderer, const char* introPath){
    SDL_Surface* surface = IMG_Load(introPath);
    if(!surface){
        cout << "Error loading intro image: " << IMG_GetError() << endl;
        introTexture = nullptr;
    }else {
        introTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    rect = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
}
Intro::~Intro(){
    if(introTexture){
        SDL_DestroyTexture(introTexture);
    }
}
void Intro::render(SDL_Renderer* renderer){
    if(introTexture){
        SDL_RenderCopy(renderer, introTexture, nullptr, &rect);
    }
}
bool Intro::waitForInput(){
    SDL_Event event;
    while(true){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                return false;
            if(event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
                return true;
        }
        SDL_Delay(10);
    }
}
