#pragma once

#include "Singleton.h"
#include "Object.h"
#include <vector>

using namespace std;

class ObjectManager :public Singleton<ObjectManager>
{
	friend class Singleton<ObjectManager>;

private:

	// Private constructor to avoid more than one instance
	ObjectManager() {};

	vector<Object*> objects;
	vector<Object*> objectsToRemove;

	void RemoveObjects();

public:

	void Init();

	void Update(void);

	void Destroy();

	vector<Object*>* GetObjects() { return &objects; }

	void AddObject(Object* _object);
	void RemoveObject(Object* _object);
};