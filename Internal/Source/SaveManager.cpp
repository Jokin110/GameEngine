#include "SaveManager.h"

SaveManager::SaveManager()
{
	integerData.clear();
	floatData.clear();
	stringData.clear();
}

void SaveManager::Init()
{
	fstream file;

	file.open("data.txt", ios::in);

	string key;
	int intValue;
	float floatValue;
	string stringValue;

	int dataType = 0;
	int line = 0;

	if (!file)
		cout << "Couldn't load data file.\n";
	else
	{
		while (!file.eof())
		{
			if (line % 2 == 0)
			{
				file >> key;

				if (key == "--------")
				{
					dataType++;
					line++;
				}
			}
			else
			{
				switch (dataType)
				{
				case 0:
					file >> intValue;
					integerData.push_back(IntegerElement(key, intValue));
					break;
				case 1:
					file >> floatValue;
					floatData.push_back(FloatElement(key, floatValue));
					break;
				case 2:
					file >> stringValue;
					stringData.push_back(StringElement(key, stringValue));
					break;
				}
			}

			line++;
		}
		cout << "Data loaded!\n";
	}

	file.close();
}

void SaveManager::DeleteAll()
{
	integerData.clear();
	floatData.clear();
	stringData.clear();
}

void SaveManager::DeleteKey(string key)
{
	for (int i = 0; i < integerData.size(); i++)
	{
		if (integerData[i].id == key)
		{
			integerData.erase(integerData.begin() + i);
			return;
		}
	}
	for (int i = 0; i < floatData.size(); i++)
	{
		if (floatData[i].id == key)
		{
			floatData.erase(floatData.begin() + i);
			return;
		}
	}
	for (int i = 0; i < stringData.size(); i++)
	{
		if (stringData[i].id == key)
		{
			stringData.erase(stringData.begin() + i);
			return;
		}
	}
}

bool SaveManager::HasKey(string key)
{
	for (int i = 0; i < integerData.size(); i++)
	{
		if (integerData[i].id == key)
			return true;
	}
	for (int i = 0; i < floatData.size(); i++)
	{
		if (floatData[i].id == key)
			return true;
	}
	for (int i = 0; i < stringData.size(); i++)
	{
		if (stringData[i].id == key)
			return true;
	}

	return false;
}

int SaveManager::GetInt(string key, int defaultValue)
{
	int value = defaultValue;

	if (HasKey(key))
	{
		for (int i = 0; i < integerData.size(); i++)
		{
			if (integerData[i].id == key)
			{
				value = integerData[i].data;
			}
		}
	}

	return value;
}

float SaveManager::GetFloat(string key, float defaultValue)
{
	float value = defaultValue;

	if (HasKey(key))
	{
		for (int i = 0; i < floatData.size(); i++)
		{
			if (floatData[i].id == key)
			{
				value = floatData[i].data;
			}
		}
	}

	return value;
}

string SaveManager::GetString(string key, string defaultValue)
{
	string value = defaultValue;

	if (HasKey(key))
	{
		for (int i = 0; i < stringData.size(); i++)
		{
			if (stringData[i].id == key)
			{
				value = stringData[i].data;
			}
		}
	}

	return value;
}

void SaveManager::SetInt(string key, int value)
{
	if (HasKey(key))
	{
		for (int i = 0; i < integerData.size(); i++)
		{
			if (integerData[i].id == key)
			{
				integerData[i].data = value;
			}
		}
	}
	else
	{
		integerData.push_back(IntegerElement(key, value));
	}
}

void SaveManager::SetFloat(string key, float value)
{
	if (HasKey(key))
	{
		for (int i = 0; i < floatData.size(); i++)
		{
			if (floatData[i].id == key)
			{
				floatData[i].data = value;
			}
		}
	}
	else
	{
		floatData.push_back(FloatElement(key, value));
	}
}

void SaveManager::SetString(string key, string value)
{
	if (HasKey(key))
	{
		for (int i = 0; i < stringData.size(); i++)
		{
			if (stringData[i].id == key)
			{
				stringData[i].data = value;
			}
		}
	}
	else
	{
		stringData.push_back(StringElement(key, value));
	}
}

void SaveManager::Save()
{
	fstream file;

	file.open("data.txt", ios::out);

	for (int i = 0; i < integerData.size(); i++)
	{
		file << integerData[i].id << endl;
		file << integerData[i].data << endl;
	}
	file << "--------" << endl;
	for (int i = 0; i < floatData.size(); i++)
	{
		file << floatData[i].id << endl;
		file << floatData[i].data << endl;
	}
	file << "--------" << endl;
	for (int i = 0; i < stringData.size(); i++)
	{
		file << stringData[i].id << endl;
		file << stringData[i].data << endl;
	}

	integerData.clear();
	floatData.clear();
	stringData.clear();

	file.close();
}

void SaveManager::Destroy()
{
	Save();

	DestroySingleton();
}