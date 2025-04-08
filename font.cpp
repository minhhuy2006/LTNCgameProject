#include "font.h"
#include <iostream>
using namespace std;
Font::Font(const string& fontPath, int fontSize) {
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font) {
        cout << "Không tải được phông chữ " << TTF_GetError() << endl;
    }
}
Font::~Font() {
    if (font) {
        TTF_CloseFont(font);
    }
}
void Font::renderText(SDL_Renderer* renderer, const string& text, int x, int y, SDL_Color color) {
    if (!font) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        cout << "Không thể tạo surface cho chữ " << TTF_GetError() << endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        cout << "Không thể tạo texture cho chữ" << SDL_GetError() << endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect destRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
