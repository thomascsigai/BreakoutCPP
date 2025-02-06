#pragma once

#include <SDL.h>

namespace UserEvents
{
	// Place here your events you have to use in your app
	// const inline Uint32 EVENT_TYPE = SDL_RegisterEvents(1);
	const inline Uint32 BRICK_DESTROYED = SDL_RegisterEvents(1);
	
	const inline Uint32 BALL_OUT = SDL_RegisterEvents(1);
	const inline Uint32 BALL_TOUCH = SDL_RegisterEvents(1);

	const inline Uint32 START_GAME = SDL_RegisterEvents(1);

	const inline Uint32 GAME_OVER = SDL_RegisterEvents(1);
}