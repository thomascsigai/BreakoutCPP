#include <Ball.h>
#include <Player.h>

namespace DjipiApp
{
	Ball::Ball()
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT - 50);
		m_Transform.SetSize(BALL_SIZE, BALL_SIZE);

		m_VelX = BALL_SPEED;
		m_VelY = -BALL_SPEED;
	}

	void Ball::Update(double deltaTime)
	{
		// Hit a left wall
		if (m_Transform.x < 0)
		{
			m_VelX *= -1;
			m_Transform.SetPosition(0, m_Transform.y);
		}
		
		// Hit a right wall
		if (m_Transform.x > SCREEN_WIDTH - BALL_SIZE)
		{
			m_VelX *= -1;
			m_Transform.SetPosition(SCREEN_WIDTH - BALL_SIZE, m_Transform.y);
		}

		// Hit a up wall
		if (m_Transform.y < 0)
		{
			m_VelY *= -1;
			m_Transform.SetPosition(m_Transform.x, 0);
		}

		// Hit a down wall
		if (m_Transform.y > SCREEN_HEIGHT - BALL_SIZE)
		{
			// Lose point
			m_Transform.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		}

		GameObject::Move(deltaTime);
	}

	void Ball::OnCollide(GameObject& other)
	{
		if (typeid(other) == typeid(DjipiApp::Player))
		{
			m_VelY *= -1;
			m_Transform.SetPosition(m_Transform.x, other.GetTransform().y - BALL_SIZE);

			// X direction depends on where the ball touch the paddle
			float t = ((m_Transform.x + BALL_SIZE / 2)  - other.GetTransform().x) / PADDLE_WIDTH;
			m_VelX = (t - 0.5) * DISPERSION_CONST * BALL_SPEED;

			float norm = sqrt(pow(m_VelX, 2) + pow(m_VelY, 2));
			m_VelX = m_VelX * BALL_SPEED / norm;
			m_VelY = m_VelY * BALL_SPEED / norm;
		}
	}
}