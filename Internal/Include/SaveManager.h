#pragma once

#include "Singleton.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

struct IntegerElement
{
	IntegerElement(string _id, int _data) { id = _id; data = _data; }
	string id;
	int data;
};

struct FloatElement
{
	FloatElement(string _id, float _data) { id = _id; data = _data; }
	string id;
	float data;
};

struct StringElement
{
	StringElement(string _id, string _data) { id = _id; data = _data; }
	string id;
	string data;
};

class SaveManager :public Singleton<SaveManager>
{
	friend class Singleton<SaveManager>;

private:
	vector<IntegerElement> integerData;
	vector<FloatElement> floatData;
	vector<StringElement> stringData;

	// Private constructor to avoid more than one instance
	SaveManager();
	void Save();

public:
	void Init();

	void DeleteAll();
	void DeleteKey(string key);
	bool HasKey(string key);
	int GetInt(string key, int defaultValue);
	float GetFloat(string key, float defaultValue);
	string GetString(string key, string defaultValue);
	void SetInt(string key, int value);
	void SetFloat(string key, float value);
	void SetString(string key, string value);

	void Destroy();
};