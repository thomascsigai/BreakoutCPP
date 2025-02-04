#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

// WINDOW SETTINGS --------------------------------------------------

constexpr Uint16 SCREEN_WIDTH = 645;
constexpr Uint16 SCREEN_HEIGHT = 700;


// RESOURCES SETTINGS ---------------------------------------------------

#define RESOURCES_DIR_PATH "resources/"

#define BIT_FONT_DIR_PATH "resources/fonts/bit5x3.ttf"


// GAME SPECIFIC SETTINGS -------------------------------------------

// Score display
constexpr Uint16 SCORE_PANEL_SIZE = 100;

// Paddle settings
constexpr Uint16 PADDLE_WIDTH = 80;
constexpr Uint16 PADDLE_HEIGHT = 6;
constexpr Uint16 PLAYER_SPEED = 500;
constexpr Uint16 DISPERSION_CONST = 2;

// Ball settings
constexpr float BALL_SIZE = 8;
constexpr float BALL_SPEED = 300;

// Bricks settings
constexpr float BRICK_WIDTH = 42;
constexpr float BRICK_HEIGHT = 10;

constexpr Uint16 BRICKS_ROWS = 8;
constexpr Uint16 BRICKS_NUMBER_PER_ROWS = 14;

enum BrickType
{
	Yellow = 1,
	Green = 3,
	Orange = 5,
	Red = 7
};


// KEYBINDS ---------------------------------------------------------

// Paddles keybinds
struct MoveKeybind
{
	SDL_Keycode LEFT;
	SDL_Keycode RIGHT;
};

constexpr MoveKeybind MOVE_KEYBIND = { SDLK_LEFT, SDLK_RIGHT };
constexpr SDL_KeyCode START_KEYBIND = SDLK_SPACE;
