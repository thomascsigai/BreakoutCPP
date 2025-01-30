#include <Brick.h>
#include <Ball.h>
#include <GameConfig.h>

namespace DjipiApp
{
	Brick::Brick(float x, float y, int numberOfLives)
	{
		m_Transform.SetPosition(x, y);
		m_Transform.SetSize(BRICK_WIDTH, BRICK_HEIGHT);

		m_Lives = numberOfLives;
	}

	Brick::~Brick()
	{
		cout << "Brick destroyed" << endl;
	}

	void Brick::OnCollide(Djipi::GameObject& other)
	{
		if (typeid(other) == typeid(DjipiApp::Ball))
		{
			if (--m_Lives <= 0)
			{
				delete this;
			}
			else
			{
				other.SetVelocity(other.GetVelocityX(), other.GetVelocityY() * -1);

				Transform otherTransform = other.GetTransform();
				otherTransform.SetPosition(otherTransform.x, otherTransform.y + BALL_SIZE);
			}
		}
	}
}