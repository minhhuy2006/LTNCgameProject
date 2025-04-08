#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"
#include "bullet.h"
#include "sound.h"
using namespace std;
class Player {
private:
    float x, y;
    float dx, dy;
    int width, height;
    int health;
    double angle;
    Uint32 lastShootTime;
    Uint32 hitDelay;
    SDL_Texture* texture;
    SDL_Renderer* renderer;

public:
    Player(SDL_Renderer* renderer, const char* imagePath, float startX, float startY);
    void handleInput(const Uint8* keystate, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right);
    void move();
    void shoot(vector<Bullet>& bullets, Uint32 currentTime, SDL_Texture* bulletTexture, Sound& shootSound);
    bool checkCollision(const Bullet& bullet, Uint32 currentTime);
    void decreaseHealth();
    void render(SDL_Renderer* renderer);
    void renderHealth(SDL_Renderer* renderer, int x, int y);
    void resetPosition(float startX, float startY);
    int getHealth() const { return health; }
    void free() {
        if (texture) {
            SDL_DestroyTexture(texture);
            texture = nullptr;
        }
    }
    void setHealth(int h) { health = h; }
    ~Player();
};

#endif // PLAYER_H_INCLUDED
