#pragma once
#include "GameObject.h"
#include "PowerUp.h"

class Thor :	public GameObject
{
public:
	
	Texture idleList[5];
	Texture abiList[6];
	int idleIndex;
	int abiIndex;
	Vector2D direction;
	
	float speed;
	float limitDown;
	float limitUp;
	double waiting;

	int state; // 0 - going down, 1 - casting ability, 2 - going up, 3 - looking for

	double deltaCtr;
	double thorCtr;
	double thorTime;

	Thor();

	void Update();
	 bool WaitingState();

	virtual ~Thor();
};

