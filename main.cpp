#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "defs.h"
#include "Background.h"
#include "Intro.h"
#include "Font.h"
#include "Player.h"
#include "Bullet.h"
#include "Music.h"
#include "Sound.h"
#include "Time.h"

using namespace std;

int SDL_main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    SDL_Window* window = SDL_CreateWindow("Space Shooting 2 Player",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Background background(renderer, "background.jpg");
    Intro intro(renderer, "intro.jpg");
    Font font("pursia.ttf", 28);
    SDL_Color textColor = {255, 255, 255, 255};
    Music bgm("music.wav");
    bgm.play();
    SDL_Surface* bulletSurface = IMG_Load("bullet.jpg");
    if (!bulletSurface) {
        cout << "Lỗi tải bullet.jpg: " << IMG_GetError() << endl;
        return -1;
    }
    SDL_Texture* bulletTexture = SDL_CreateTextureFromSurface(renderer, bulletSurface);
    SDL_FreeSurface(bulletSurface);
    Sound shootSound("shoot.wav");
    bool gameRunning = true;
    while (gameRunning) {
        SDL_RenderClear(renderer);
        intro.render(renderer);
        SDL_RenderPresent(renderer);
        if(!intro.waitForInput()){
            break;
        }
        Player player1(renderer, "player1.jpg", 10, SCREEN_HEIGHT / 2 - PLAYER_HEIGHT / 2);
        Player player2(renderer, "player2.jpg", SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2 - PLAYER_HEIGHT / 2);
        vector<Bullet> bullets;
        Uint32 lastShootTime1 = 0;
        Uint32 lastShootTime2 = 0;
        Time gameTime;
        gameTime.reset();
        bool gameLoop = true;
        bool paused = false;
        while (gameLoop){
            Uint32 currentTime = SDL_GetTicks();
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    gameRunning = false;
                    gameLoop = false;
                }
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                    paused = !paused;
                    if (paused) gameTime.pause();
                    else gameTime.resume();
                }
            }
            const Uint8* keyState = SDL_GetKeyboardState(NULL);
            if (!paused){
                player1.handleInput(keyState, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D);
                player2.handleInput(keyState, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
                player1.move();
                player2.move();
                if (keyState[SDL_SCANCODE_SPACE] && currentTime - lastShootTime1 > SHOOT_DELAY) {
                    player1.shoot(bullets, currentTime, bulletTexture, shootSound);
                    lastShootTime1 = currentTime;
                }
                if ((SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) && currentTime - lastShootTime2 > SHOOT_DELAY) {
                    player2.shoot(bullets, currentTime, bulletTexture, shootSound);
                    lastShootTime2 = currentTime;
                }
                for (auto& bullet : bullets) {
                    bullet.move();
                    if (player1.checkCollision(bullet, currentTime)) {
                        player1.decreaseHealth();
                        bullet.x = -100;
                    }
                    if (player2.checkCollision(bullet, currentTime)) {
                        player2.decreaseHealth();
                        bullet.x = -100;
                    }
                }
                bullets.erase(remove_if(bullets.begin(), bullets.end(),
                    [](Bullet& b) { return b.isOutOfBounds(); }), bullets.end());
                if(gameTime.isTimeUp() || player1.getHealth()<=0 || player2.getHealth()<=0){
                    string resultText;
                    if (player1.getHealth() <= 0) resultText = "Player 2 Wins!";
                    else if(player2.getHealth() <= 0) resultText = "Player 1 Wins!";
                    else if(player1.getHealth() > player2.getHealth()) resultText = "Time's Up! Player 1 Wins!";
                    else if(player2.getHealth() > player1.getHealth()) resultText = "Time's Up! Player 2 Wins!";
                    else resultText = "Time's Up! Draw!";
                    bool waiting = true;
                    while (waiting) {
                        while (SDL_PollEvent(&event)) {
                            if (event.type == SDL_QUIT) {
                                gameRunning = false;
                                waiting = false;
                            }
                            if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN) {
                                waiting = false;
                            }
                        }
                        SDL_RenderClear(renderer);
                        background.render(renderer);
                        font.renderText(renderer, resultText, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2 - 30, textColor);
                        font.renderText(renderer, "Press any key or click to restart",SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2 + 30, textColor);
                        SDL_RenderPresent(renderer);
                    }
                    gameLoop = false;
                }
            }
            SDL_RenderClear(renderer);
            background.render(renderer);
            player1.render(renderer);
            player2.render(renderer);
            for (auto& b : bullets) b.render(renderer);
            player1.renderHealth(renderer, 50, 70);
            player2.renderHealth(renderer, SCREEN_WIDTH - 350, 70);
            font.renderText(renderer, "Player 1", 50, 10, textColor);
            font.renderText(renderer, "Player 2", SCREEN_WIDTH - 150, 10, textColor);
            font.renderText(renderer, "Time: " + to_string(gameTime.getRemainingTime()), SCREEN_WIDTH / 2 - 50, 10, textColor);
            if (paused) {
                font.renderText(renderer, "PAUSED", SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 - 30, textColor);
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
