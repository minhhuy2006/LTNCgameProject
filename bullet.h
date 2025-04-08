#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include <SDL.h>
using namespace std;

class Bullet {
public:
    float x;
    float y;
    float dx;
    float dy;
    SDL_Texture* texture;
    Uint32 lastShootTime;
    Bullet(float _x, float _y, float _dx, float _dy, SDL_Texture* _texture, Uint32 _currentTime);
    void move();
    void render(SDL_Renderer* renderer);
    bool isOutOfBounds();
};

#endif // BULLET_H_INCLUDED
