#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;
class Font {
private:
    TTF_Font* font;
public:
    Font(const string& fontPath, int fontSize);
    ~Font();
    void renderText(SDL_Renderer* renderer, const string& text, int x, int y, SDL_Color color);
};


#endif // FONT_H_INCLUDED
