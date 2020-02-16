#include "PlayerPad.h"



PlayerPad::PlayerPad() : GameObject()
{
	this->deltaCtr = 0;
	this->renderType = TextureT;

	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 120;
	this->rect.h = 20;

	this->color = Color::Pink();
	this->type = ObjType::PlayerPads;

	this->position.x = GameManager::SCREEN_WIDTH / 2.f;
	this->position.y = 60;

	float sca = 0.15f;



	boatFlip = Texture();
	boatFlip.loadFromFile("Media/vikingBoatF.png");

	oriH = boatFlip.mHeight;
	oriW = boatFlip.mWidth;

	boatFlip.y = -60;
	boatFlip.mHeight *= sca;
	boatFlip.mWidth *= sca;

	boat = Texture();
	boat.loadFromFile("Media/vikingBoat.png");
	boat.y = -60;
	boat.mHeight *= sca;
	boat.mWidth *= sca;

	this->texture = boatFlip;
	this->druged = false;
}

void PlayerPad::KeyPress(SDL_Keycode key)
{
	Rectangle rect;
	switch (key)
	{
	case SDLK_RIGHT:
		rect = GetRect();
		if ((rect.w + rect.x) < GameManager::SCREEN_WIDTH)
		{
			this->position.x += speed;
			texture = boatFlip;
		}
		break;
	case SDLK_LEFT:
		rect = GetRect();
		if (rect.x > 0)
		{
			this->position.x -= speed;
			texture = boat;
		}		
		break;
	}
}

void PlayerPad::Update()
{
	deltaCtr += GameManager::DeltaTime;
	if (druged && deltaCtr > 600)
	{
		this->rect.w = 120;
		this->rect.h = 20;

		druged = false;
		float sca = 0.15f;
		float posPad = -60;

		boatFlip.y = posPad;
		boatFlip.mHeight = oriH * sca;
		boatFlip.mWidth = oriW * sca;

		this->rect.w = boatFlip.mHeight;

		boat.y = posPad;
		boat.mHeight = oriH * sca;
		boat.mWidth = oriW * sca;
		this->texture = boat;
	}
}

void PlayerPad::AddPowerUp(int type)
{
	if (type == 1)
	{


		deltaCtr = 0;
		druged = true;

		float sca = 0.25f;
		float posPad = -120;

		boatFlip.y = posPad;
		boatFlip.mHeight = oriH * sca;
		boatFlip.mWidth = oriW * sca;

		this->rect.w = boatFlip.mHeight;

		boat.y = posPad;
		boat.mHeight = oriH * sca;
		boat.mWidth = oriW * sca;

		this->texture = boat;
	}
}


PlayerPad::~PlayerPad()
{
}
