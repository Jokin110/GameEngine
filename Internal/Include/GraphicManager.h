#pragma once
#include "Singleton.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include "ObjectManager.h"
#include "Text.h"

class GraphicManager : public Singleton<GraphicManager>
{
	friend class Singleton<GraphicManager>;

private:

	// Private constructor to avoid more than one instance
	GraphicManager() {};

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The window renderer
	SDL_Renderer* renderer = NULL;

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	vector<Object*> objectsToLoad;

	vector<Text*> texts;
	vector<Text*> textsToRemove;

	void RemoveTexts();

	/*****************************************************************************/

public:

	bool Init();

	void Update();

	void Destroy();

	int GetScreenWidth() { return SCREEN_WIDTH; }
	int GetScreenHeight() { return SCREEN_HEIGHT; }

	SDL_Renderer* GetRenderer();

	void AddObject(Object* _object) { objectsToLoad.push_back(_object); }
	void AddText(Text* _text) { texts.push_back(_text); }
	void RemoveText(Text* _text) { textsToRemove.push_back(_text); }

	/*****************************************************************************/

};

