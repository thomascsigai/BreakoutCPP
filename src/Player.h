#pragma once

#include <Djipi.h>

namespace DjipiApp
{
	class Player : public Djipi::GameObject
	{
	public:
		Player();

		void Update(double deltaTime) override;

		void HandleEvent(SDL_Event& e) override;

		void LooseLife();

		void IncreaseScore(Uint16 points);

		void Reset();

		// Getters
		Uint16 GetScore() const { return m_Score; }
		Uint16 GetLives() const { return m_Lives; }

	private:
		Uint16 m_Lives;
		Uint16 m_Score;
	};
}