#include "GameObject.h"


GameObject::GameObject()
{
	this->ID = reinterpret_cast<uint32_t>(this);
	this->scale = Vector2D(1, 1);
	this->position = Vector2D(0, 0);
	this->hasCollision = true;
}

void GameObject::Render(SDL_Renderer* gRenderer)
{
	SDL_Rect temp;
	Rectangle rect = GetRect();
	temp.x = rect.x;
	temp.y = rect.y;
	temp.w = rect.w;
	temp.h = rect.h;

	if (this->renderType == RenderType::GeometryT)
	{
		temp.x = rect.x;
		temp.y = rect.y;
		temp.w = rect.w;
		temp.h = rect.h;

		SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 0xFF);
		SDL_RenderFillRect(gRenderer, &temp);
	}
	else if(this->renderType == RenderType::TextureT)
	{
		temp.x = this->texture.x + rect.x;
		temp.y = this->texture.y + rect.y;
		temp.w = this->texture.mWidth;
		temp.h = this->texture.mHeight;

		SDL_RenderCopy(gRenderer, this->texture.mTexture, NULL, &temp);
	}
}

void GameObject::Update()
{
}

void GameObject::KeyPress(SDL_Keycode key)
{
}

void GameObject::OnCollision(GameObject * other)
{
}


Rectangle GameObject::GetRect()
{
	int x = (int)(this->position.x - (this->rect.w / 2.f));
	int y = (int)(GameManager::SCREEN_HEIGHT - (this->position.y + (this->rect.h / 2.f)));
	int w = (int)(rect.w * scale.x);
	int h = (int)(rect.h * scale.y);

	return Rectangle(x,y,w,h);
}

GameObject::~GameObject()
{
}


list<GameObject*> * GameObject::gameObjList;
list<GameObject*> * GameObject::removePull;
list<GameObject*> * GameObject::addPull;
