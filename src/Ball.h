#pragma once

#include <Djipi.h>

namespace DjipiApp
{
	class Ball : public Djipi::GameObject
	{
	public:
		Ball();

		void Update(double deltaTime) override;

		void OnCollide(Djipi::GameObject& other) override;
	};
}
