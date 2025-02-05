#pragma once

#include <Djipi.h>
#include <UserEvents.h>

namespace DjipiApp
{
	class Brick : public Djipi::GameObject
	{
	public:
		Brick(float x, float y, BrickType type);

		void OnCollide(Djipi::GameObject& other) override;

		void Reset();

		// Getters
		bool IsDestroyed() const { return m_Destroyed; }

	private:
		BrickType m_Type;
		bool m_Destroyed;

		void SetBrickColor();

		// Events 
		// SDL_Event OnEvent = { UserEvents::EVENT_TYPE };
		SDL_Event OnBrickDestroyed = { UserEvents::BRICK_DESTROYED };
	};
}