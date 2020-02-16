#include "PowerUp.h"



PowerUp::PowerUp(int type)
{
	this->renderType = TextureT;
	this->texture = Texture();
	float scale = 0.1f;
	this->type = ObjType::Power;
	this->powerUpType = type;
	speed = 1;

	if (type == 0)
	{
		this->texture.loadFromFile("Media/meat.png");
		texture.mHeight *= scale;
		texture.mWidth *= scale;
		
	}
	else if (type == 1)
	{
		this->texture.loadFromFile("Media/potion.png");
		texture.mHeight *= scale;
		texture.mWidth *= scale;
	
	}


}

void PowerUp::Update()
{
	this->position.y -= speed * GameManager::DeltaTime;

}

void PowerUp::OnCollision(GameObject * other)
{
	Boarders * bd;



	switch (other->type)
	{
	case Border:

		bd = dynamic_cast<Boarders*>(other);
		if (bd->side == Bottom)
		{
			GameObject::RemoveObject(this);
		}

		break;

	case PlayerPads:

		PlayerPad * pd = dynamic_cast<PlayerPad*>(other);
		GameObject::RemoveObject(this);
		GameManager::AddPoint(50);

		if (powerUpType == 0)
		{
			GameManager::PlayAudio(S_Eating);
			GameManager::AddLive();
		}
		else
		{
			pd->AddPowerUp(1);
			GameManager::PlayAudio(S_BoatScale);
		}

		break;
	}

}


PowerUp::~PowerUp()
{
}
