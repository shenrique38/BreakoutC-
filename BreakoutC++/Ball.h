#pragma once
#include "GameObject.h"
#include "Block.h"

class Ball : public GameObject
{
public:

	Vector2D direction;
	float speed = 2.2f;
	bool colCycleCtr;
	int colCycle;

	Ball();
	void Update();
	void OnCollision(GameObject * other);
	void PlayerPadCollision(GameObject * other);
	void BlockCollision(GameObject * other);

	virtual ~Ball();
};

