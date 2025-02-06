// Defines application entry point.
//

#include <GameConfig.h>
#include <Djipi.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <vector>
#include <string>

#include <Player.h>
#include <Ball.h>
#include <Brick.h>

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The renderer 
SDL_Renderer* gRenderer = NULL;
// The font
TTF_Font* gFont = NULL;

// UI Textures
Djipi::Texture gScoreTexture;
Djipi::Texture gLivesTexture;
Djipi::Texture gMessageTexture;
bool showMessage = true;

// Sounds
Mix_Chunk* gBallCollisionSound = NULL;
Mix_Chunk* gPointScoreSound = NULL;
Mix_Chunk* gLooseLifeSound = NULL;
Mix_Chunk* gGameOverSound = NULL;
Mix_Chunk* gWinSound = NULL;

bool CheckCollision(SDL_FRect a, SDL_FRect b)
{
	float leftA, rightA, topA, bottomA;
	float leftB, rightB, topB, bottomB;

	leftA = a.x;	rightA = a.x + a.w;
	topA = a.y;	bottomA = a.y + a.h;

	leftB = b.x;	rightB = b.x + b.w;
	topB = b.y;	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	//If none of the sides from A are outside B
	return true;
}

void LoadBricks(vector<DjipiApp::Brick>& bricks)
{
	int spaceBetweenBricks = (SCREEN_WIDTH / BRICKS_NUMBER_PER_ROWS) - BRICK_WIDTH;
	int scoreDifference = BRICKS_ROWS / 4;

	// Load the bricks column by column
	for (int i = 0; i < BRICKS_NUMBER_PER_ROWS; i++)
	{
		int scoreIterator = 7;
		for (int j = 0; j < BRICKS_ROWS; j++)
		{
			if (j > 0 && j % scoreDifference == 0)
			{
				scoreIterator -= scoreDifference;
			}

			DjipiApp::Brick brick = DjipiApp::Brick(
				i * BRICK_WIDTH + spaceBetweenBricks * (i + 0.5),
				j * BRICK_HEIGHT + spaceBetweenBricks * (j + 0.5) + SCORE_PANEL_SIZE,
				(BrickType) scoreIterator
			);
			bricks.push_back(brick);
		}
	}
}

void ResetBricks(vector<DjipiApp::Brick>& bricks)
{
	for (int i = 0; i < bricks.size(); i++)
	{
		bricks[i].Reset();
	}
}

void LoadScore(int points, int lives)
{
	//Render text
	SDL_Color textColor = { 255, 255, 255 };
	if (!gScoreTexture.LoadFromRenderedText("Score: " + to_string(points), textColor, gFont, gRenderer))
	{
		printf("Failed to render score texture!\n");
	}
	if (!gLivesTexture.LoadFromRenderedText("Lives: " + to_string(lives), textColor, gFont, gRenderer))
	{
		printf("Failed to render lives texture!\n");
	}
}

// Load a texture to display a gameover / start message
void LoadMessage(std::string message)
{
	SDL_Color textColor = { 255, 255, 255 };
	if (!gMessageTexture.LoadFromRenderedText(message, textColor, gFont, gRenderer))
	{
		printf("Failed to render message texture!\n");
	}
}

void LoadSounds()
{
	gBallCollisionSound = Mix_LoadWAV(BALL_TOUCH_SOUND_PATH);
	if (gBallCollisionSound == NULL)
	{
		cerr << "Failed to load Ball touch sound : " << Mix_GetError() << endl;
	}
	
	gPointScoreSound = Mix_LoadWAV(POINT_SCORE_SOUND_PATH);
	if (gPointScoreSound == NULL)
	{
		cerr << "Failed to load Point Score sound : " << Mix_GetError() << endl;
	}
	
	gLooseLifeSound = Mix_LoadWAV(LOOSE_LIFE_SOUND_PATH);
	if (gLooseLifeSound == NULL)
	{
		cerr << "Failed to load loose life sound : " << Mix_GetError() << endl;
	}
	
	gGameOverSound = Mix_LoadWAV(GAME_OVER_SOUND_PATH);
	if (gGameOverSound == NULL)
	{
		cerr << "Failed to load game over sound : " << Mix_GetError() << endl;
	}
	
	gWinSound = Mix_LoadWAV(GAME_WIN_SOUND_PATH);
	if (gWinSound == NULL)
	{
		cerr << "Failed to load game win sound : " << Mix_GetError() << endl;
	}
}

