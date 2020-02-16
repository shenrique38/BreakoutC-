#include "Ball.h"
#include "Boarders.h"
#include <math.h>

Ball::Ball() : GameObject()
{
	this->renderType = TextureT;
	this->type = ObjType::GoldBall;

	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 10;
	this->rect.h = 10;

	this->color = Color::Yellow();
	this->direction = Vector2D::Down();

	this->texture = Texture();
	texture.loadFromFile("Media/shield.png");

	texture.mHeight *= .15f;
	texture.mWidth *= .15f;

	this->rect.w = texture.mWidth;
	this->rect.h = texture.mHeight;

	colCycle = 0;
}

void Ball::Update()
{
	colCycle++;
	if (colCycle >= 20)
	{
		colCycle = 0;
		colCycleCtr = true;
	}

	this->direction.Normalize();
	this->position += direction * speed * GameManager::DeltaTime;
}

void Ball::OnCollision(GameObject * other)
{
	if (!colCycleCtr)
	{
		return;
	}
	colCycleCtr = false;
	Block * bk;
	switch (other->type)
	{
	case Blocks:

		bk = dynamic_cast<Block*>(other);
		bk->Kill();
		BlockCollision(other);
		GameManager::PlayAudio(S_BorderBounce);
		break;
	case PlayerPads:
		
		GameManager::PlayAudio(S_WarCry);
		PlayerPadCollision(other);
		break;
	case Border:
		Boarders * bd = dynamic_cast<Boarders*>(other);
		switch (bd->side)
		{
		case Left:
			direction = Vector2D::Reflect(direction, Vector2D::Right());
			GameManager::PlayAudio(S_BorderBounce);
			break;
		case Right:
			direction = Vector2D::Reflect(direction, Vector2D::Left());
			GameManager::PlayAudio(S_BorderBounce);
			break;
		case Top:
			direction = Vector2D::Reflect(direction, Vector2D::Down());
			GameManager::PlayAudio(S_BorderBounce);
			break;
		case Bottom:
			this->position = Vector2D(GameManager::SCREEN_WIDTH / 2.f, GameManager::SCREEN_HEIGHT / 2.f);
			this->direction = Vector2D::Down();
			GameManager::RemoveLive();
			break;
		}
		break;
	}
}

void Ball::PlayerPadCollision(GameObject * other)
{
	Rectangle rect = other->GetRect();
	float Arc = 50;
	float pos = this->position.x - rect.x;
	float halfW = rect.w / 2.f;
	float hitAngle;
	float convAng;
	double rad;

	if (pos > halfW)
	{
		//right
		hitAngle = (pos - halfW) / halfW;
		convAng = 90 - (Arc * hitAngle);

		rad = M_PI * convAng / 180.0;
		direction.x = (float)cosf(rad);
		direction.y = (float)sinf(rad);
	}
	else if (pos < halfW)
	{
		//left
		hitAngle = (halfW - pos) / halfW;
		convAng = 90 + (Arc * hitAngle);

		rad = M_PI * convAng / 180.0;
		direction.x = (float)cosf(rad);
		direction.y = (float)sinf(rad);
	}
	else
	{
		direction = Vector2D::Up();
	}

}

void Ball::BlockCollision(GameObject * other)
{
	Rectangle rect = other->GetRect();
	int bottomPoint = rect.y - rect.h;

	if (this->position.x < rect.x && this->position.y < rect.y)
	{
		//left
		direction = Vector2D::Reflect(direction, Vector2D::Left());
	}
	else if (this->position.x > rect.x && this->position.y > rect.y)
	{
		//top
		direction = Vector2D::Reflect(direction, Vector2D::Up());
	}
	else if (this->position.y > bottomPoint)
	{
		//right
		direction = Vector2D::Reflect(direction, Vector2D::Right());
	}
	else
	{
		direction = Vector2D::Reflect(direction, Vector2D::Down());
	}
}


Ball::~Ball()
{
}
