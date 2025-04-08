#include "player.h"
#include <SDL_image.h>
#include <cmath>
#include <iostream>
using namespace std;

Player::Player(SDL_Renderer* renderer, const char* imagePath, float startX, float startY) {
    x = startX;
    y = startY;
    dx = 0;
    dy = 0;
    health = 8;
    angle = 0;
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;
    lastShootTime = 0;
    hitDelay = 6;
    this->renderer = renderer;
    SDL_Surface* surface = IMG_Load(imagePath);
    if (!surface) {
        cout << "Không thể tải ảnh tàu: " << IMG_GetError() << endl;
        texture = nullptr;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}
void Player::handleInput(const Uint8* keystate, SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right) {
    dx = 0;
    dy = 0;

    if (keystate[up]) dy = -1;
    if (keystate[down]) dy = 1;
    if (keystate[left]) dx = -1;
    if (keystate[right]) dx = 1;

    if (dx != 0 || dy != 0) {
        angle = atan2(dy, dx) * 180.0 / M_PI;
    }
}
void Player::move() {
    x += dx * PLAYER_SPEED;
    y += dy * PLAYER_SPEED;

    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > SCREEN_WIDTH - width) x = SCREEN_WIDTH - width;
    if (y > SCREEN_HEIGHT - height) y = SCREEN_HEIGHT - height;
}
void Player::shoot(vector<Bullet>& bullets, Uint32 currentTime, SDL_Texture* bulletTexture, Sound& shootSound) {
    lastShootTime = currentTime;

    float rad = angle * M_PI / 180.0f;
    float bx = x + width / 2 + cos(rad) * width / 2;
    float by = y + height / 2 + sin(rad) * height / 2;

    float bulletDx = cos(rad) * BULLET_SPEED;
    float bulletDy = sin(rad) * BULLET_SPEED;

    bullets.emplace_back(bx, by, bulletDx, bulletDy, bulletTexture, currentTime);
    shootSound.playShootSound();
}
bool Player::checkCollision(const Bullet& bullet, Uint32 currentTime) {
    if (currentTime - bullet.lastShootTime <= hitDelay) return false;

    SDL_Rect playerRect = { (int)x, (int)y, width, height };
    SDL_Rect bulletRect = { (int)bullet.x, (int)bullet.y, BULLET_WIDTH, BULLET_HEIGHT };

    return SDL_HasIntersection(&playerRect, &bulletRect);
}
void Player::decreaseHealth() {
    if (health > 0) health--;
}
void Player::render(SDL_Renderer* renderer) {
    SDL_Rect dst = { (int)x, (int)y, width, height };
    SDL_RenderCopyEx(renderer, texture, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}
void Player::renderHealth(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect border = { x, y, 8 * 40, 20 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &border);

    SDL_Rect fill = { x, y, health * 40, 20 };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fill);
}
void Player::resetPosition(float startX, float startY) {
    x = startX;
    y = startY;
    dx = 0;
    dy = 0;
    angle = 0;
}
Player::~Player() {
    if (texture) SDL_DestroyTexture(texture);
}
