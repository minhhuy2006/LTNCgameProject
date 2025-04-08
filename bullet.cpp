#include "bullet.h"
#include "defs.h"
#include <iostream>
using namespace std;

Bullet::Bullet(float x, float y, float dx, float dy, SDL_Texture* texture, Uint32 currentTime) {
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    this->texture = texture;
    this->lastShootTime = currentTime;
}
void Bullet::move() {
    x += dx;
    y += dy;
}
void Bullet::render(SDL_Renderer* renderer) {
    SDL_Rect destRect;
    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
    destRect.w = BULLET_WIDTH;
    destRect.h = BULLET_HEIGHT;
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
bool Bullet::isOutOfBounds() {
    return x < 0 || y < 0 || x > 1000 || y > 800;
}
