#pragma once

#include <Djipi.h>
#include <UserEvents.h>

namespace DjipiApp
{
	class Ball : public Djipi::GameObject
	{
	public:
		Ball();

		void Update(double deltaTime) override;

		void OnCollide(Djipi::GameObject& other) override;

		void HandleEvent(SDL_Event& e) override;

		// Override of Move to take speed multiplier in account
		void Move(double deltaTime) override;

		void IncreaseSpeed(Uint16 multiplier);

	private:
		float m_SpeedMultiplier;

		void StartGame();

		void LoosePoint();

		// Events
		SDL_Event OnBallOut = { UserEvents::BALL_OUT };
	};
}
