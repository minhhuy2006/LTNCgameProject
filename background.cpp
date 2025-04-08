#include "Background.h"
using namespace std;

Background::Background(SDL_Renderer* renderer, const char* filePath){
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface){
        cout << "Error loading background image: " << IMG_GetError() << endl;
        texture = nullptr;
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}
Background::~Background() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}
void Background::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}
