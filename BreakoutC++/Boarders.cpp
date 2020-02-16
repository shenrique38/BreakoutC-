#include "Boarders.h"


Boarders::Boarders(Side side) : GameObject()
{
	this->renderType = TextT;
	this->type = ObjType::Border;
	this->side = side;
	this->color = Color::Green();
	int length = 10;
	int pad = 13;

	switch (side)
	{
	case Left:
		rect.x = 0;
		rect.y = 0;
		rect.w = length;
		rect.h = GameManager::SCREEN_HEIGHT - pad;

		this->position.y = GameManager::SCREEN_HEIGHT / 2.f;
		break;
	case Right:
		rect.x = 0;
		rect.y = 0;
		rect.w = length;
		rect.h = GameManager::SCREEN_HEIGHT - pad;

		this->position.y = GameManager::SCREEN_HEIGHT / 2.f;
		this->position.x = GameManager::SCREEN_WIDTH;
		break;
	case Bottom:
		rect.x = 0;
		rect.y = 0;
		rect.w = GameManager::SCREEN_WIDTH - pad;
		rect.h = length;

		this->position.x = GameManager::SCREEN_WIDTH / 2.f;

		break;
	case Top:
		rect.x = 0;
		rect.y = 0;
		rect.w = GameManager::SCREEN_WIDTH - pad;
		rect.h = length;

		this->position.x = (GameManager::SCREEN_WIDTH / 2.f);
		this->position.y = GameManager::SCREEN_HEIGHT;
		break;
	}

}


Boarders::~Boarders()
{
}
