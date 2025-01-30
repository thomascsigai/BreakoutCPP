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

// Score display
constexpr Uint16 SCORE_PANEL_SIZE = 100;

// Paddle settings
constexpr Uint16 PADDLE_WIDTH = 80;
constexpr Uint16 PADDLE_HEIGHT = 6;
constexpr Uint16 PLAYER_SPEED = 400;

// Ball settings
constexpr float BALL_SIZE = 8;
constexpr float BALL_SPEED = 300;

// Bricks settings
constexpr float BRICK_WIDTH = 33.5;
constexpr float BRICK_HEIGHT = 10;

constexpr Uint16 BRICKS_ROWS = 8;
constexpr Uint16 BRICKS_NUMBER_PER_ROWS = 16;


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