void LoadFont()
{
	//Open the font
	gFont = TTF_OpenFont(BIT_FONT_DIR_PATH, 60);
	if (gFont == NULL)
	{
		printf("Failed to load bit font! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		LoadScore(0, 3);
	}
}

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	Djipi::Window appWindow = Djipi::Window();
	appWindow.Init();

	gWindow = appWindow.GetWindow();
	gRenderer = appWindow.GetRenderer();

	// Time
	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	Djipi::Timer resetTimer = Djipi::Timer();

	// GAMEOBJECTS
	// Create your gameobjects here
	
	DjipiApp::Player player = DjipiApp::Player();
	DjipiApp::Ball ball = DjipiApp::Ball();

	vector<DjipiApp::Brick> bricks = {};
	LoadBricks(bricks);

	// UI
	LoadFont();
	LoadMessage("Press Space");

	// Sounds
	LoadSounds();
	
	// GAME LOOP
	while (!quit)
	{
		// EVENTS LOOP
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			// Handle your events here
			if (e.type == UserEvents::BRICK_DESTROYED)
			{
				Uint16 brickType = *static_cast<BrickType*>(e.user.data1);
				player.IncreaseScore(brickType);
				ball.IncreaseSpeed(brickType);
				Mix_PlayChannel(-1, gPointScoreSound, 0);

				LoadScore(player.GetScore(), player.GetLives());

				if (player.GetScore() >= 448)
				{
					SDL_Event OnGameWin = { UserEvents::GAME_WIN };
					SDL_PushEvent(&OnGameWin);
				}
			}
			
			if (e.type == UserEvents::BALL_OUT)
			{
				player.LooseLife();
				LoadScore(player.GetScore(), player.GetLives());
				showMessage = true;
				Mix_PlayChannel(-1, gLooseLifeSound, 0);

				if (player.GetLives() <= 0)
				{
					SDL_Event OnGameOver = { UserEvents::GAME_OVER };
					SDL_PushEvent(&OnGameOver);
				}
			}

			if (e.type == UserEvents::START_GAME)
			{
				showMessage = false;
			}

			if (e.type == UserEvents::GAME_OVER)
			{
				showMessage = true;
				LoadMessage("Game Over");
				resetTimer.Start();
				Mix_PlayChannel(-1, gGameOverSound, 0);
			}
			
			if (e.type == UserEvents::GAME_WIN)
			{
				showMessage = true;
				LoadMessage("You Win");
				resetTimer.Start();
				ball.Reset();
				Mix_PlayChannel(-1, gWinSound, 0);
			}

			if (e.type == UserEvents::BALL_TOUCH)
			{
				Mix_PlayChannel(-1, gBallCollisionSound, 0);
			}

			player.HandleEvent(e);
			
			if (!resetTimer.IsStarted())
			{
				ball.HandleEvent(e);
			}
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;

		// UPDATING
		// Updates methods here

		// Reset game
		if (resetTimer.IsStarted() && resetTimer.GetTicks() > RESET_TIME)
		{
			resetTimer.Stop();

			player.Reset();
			ResetBricks(bricks);

			LoadScore(player.GetScore(), player.GetLives());
			LoadMessage("Press Space");
		}

		player.Update(deltaTime);
		ball.Update(deltaTime);

		if (CheckCollision(ball.GetCollider(), player.GetCollider()))
		{
			ball.OnCollide(player);
		}

		for (int i = 0; i < bricks.size(); i++)
		{
			if (!bricks[i].IsDestroyed() && CheckCollision(ball.GetCollider(), bricks[i].GetCollider()))
			{
				bricks[i].OnCollide(ball);
			}
		}
		
		// RENDERING 
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

		// Render all objects in the scene here

		player.Render(gRenderer);
		ball.Render(gRenderer);

		for (int i = 0; i < bricks.size(); i++)
		{
			if (!bricks[i].IsDestroyed())
			{
				bricks[i].Render(gRenderer);
			}
		}

		// UI Renders
		gScoreTexture.Render(10, (SCORE_PANEL_SIZE - gScoreTexture.GetHeight()) / 2, gRenderer);
		gLivesTexture.Render(SCREEN_WIDTH - gLivesTexture.GetWidth() - 10, 
			(SCORE_PANEL_SIZE - gLivesTexture.GetHeight()) / 2, gRenderer);

		if (showMessage)
		{
			gMessageTexture.Render(SCREEN_WIDTH / 2 - gMessageTexture.GetWidth() / 2, SCREEN_HEIGHT / 2 + 50, gRenderer);
		}

		SDL_RenderPresent(gRenderer);
	}

	appWindow.Close();

	return 0;
}