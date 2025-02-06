#include <Player.h>
#include <GameConfig.h>

namespace DjipiApp
{
	Player::Player()
	{
		m_Transform.SetPosition(SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - PADDLE_HEIGHT - 20);
		m_Transform.SetSize(PADDLE_WIDTH, PADDLE_HEIGHT);

		m_Lives = 3;
		m_Score = 0;
	}

	void Player::Update(double deltaTime)
	{
		m_Transform.x += m_VelX * deltaTime;

		if (m_Transform.x < -PADDLE_WIDTH + 5 || m_Transform.x > SCREEN_WIDTH - 5)
		{
			m_Transform.x -= m_VelX * deltaTime;
		}

		m_Transform.UpdateCollider();
	}

	void Player::HandleEvent(SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_VelX -= PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_VelX += PLAYER_SPEED;
		}
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			if (e.key.keysym.sym == MOVE_KEYBIND.LEFT) m_VelX += PLAYER_SPEED;
			if (e.key.keysym.sym == MOVE_KEYBIND.RIGHT) m_VelX -= PLAYER_SPEED;
		}
	}

	void Player::LooseLife()
	{
		m_Lives--;
	}

	void Player::IncreaseScore(Uint16 points)
	{
		m_Score += points;
	}

	void Player::Reset()
	{
		m_Lives = 3;
		m_Score = 0;
	}
}