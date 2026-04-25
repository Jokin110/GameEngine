#include "Text.h"
#include "GraphicManager.h"

Text::Text(string _font, int _size, SDL_Color _color, Vector2 _pos, Vector2 _anchors)
{
	font = NULL;

	fontPath = _font;
	size = _size;
	color = _color;
	pos = _pos;
	anchors = _anchors;

	text = "New Text";

	GraphicManager::GetInstance().AddText(this);

	isActive = true;
	scale = 1;
}

bool Text::InitFont()
{
	font = TTF_OpenFont(fontPath.c_str(), size);

	return font != NULL;
}

void Text::SetText(string _text)
{
	text = _text;

	renderSprite.loadFromRenderedText(text, font, color);
}

void Text::Destroy()
{
	if (font != NULL)
	{
		TTF_CloseFont(font);
		font = NULL;
	}
}