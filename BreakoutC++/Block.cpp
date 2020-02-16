#include "Block.h"



Block::Block(Color color) : GameObject()
{
	this->renderType = TextureT;

	this->rect.x = 0;
	this->rect.y = 0;
	this->rect.w = 40;
	this->rect.h = 20;

	this->color = color;
	this->type = ObjType::Blocks;	

	flip = Texture();
	flap = Texture();
	flop = Texture();

	int random = (rand() % 550);
	if (random >= 0 && random < 150)
	{
		flip.loadFromFile("Media/drag1.png");
		flip.mHeight *= .15f;
		flip.mWidth *= .15f;

		flap.loadFromFile("Media/dragF1.png");
		flap.mHeight *= .15f;
		flap.mWidth *= .15f;

		flop.loadFromFile("Media/dragD1.png");
		flop.mHeight *= .15f;
		flop.mWidth *= .15f;
	}
	else if (random >= 150 && random < 290)
	{
		flip.loadFromFile("Media/drag2.png");
		flip.mHeight *= .15f;
		flip.mWidth *= .15f;

		flap.loadFromFile("Media/dragF2.png");
		flap.mHeight *= .15f;
		flap.mWidth *= .15f;

		flop.loadFromFile("Media/dragD2.png");
		flop.mHeight *= .15f;
		flop.mWidth *= .15f;
	}
	else if (random >= 290 && random < 400)
	{
		flip.loadFromFile("Media/drag3.png");
		flip.mHeight *= .15f;
		flip.mWidth *= .15f;

		flap.loadFromFile("Media/dragF3.png");
		flap.mHeight *= .15f;
		flap.mWidth *= .15f;

		flop.loadFromFile("Media/dragD3.png");
		flop.mHeight *= .15f;
		flop.mWidth *= .15f;
	}
	else
	{
		flip.loadFromFile("Media/drag4.png");
		flip.mHeight *= .15f;
		flip.mWidth *= .15f;

		flap.loadFromFile("Media/dragF4.png");
		flap.mHeight *= .15f;
		flap.mWidth *= .15f;

		flop.loadFromFile("Media/dragD4.png");
		flop.mHeight *= .15f;
		flop.mWidth *= .15f;
	}

	this->rect.w = flip.mWidth;
	this->rect.h = flip.mHeight;

	this->texture = flip;

	 now = 0;
	 last = SDL_GetPerformanceCounter();
	 deltaCtr = 0;
	 downSpeed = 4;
	 beingKilled = false;
}

void Block::OnCollision(GameObject * other)
{	
}

void Block::Update()
{
	deltaCtr += GameManager::DeltaTime;	

	if(deltaCtr > 10.0 && !beingKilled)
	{
		deltaCtr = 0;

		if (flipFlap)
		{
			flipFlap = false;
			this->texture = flip;
		}
		else
		{
			flipFlap = true;
			this->texture = flap;
		}

	}
	 
	if (beingKilled)
	{
		this->position.y -= downSpeed * GameManager::DeltaTime;
		if (this->position.y <= -10)
		{
			GameObject::RemoveObject(this);
		}

	}
	
	
}

void Block::Kill()
{
	hasCollision = false;
	// GameObject::RemoveObject(this);
	GameManager::AddPoint(5);
	GameManager::PlayAudio(S_EnemyDestroy);
	GameManager::enemyCount--;
	beingKilled = true;
	this->texture = flop;

}

Block::~Block()
{
}
