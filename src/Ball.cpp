#include <Ball.h>
#include <Player.h>

namespace DjipiApp
{
	Ball::Ball()
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2);
		m_Transform.SetSize(BALL_SIZE, BALL_SIZE);

		m_VelX = 0;
		m_VelY = 0;

		m_SpeedMultiplier = 1;
	}

	void Ball::Update(double deltaTime)
	{
		// Hit a left wall
		if (m_Transform.x < 0)
		{
			m_VelX *= -1;
			m_Transform.SetPosition(0, m_Transform.y);
			SDL_PushEvent(&OnBallTouch);
		}
		
		// Hit a right wall
		if (m_Transform.x > SCREEN_WIDTH - BALL_SIZE)
		{
			m_VelX *= -1;
			m_Transform.SetPosition(SCREEN_WIDTH - BALL_SIZE, m_Transform.y);
			SDL_PushEvent(&OnBallTouch);
		}

		// Hit a up wall
		if (m_Transform.y < 0 + SCORE_PANEL_SIZE)
		{
			m_VelY *= -1;
			m_Transform.SetPosition(m_Transform.x, 0);
			SDL_PushEvent(&OnBallTouch);
		}

		// Hit a down wall
		if (m_Transform.y > SCREEN_HEIGHT - BALL_SIZE)
		{
			LoosePoint();
		}

		DjipiApp::Ball::Move(deltaTime);
	}

	void Ball::Move(double deltaTime)
	{
		m_Transform.x += m_VelX * m_SpeedMultiplier * deltaTime;
		m_Transform.y += m_VelY * m_SpeedMultiplier * deltaTime;

		m_Transform.UpdateCollider();
	}

	void Ball::IncreaseSpeed(Uint16 pointsScored)
	{
		float normSpeed = pow(m_VelX * m_SpeedMultiplier, 2) + pow(m_VelY * m_SpeedMultiplier, 2);

		if (normSpeed < BALL_MAX_SPEED * BALL_MAX_SPEED)
		{
			m_SpeedMultiplier += (float)pointsScored / BALL_SPEED_MULT_MODIFIER;
		}
	}

	void Ball::OnCollide(GameObject& other)
	{
		if (typeid(other) == typeid(DjipiApp::Player))
		{
			m_VelY *= -1;
			m_Transform.SetPosition(m_Transform.x, other.GetTransform().y - BALL_SIZE);
			SDL_PushEvent(&OnBallTouch);

			//// X direction depends on where the ball touch the paddle
			float t = ((m_Transform.x + BALL_SIZE / 2)  - other.GetTransform().x) / PADDLE_WIDTH;
			m_VelX = (t - 0.5) * DISPERSION_CONST * BALL_SPEED;

			float norm = sqrt(pow(m_VelX, 2) + pow(m_VelY, 2));
			m_VelX = m_VelX * BALL_SPEED / norm;
			m_VelY = m_VelY * BALL_SPEED / norm;
		}
	}

	void Ball::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == START_KEYBIND)
			{
				StartGame();
			}
		}
	}

	void Ball::StartGame()
	{
		if (m_VelX == 0 && m_VelY == 0)
		{
			m_VelX = 1;
			m_VelY = BALL_SPEED;

			SDL_PushEvent(&OnStartGame);
		}
	}

	void Ball::LoosePoint()
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		
		m_VelX = 0;
		m_VelY = 0;

		m_SpeedMultiplier = 1;

		SDL_PushEvent(&OnBallOut);
	}
}