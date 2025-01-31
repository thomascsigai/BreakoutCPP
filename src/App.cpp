// Defines application entry point.
//

#include <GameConfig.h>
#include <Djipi.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <vector>

#include <Player.h>
#include <Ball.h>
#include <Brick.h>

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The renderer 
SDL_Renderer* gRenderer = NULL;

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

int main(int argc, char* argv[])
{
	bool quit = false;

	SDL_Event e;

	Djipi::Window appWindow = Djipi::Window();
	appWindow.Init();

	gWindow = appWindow.GetWindow();
	gRenderer = appWindow.GetRenderer();

	Uint64 previousTime = SDL_GetTicks();
	Uint64 currentTime;
	double deltaTime;

	// GAMEOBJECTS
	// Create your gameobjects here
	
	DjipiApp::Player player = DjipiApp::Player();
	DjipiApp::Ball ball = DjipiApp::Ball();

	vector<DjipiApp::Brick> bricks = {};
	LoadBricks(bricks);
	
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
				cout << player.GetScore() << endl;
			}
			
			if (e.type == UserEvents::BALL_OUT)
			{
				player.LooseLife();
			}

			player.HandleEvent(e);
			ball.HandleEvent(e);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (double)(currentTime - previousTime) / 1000;
		previousTime = currentTime;

		// UPDATING
		// Updates methods here

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

		SDL_RenderPresent(gRenderer);
	}

	appWindow.Close();

	return 0;
}