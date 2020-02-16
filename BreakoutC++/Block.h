#pragma once
#include "GameObject.h"
#include <chrono>
#include <ctime>    

class Block : public GameObject
{
public:

	Texture flip;
	Texture flap;
	Texture flop;
	bool flipFlap;

	Uint64 now;
	Uint64 last;

	double deltaCtr;
	float downSpeed;
	bool beingKilled;

	Block(Color color);

	void OnCollision(GameObject * other);
	void Update();
	void Kill();

	virtual ~Block();
};

