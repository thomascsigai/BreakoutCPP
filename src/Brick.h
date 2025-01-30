#pragma once

#include <Djipi.h>

namespace DjipiApp
{
	class Brick : public Djipi::GameObject
	{
	public:
		Brick(float x, float y, int numberOfLives);
		~Brick();

		void OnCollide(Djipi::GameObject& other) override;

	private:
		int m_Lives;

	};
}