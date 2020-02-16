
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include "Auxi.h"
#include "MapHangler.h"
#include "GameManager.h"
#include "GameObject.h"
#include <chrono>
#include <ctime>    

bool quit = false;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

SDL_Surface* background;
SDL_Renderer* gRenderer = NULL;

bool help;
int historyState;

bool Init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Breakout C#", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GameManager::SCREEN_WIDTH, GameManager::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		//Create renderer for window
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		Color cl = Color::Black();

		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, cl.r, cl.g, cl.b, 0xFF);

		IMG_Init(IMG_INIT_PNG);
		TTF_Init();

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

		GameObject::Init();
		GameManager::gRenderer = gRenderer;
	}

	return success;
}
bool LoadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
	if (gHelloWorld == NULL)
	{
		success = false;
	}

	return success;
}
void Close()
{
	//Deallocate surface
	SDL_FreeSurface(gHelloWorld);
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


void Draw()
{
	//Clear screen
	Color cl = Color::Black();
	SDL_SetRenderDrawColor(gRenderer, cl.r, cl.g, cl.b, 0xFF);

	SDL_RenderClear(gRenderer);


	for (list<GameObject*>::iterator i = GameObject::gameObjList->begin(); i != GameObject::gameObjList->end(); i++)
	{
		(**i).Render(gRenderer);
	}

	GameManager::DrawText();

	//Update screen
	SDL_RenderPresent(gRenderer);

}
void Update()
{
	for (list<GameObject*>::iterator i = GameObject::gameObjList->begin(); i != GameObject::gameObjList->end(); i++)
	{
		(**i).Update();
	}
}
void PullCheck()
{
	SDL_Event  e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			for (list<GameObject*>::iterator i = GameObject::gameObjList->begin(); i != GameObject::gameObjList->end(); i++)
			{
				(**i).KeyPress(e.key.keysym.sym);
			}
		}
	}

}
void Collision()
{
	for (list<GameObject*>::iterator i = GameObject::gameObjList->begin(); i != GameObject::gameObjList->end(); i++)
	{
		if (!(**i).hasCollision)
		{
			continue;
		}

		for (list<GameObject*>::iterator j = GameObject::gameObjList->begin(); j != GameObject::gameObjList->end(); j++)
		{
			if (!(**j).hasCollision)
			{
				continue;
			}

			if ((**i).ID != (**j).ID)
			{
				Vector2D test = Rectangle::GetIntersectionDepth((**i).GetRect(), (**j).GetRect());
				if (test.x != 0 && test.y != 0)
				{
					(**j).OnCollision((*i));
				}

			}
		}

	}
}


int main(int argc, char* args[])
{
	Init();
	GameManager::StartGame();


	auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	auto time = std::chrono::system_clock::now();
	int frameCount = 0;
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	MapHangler::LoadStory();
	MapHangler::ShowStory(0);

	help = false;

	while (!help) // help loop
	{
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() > 8)
		{
			if (historyState >= 4)
			{
				help = true;
			}
			else
			{
				historyState++;
				MapHangler::ShowStory(historyState);
				start = std::chrono::system_clock::now();
			}
		}
		GameObject::UpdateList();
		Draw();
	}

	MapHangler::StartGame();

	while (!quit) // game loop
	{
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (elapsed_seconds.count() > 1)
		{
			GameManager::FrameRate = frameCount;
			frameCount = 0;
			start = std::chrono::system_clock::now();

			//cout << GameManager::FrameRate << endl;
		}

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		double deltaTime = (double)((NOW - LAST) * 100 / (double)SDL_GetPerformanceFrequency());
		GameManager::DeltaTime = deltaTime;
		// cout << deltaTime << endl;

		PullCheck();
		Update();
		Collision();
		Draw();
		GameObject::UpdateList();
		frameCount++;

		if (GameManager::lives <= 0 || GameManager::enemyCount <= 0)
		{
			quit = true;
		}

	}

	MapHangler::ClearMapObjects();
	MapHangler::ShowFinalGameState(GameManager::enemyCount <= 0);
	if (GameManager::enemyCount <= 0)
	{
		GameManager::PlayAudio(S_WinSound);
	}
	else
	{
		GameManager::PlayAudio(S_LoseSound);
	}

	GameObject::UpdateList();
	GameManager::ShowFinalScore();
	GameManager::StopBackGroundMusic();


	quit = false;

	Draw();
	SDL_Delay(8000);

	//Free resources and close SDL
	Close();

	return 0;
}