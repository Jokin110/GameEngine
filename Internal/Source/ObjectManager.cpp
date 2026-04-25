#include "ObjectManager.h"

void ObjectManager::Init()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Start();
	}
}

void ObjectManager::Update(void)
{
	RemoveObjects();

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] != NULL)
			objects[i]->Update();
	}
}

void ObjectManager::Destroy()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] != NULL)
		{
			objects[i]->Destroy();
			//delete objects[i];
			objects[i] = NULL;
		}
	}

	DestroySingleton();
}

void ObjectManager::AddObject(Object* _object)
{
	objects.push_back(_object);
}

void ObjectManager::RemoveObject(Object* _object)
{
	objectsToRemove.push_back(_object);
}

void ObjectManager::RemoveObjects()
{
	while (objectsToRemove.size() > 0)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			Object* objectToRemove = objectsToRemove[0];
			if (objects[i] == objectToRemove)
			{
				objects.erase(objects.begin() + i);
				objectsToRemove.erase(objectsToRemove.begin());

				//delete objectToRemove;
				objectToRemove = NULL;

				break;
			}
		}
	}
}