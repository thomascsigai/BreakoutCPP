#include <Brick.h>
#include <Ball.h>
#include <GameConfig.h>

namespace DjipiApp
{
	Brick::Brick(float x, float y, BrickType type)
	{
		m_Transform.SetPosition(x, y);
		m_Transform.SetSize(BRICK_WIDTH, BRICK_HEIGHT);

		m_Type = type;
		SetBrickColor();

		m_Destroyed = false;
	}

	void Brick::SetBrickColor()
	{
		switch (m_Type)
		{
		case BrickType::Yellow:
			SetColor(255, 255, 0, 255);
			break;
		
		case BrickType::Green:
			SetColor(0, 255, 0, 255);
			break;
		
		case BrickType::Orange:
			SetColor(255, 128, 0, 255);
			break;
		
		case BrickType::Red:
			SetColor(255, 0, 0, 255);
			break;

		default:
			SetColor(255, 255, 255, 255);
			break;
		}
	}

	void Brick::OnCollide(Djipi::GameObject& other)
	{
		if (typeid(other) == typeid(DjipiApp::Ball))
		{
			other.SetVelocity(other.GetVelocityX(), other.GetVelocityY() * -1);
			m_Destroyed = true;

			OnBrickDestroyed.user.data1 = &m_Type;
			SDL_PushEvent(&OnBrickDestroyed);
		}
	}
}