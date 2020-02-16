#pragma once
#include "GameObject.h"

class PlayerPad : public GameObject
{
public:

	double deltaCtr;
	bool druged;
	float speed = 20;

	float oriW;
	float oriH;

	Texture boatFlip;
	Texture boat;

	PlayerPad();
	void KeyPress(SDL_Keycode key);
	void Update();
	void AddPowerUp(int type);

	virtual ~PlayerPad();
};

