#pragma once

#include <sstream>
#include <math.h>
#include <list>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include "Rectangle.h"
#include "GameManager.h"

using namespace std;

using std::list;

enum ObjType
{
	Blocks,
	PlayerPads,
	GoldBall,
	Border,
	Power,
};

enum Side
{
	Left,
	Right,
	Bottom,
	Top,
};

enum RenderType
{
	GeometryT,
	TextureT,
	TextT,
};

struct Color  //representa uma cor
{
	int r; //red
	int g; //green
	int b; //blue
	int a;

	Color()
	{
		r = g = b = 0;
		a = 0;
	}
	Color(int red, int green, int blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	static Color Red()
	{
		return Color(255, 0, 0);
	}
	static Color Blue()
	{
		return Color(0, 0, 255);
	}
	static Color Green()
	{
		return Color(0, 255, 0);
	}
	static Color White()
	{
		return Color(255, 255, 255);
	}
	static Color Black()
	{
		return Color(0, 0, 0);
	}
	static Color Aqua()
	{
		return Color(0, 255, 255);
	}
	static Color Pink()
	{
		return Color(255, 0, 255);
	}
	static Color Yellow()
	{
		return Color(255, 255, 0);
	}
};

struct Texture
{
	SDL_Texture* mTexture;
	Rectangle rect;
	int x, y;
	int mWidth;
	int mHeight;

	Texture()
	{

	}
	void loadFromFile(std::string path)
	{
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());

		//SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(GameManager::gRenderer, loadedSurface);

		x = y = 0;
		mWidth = loadedSurface->w;
		mHeight = loadedSurface->h;

		SDL_FreeSurface(loadedSurface);
	}

};

struct Text
{
	SDL_Texture * text_texture;
	SDL_Rect text_rect;

	Text()
	{
	
	}

	void LoadFont(const std::string &path, int font_size, const std::string &message_text, const Color color)
	{
		SDL_Color col;
		col.r = color.r;
		col.b = color.b;
		col.g = color.g;
		col.a = color.a;

		TTF_Font *font = TTF_OpenFont(path.c_str(), font_size);

		auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), col);
		auto text_texture = SDL_CreateTextureFromSurface(GameManager::gRenderer, text_surface);
		SDL_FreeSurface(text_surface);

		SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
		this->text_texture = text_texture;
		
		
	}

	void Display()
	{

	}

	

};