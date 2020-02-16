#pragma once
#include "GameObject.h"
#include "Boarders.h"
#include "PlayerPad.h"

class PowerUp : public GameObject
{
public:

	float speed;
	int powerUpType;// 0 - life, 1 - potion

	PowerUp(int type); // 0 - life, 1 - potion
	void Update();
	void OnCollision(GameObject * other);
	~PowerUp();
};

