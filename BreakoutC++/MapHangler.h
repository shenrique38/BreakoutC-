#pragma once
#include "GameManager.h"
#include "GameObject.h"
#include "Boarders.h"
#include "Block.h"
#include "PlayerPad.h"
#include "Ball.h"
#include "Thor.h"

class MapHangler
{
public:

	static GameObject history[7];

	MapHangler();

	static void StartGame()
	{
	
	    SpawnEnvirionment();
		SpawnTextObjects();
		SpawnBorders();
		SpawnPlayerPad();
		SpawnGoldenBall();
		SpawnThor();
		SpawnLevel1Blocks();
	}

	static void LoadStory()
	{
		float posX = GameManager::SCREEN_WIDTH / 4;
		float posY = GameManager::SCREEN_HEIGHT -50;

		history[0] = GameObject();
		history[0].texture = Texture();
		history[0].texture.loadFromFile("Media/history1.png");
		history[0].renderType = RenderType::TextureT;
		history[0].position.x = posX;
		history[0].position.y = posY;
		history[0].hasCollision = false;

		history[1] = GameObject();
		history[1].texture = Texture();
		history[1].texture.loadFromFile("Media/history2.png");
		history[1].renderType = RenderType::TextureT;
		history[1].position.x = posX;
		history[1].position.y = posY;
		history[1].hasCollision = false;

		history[2] = GameObject();
		history[2].texture = Texture();
		history[2].texture.loadFromFile("Media/history3.png");
		history[2].renderType = RenderType::TextureT;
		history[2].position.x = posX;
		history[2].position.y = posY;
		history[2].hasCollision = false;

		history[3] = GameObject();
		history[3].texture = Texture();
		history[3].texture.loadFromFile("Media/history4.png");
		history[3].renderType = RenderType::TextureT;
		history[3].position.x = posX;
		history[3].position.y = posY;
		history[3].hasCollision = false;

		history[4] = GameObject();
		history[4].texture = Texture();
		history[4].texture.loadFromFile("Media/history5.png");
		history[4].renderType = RenderType::TextureT;
		history[4].position.x = posX;
		history[4].position.y = posY;
		history[4].hasCollision = false;

		history[5] = GameObject();
		history[5].texture = Texture();
		history[5].texture.loadFromFile("Media/wonImg.png");
		history[5].renderType = RenderType::TextureT;
		history[5].position.x = posX;
		history[5].position.y = posY;
		history[5].hasCollision = false;

		history[6] = GameObject();
		history[6].texture = Texture();
		history[6].texture.loadFromFile("Media/lostImg.png");
		history[6].renderType = RenderType::TextureT;
		history[6].position.x = posX;
		history[6].position.y = posY;
		history[6].hasCollision = false;

	}
	static void ShowStory(int part)
	{
		GameObject::AddObject(&history[part]);
	}
	static void ClearStory()
	{
		for (int i = 0; i < 5; i++)
		{
			GameObject::RemoveObject(&history[i]);
		}
	}


	static void ClearMapObjects()
	{
		for (list<GameObject*>::iterator i = GameObject::gameObjList->begin(); i != GameObject::gameObjList->end(); i++)
		{
			GameObject::RemoveObject(*i);
		}
	}
	static void ShowFinalGameState(bool won)
	{
		if (won)
		{
			GameObject::AddObject(&history[5]);
		}
		else
		{
			GameObject::AddObject(&history[6]);
		}
	}


	static void SpawnTextObjects()
	{	

		GameObject * score = new GameObject();
		score->texture = Texture();
		score->texture.loadFromFile("Media/score.png");
		score->renderType = RenderType::TextureT;
		score->position.x = 10;
		score->position.y = GameManager::SCREEN_HEIGHT - 10;
		score->hasCollision = false;
		score->texture.mWidth *= .15;
		score->texture.mHeight *= .15;
		GameObject::gameObjList->push_back(score);

		GameObject * lives = new GameObject();
		lives->texture = Texture();
		lives->texture.loadFromFile("Media/lives.png");
		lives->renderType = RenderType::TextureT;
		lives->position.x = 580;
		lives->position.y = GameManager::SCREEN_HEIGHT - 10;
		lives->hasCollision = false;
		lives->texture.mWidth *= .15;
		lives->texture.mHeight *= .15;
		GameObject::gameObjList->push_back(lives);
	}

	static void SpawnEnvirionment()
	{
		GameObject * background;

		background = new GameObject();
		background->texture = Texture();
		background->texture.loadFromFile("Media/background.png");
		background->renderType = RenderType::TextureT;
		background->position.x = 0;
		background->position.y = 600;
		background->hasCollision = false;
		background->texture.mWidth = GameManager::SCREEN_WIDTH;
		background->texture.mHeight = GameManager::SCREEN_HEIGHT;
		GameObject::gameObjList->push_back(background);

		GameObject * water;
		for (int i = 1; i < 15; i++)
		{
			water = new GameObject();
			water->texture = Texture();
			water->texture.loadFromFile("Media/water.png");
			water->renderType = RenderType::TextureT;
			water->position.x = 60 *i;
			water->position.y = 0;
			water->rect.w = water->texture.mWidth;
			water->rect.h = water->texture.mHeight;
			water->hasCollision = false;
			water->scale = Vector2D(.5f, .5f);

			GameObject::gameObjList->push_back(water);
		}

		
	}
	static void SpawnBorders()
	{
		Boarders * bTop = new Boarders(Side::Top);
		Boarders * bLeft = new Boarders(Side::Left);

		Boarders * bBottom = new Boarders(Side::Bottom);
		Boarders * bRight = new Boarders(Side::Right);

		GameObject::gameObjList->push_back(bLeft);
		GameObject::gameObjList->push_back(bTop);
		GameObject::gameObjList->push_back(bBottom);
		GameObject::gameObjList->push_back(bRight);
	}
	static void SpawnPlayerPad()
	{
		PlayerPad * player = new PlayerPad();
		GameObject::gameObjList->push_back(player);
	}
	static void SpawnGoldenBall()
	{
		Ball * ball = new Ball();
		GameObject::AddObject(ball);
		ball->position = Vector2D(GameManager::SCREEN_WIDTH / 2.f, GameManager::SCREEN_HEIGHT / 2.f);
	}
	static void SpawnThor()
	{
		Thor * thor = new Thor();
		GameObject::gameObjList->push_back(thor);

	}
	
	static void SpawnLevel1Blocks()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 12; j++)
			{
				Block * block = new Block(Color::Red());
				block->position.x = j * 50 + 110;
				block->position.y = (GameManager::SCREEN_HEIGHT - 100) - (i * 30);

				GameObject::gameObjList->push_back(block);
				GameManager::enemyCount++;
			}
		}
	}
	
	~MapHangler();
};

