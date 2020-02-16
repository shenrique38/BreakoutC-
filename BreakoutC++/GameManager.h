#pragma once

#include "SDL.h";
#include <SDL_ttf.h>
#include <string>
#include <list>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>

using namespace std;

struct LText
{
	int x;
	int y;
	SDL_Texture * text_texture;
	SDL_Rect text_rect;
	TTF_Font *font;
	SDL_Color col;

	LText()
	{

	}

	void LoadFont(const std::string &path, int font_size, const std::string &message_text, const SDL_Color color, SDL_Renderer* gRenderer)
	{

		col.r = color.r;
		col.b = color.b;
		col.g = color.g;
		col.a = color.a;

		font = TTF_OpenFont(path.c_str(), font_size);

		auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), col);
		auto text_texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
		SDL_FreeSurface(text_surface);

		SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
		this->text_texture = text_texture;


	}

	void Display(const std::string &message_text, SDL_Renderer* gRenderer)
	{
		SDL_DestroyTexture(text_texture);

		auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), col);
		text_texture = SDL_CreateTextureFromSurface(gRenderer, text_surface);
		SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);

		SDL_Rect temp = SDL_Rect();
		temp.x = x;
		temp.y = y;
		temp.w = text_rect.w;
		temp.h = text_rect.h;

		SDL_RenderCopy(gRenderer, text_texture, NULL, &temp);
		SDL_FreeSurface(text_surface);
	}
};

enum GameSound
{
	S_EnemyDestroy,
	S_BorderBounce,
	S_BackgroundMusic,
	S_WarCry,
	S_Eating,
	S_BoatScale,
	S_Thunder,
	S_WinSound,
	S_LoseSound,
};

class GameManager
{
public:

	static Mix_Chunk *s_enemyDestroy;
	static Mix_Chunk *s_ballBounce;
	static Mix_Chunk *S_backgroundM;

	static Mix_Chunk *s_war_cry;
	static Mix_Chunk *s_thorArrival;
	static Mix_Chunk *s_boatScale;
	static Mix_Chunk *s_eating;

	static Mix_Chunk *s_win;
	static Mix_Chunk *s_lose;

	static LText * scoreText;
	static LText * livesText;
	static LText * finalScoreText;

	static SDL_Renderer* gRenderer;

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int blockW = 40;
	static  int const blockH = 20;

	static int Score;
	static int lives;
	static int FrameRate;
	static float DeltaTime;
	static bool showFinal;

	static int enemyCount;


	static void StartGame()
	{
		GameManager::Score = 0;
		GameManager::lives = 3;
		GameManager::enemyCount = 0;
		GameManager::showFinal = false;

		LoadFont();
		LoadAudio();
	}

	static void LoadFont()
	{
		SDL_Color col;
		col.r = 0;
		col.g = 0;
		col.b = 0;

		GameManager::scoreText = new LText();

		scoreText->LoadFont("Media/arial.ttf", 27, "Viva!!: 200", col, GameManager::gRenderer);
		scoreText->x = 110;
		scoreText->y = 20;

		GameManager::livesText = new LText();

		livesText->LoadFont("Media/arial.ttf", 27, "Viva!!: 200", col, GameManager::gRenderer);
		livesText->x = 695;
		livesText->y = 20;

		col.r = 255;
		col.g = 255;
		col.b = 255;

		GameManager::finalScoreText = new LText();

		finalScoreText->LoadFont("Media/arial.ttf", 27, "Viva!!: 200", col, GameManager::gRenderer);
		finalScoreText->x = (GameManager::SCREEN_WIDTH / 2) - 100;
		finalScoreText->y = (GameManager::SCREEN_HEIGHT / 2) - 80;

	}
	static void LoadAudio()
	{
		Mix_Chunk * temp = Mix_LoadWAV("Media/high.wav");;
		cout << Mix_GetError();

		GameManager::s_enemyDestroy = Mix_LoadWAV("Media/mob_death.wav");
		GameManager::s_ballBounce = Mix_LoadWAV("Media/wood_Hit.wav");
		GameManager::S_backgroundM = Mix_LoadWAV("Media/viking_background.wav");

		GameManager::s_eating = Mix_LoadWAV("Media/eating.wav");
		GameManager::s_war_cry = Mix_LoadWAV("Media/war_cry.wav");
		GameManager::s_thorArrival = Mix_LoadWAV("Media/thunder.wav");
		GameManager::s_boatScale = Mix_LoadWAV("Media/boat_scale.wav");

		GameManager::s_win = Mix_LoadWAV("Media/winMusic.wav");
		GameManager::s_lose = Mix_LoadWAV("Media/loseMusic.wav");

		Mix_AllocateChannels(16);

		Mix_VolumeChunk(GameManager::S_backgroundM, 3);
		Mix_PlayChannel(1, GameManager::S_backgroundM, 10);
	}

	static void AddPoint(int amount)
	{
		GameManager::Score += amount;
	}
	static void RemoveLive()
	{
		GameManager::lives--;
	}
	static void AddLive()
	{
		GameManager::lives++;
	}
	static void PlayAudio(GameSound name)
	{
		switch (name)
		{
		case S_EnemyDestroy:
			Mix_VolumeChunk(GameManager::s_enemyDestroy, 8);
			Mix_PlayChannel(2, GameManager::s_enemyDestroy, 0);
			break;
		case S_BorderBounce:
			Mix_VolumeChunk(GameManager::s_ballBounce, 60);
			Mix_PlayChannel(6, GameManager::s_ballBounce, 0);
			break;
		case S_WarCry:
			Mix_VolumeChunk(GameManager::s_war_cry, 15);
			Mix_PlayChannel(5, GameManager::s_war_cry, 0);
			break;
		case S_Eating:
			Mix_VolumeChunk(GameManager::s_eating, 20);
			Mix_PlayChannel(4, GameManager::s_eating, 0);
			break;
		case S_Thunder:
			Mix_VolumeChunk(GameManager::s_thorArrival, 15);
			Mix_PlayChannel(3, GameManager::s_thorArrival, 0);
			break;
		case S_BoatScale:
			Mix_VolumeChunk(GameManager::s_boatScale, 20);
			Mix_PlayChannel(4, GameManager::s_boatScale, 0);
			break;
		case S_WinSound:
			Mix_VolumeChunk(GameManager::s_win, 15);
			Mix_PlayChannel(4, GameManager::s_win, 0);
			break;
		case S_LoseSound:
			Mix_VolumeChunk(GameManager::s_lose, 15);
			Mix_PlayChannel(4, GameManager::s_lose, 0);
			break;
		}
	}
	static void ShowFinalScore()
	{
		GameManager::showFinal = true;
	}
	static void StopBackGroundMusic()
	{
		Mix_Pause(1);
	}

	static void DrawText()
	{
		scoreText->Display(std::to_string(GameManager::Score), GameManager::gRenderer);
		livesText->Display(std::to_string(GameManager::lives), GameManager::gRenderer);

		if(showFinal)
			finalScoreText->Display("Conquered Glory: "+std::to_string(GameManager::Score), GameManager::gRenderer);
	}

	GameManager();
	virtual ~GameManager();
};
