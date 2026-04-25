#pragma once
#include "DotObject.h"

class GameManager // singleton
{
private:
	DotObject dot = DotObject(0, 0, true, true, "Dot 1");
	DotObject dot2 = DotObject(300, 300, false, true, "Dot 2");
	DotObject dot3 = DotObject(150, 100, false, false);

	bool created = false;

public:
	GameManager();

	void Start();
	void Update();
	void Destroy();
};

