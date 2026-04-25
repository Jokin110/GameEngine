#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include "Vector2.h"
#include "Sprite.h"

using namespace std;

class Text
{
private:
	TTF_Font* font;

	string text;
	string fontPath;
	int size;
	SDL_Color color;
	Vector2 pos;

	Vector2 anchors;
	
	Sprite renderSprite;
	bool isActive = true;
	float scale = 1;
public:
	Text(string font, int size = 32, SDL_Color color = { 0, 0, 0 }, Vector2 pos = Vector2(0, 0), Vector2 anchors = Vector2(0, 0));
	~Text() { Destroy(); }

	bool InitFont();

	TTF_Font* GetFont() { return font; }

	string GetText() { return text; }
	void SetText(string _text);

	float GetWidth() { return renderSprite.getWidth() * scale; }
	float GetHeight() { return renderSprite.getHeight() * scale; }

	SDL_Color GetColor() { return color; }
	Vector2 GetPosWithoutAnchors() { return Vector2(pos.GetX() - anchors.GetX() * GetWidth(), pos.GetY() - anchors.GetY() * GetHeight()); }
	Sprite* GetSprite() { return &renderSprite; }

	bool GetIsActive() { return isActive; }
	void SetActive(bool value) { isActive = value; }

	float GetScale() { return scale; }
	void SetScale(float value) { scale = value; }

	void Destroy();
};
