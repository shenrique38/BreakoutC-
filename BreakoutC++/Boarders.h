#pragma once
#include "GameObject.h"

class Boarders : public GameObject
{
public:

	Side side;

	Boarders(Side side);
	virtual ~Boarders();
};

