#pragma once
#include "Auxi.h"
#include "GameManager.h"
#include <iostream>

using namespace std;

using std::string;
using std::list;

class GameObject
{

public:

	static list<GameObject*> * gameObjList;
	static list<GameObject*> *  removePull;
	static list<GameObject*> *  addPull;

	Uint32 ID;
	ObjType type;
	RenderType renderType;

	bool hasCollision;


	Vector2D position;
	Vector2D scale;
	
	Text text;
	Texture texture;

	Rectangle rect;
	Color color;


	GameObject();
	virtual void Render(SDL_Renderer* gRenderer);
	virtual void Update();
	virtual void KeyPress(SDL_Keycode key);
	virtual void OnCollision(GameObject* other);

	Rectangle GetRect();

	
	virtual ~GameObject();


	static void Init()
	{
		gameObjList = new list < GameObject* >;
		removePull = new list < GameObject* >;
		addPull = new list < GameObject* >;
	}
	static void AddObject(GameObject * obj)
	{
		addPull->push_back(obj);
	}
	static void RemoveObject(GameObject * obj)
	{
		removePull->push_back(obj);
	}
	static void UpdateList()
	{
		for (list<GameObject*>::iterator i = GameObject::removePull->begin(); i != GameObject::removePull->end(); i++)
		{
			(*gameObjList).remove((*i));
		}
		removePull->clear();

		for (list<GameObject*>::iterator i = GameObject::addPull->begin(); i != GameObject::addPull->end(); i++)
		{
			(*gameObjList).push_back((*i));
		}
		addPull->clear();
	}
};

