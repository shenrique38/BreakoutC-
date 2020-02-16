#include "Thor.h"



Thor::Thor() : GameObject()
{
	deltaCtr = 0;
	idleIndex = 0;
	this->renderType = TextureT;
	float scale = .30;
	speed = 1;

	idleList[0].loadFromFile("Media/thor_idle1.png");
	idleList[0].mHeight *= scale;
	idleList[0].mWidth *= scale;

	idleList[1].loadFromFile("Media/thor_idle2.png");
	idleList[1].mHeight *= scale;
	idleList[1].mWidth *= scale;

	idleList[2].loadFromFile("Media/thor_idle3.png");
	idleList[2].mHeight *= scale;
	idleList[2].mWidth *= scale;

	idleList[3].loadFromFile("Media/thor_idle4.png");
	idleList[3].mHeight *= scale;
	idleList[3].mWidth *= scale;

	idleList[4].loadFromFile("Media/thor_idle5.png");
	idleList[4].mHeight *= scale;
	idleList[4].mWidth *= scale;

	texture = idleList[0];

	abiList[0].loadFromFile("Media/thor_abi1.png");
	abiList[0].mHeight *= scale;
	abiList[0].mWidth *= scale;

	abiList[1].loadFromFile("Media/thor_abi2.png");
	abiList[1].mHeight *= scale;
	abiList[1].mWidth *= scale;

	abiList[2].loadFromFile("Media/thor_abi3.png");
	abiList[2].mHeight *= scale;
	abiList[2].mWidth *= scale;

	abiList[3].loadFromFile("Media/thor_abi4.png");
	abiList[3].mHeight *= scale;
	abiList[3].mWidth *= scale;

	abiList[4].loadFromFile("Media/thor_abi5.png");
	abiList[4].mHeight *= scale;
	abiList[4].mWidth *= scale;

	abiList[5].loadFromFile("Media/thor_abi6.png");
	abiList[5].mHeight *= scale;
	abiList[5].mWidth *= scale;

	this->position = Vector2D(400, 800);
	limitDown = 600;
	limitUp = 800;
	speed = 1;
	state = 3;
	waiting = 0;
	thorTime = rand() % 1000 + 800;
	thorCtr = 0;

}

void Thor::Update()
{
	deltaCtr += GameManager::DeltaTime;
	thorCtr += GameManager::DeltaTime;

	if (state == 3)
	{
		if (thorCtr >= thorTime)
		{
			this->position.x = 400 + (rand() % 400 - 200);
			state = 0;
			GameManager::PlayAudio(S_Thunder);
		}
	}
	else if (state == 0) // going down
	{
		if (this->position.y >= limitDown)
		{
			this->position.y -= speed * GameManager::DeltaTime;
		}
		else
		{
			if (WaitingState())
			{
				state = 1;
				abiIndex = -1;
			}

		}
	}
	else if (state == 2) // going up
	{
		if (this->position.y <= limitUp)
		{
			this->position.y += speed * GameManager::DeltaTime;
		}
		else
		{
			state = 3;
			thorTime = rand() % 1000 + 800;
			thorCtr = 0;
		}
	}

	if (deltaCtr > 15.0)
	{
		deltaCtr = 0;
		idleIndex++;
		abiIndex++;

		if (state == 0 || state == 2)
		{
			this->texture = idleList[2 + idleIndex % 3];
		}
		else if (state == 1)
		{
			this->texture = abiList[abiIndex % 6];
			if (abiIndex >= 6)
			{
				idleIndex = 0;
				state = 2;
				PowerUp * up;

				int temp = rand() % 100;
				if (temp >= 70)
				{
					up = new PowerUp(0);
				}
				else
				{
					up = new PowerUp(1);
				}

				GameObject::AddObject(up);
				up->position.x = this->position.x + this->texture.mWidth;
				up->position.y = this->position.y - this->texture.mHeight + 50;
			}
		}


	}

}

bool Thor::WaitingState()
{
	waiting += GameManager::DeltaTime;
	if (waiting > 150)
	{
		waiting = 0;
		return true;
	}
	return false;

}


Thor::~Thor()
{
}
