#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 600;
constexpr Uint16 SCREEN_HEIGHT = 600;


// RESOURCES SETTINGS ---------------------------------------------------

#define RESOURCES_DIR_PATH "resources/"


// GAME SPECIFIC SETTINGS -------------------------------------------

// Paddle settings
constexpr Uint16 PADDLE_WIDTH = 80;
constexpr Uint16 PADDLE_HEIGHT = 6;
constexpr Uint16 PLAYER_SPEED = 400;

// Ball settings
constexpr float BALL_SIZE = 8;
constexpr float BALL_SPEED = 300;

// Bricks settings
constexpr Uint16 BRICK_WIDTH = 500;
constexpr Uint16 BRICK_HEIGHT = 6;


// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct MoveKeybind
{
	SDL_Keycode UP;
	SDL_Keycode DOWN;
	SDL_Keycode LEFT;
	SDL_Keycode RIGHT;
};

constexpr MoveKeybind MOVE_KEYBIND = { SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT };
