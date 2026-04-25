#include "InputManager.h"

InputManager::InputManager()
{
	mCurrentKeyStates = NULL;

	for (int i = 0; i < 282; i++)
	{
		previousKeyStates[i] = 0;
	}

	currentMouseState = 0;
	previousMouseState = 0;

	gameController = NULL;
	currentJoystickState = 0;

	currentButtonStates = NULL;
	previousButtonStates = NULL;
	numberOfButtons = 0;
}

bool InputManager::Init()
{
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Load joystick
			gameController = SDL_JoystickOpen(0);
			if (gameController == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				numberOfButtons = SDL_JoystickNumButtons(gameController);
			}
		}
	}

	mCurrentKeyStates = SDL_GetKeyboardState(NULL);

	currentButtonStates = new Uint8[numberOfButtons];
	previousButtonStates = new Uint8[numberOfButtons];

	return success;
}

void InputManager::Update()
{
	mCurrentKeyStates = SDL_GetKeyboardState(NULL);

	currentMouseState = SDL_GetMouseState(NULL, NULL);

	for (int i = 0; i < numberOfButtons; i++)
	{
		currentButtonStates[i] = SDL_JoystickGetButton(gameController, i);
	}
}

void InputManager::LateUpdate()
{
	for (int i = 0; i < 282; i++)
	{
		previousKeyStates[i] = mCurrentKeyStates[i];
	}

	previousMouseState = currentMouseState;

	for (int i = 0; i < numberOfButtons; i++)
	{
		previousButtonStates[i] = currentButtonStates[i];
	}
}

bool InputManager::GetKeyDown(int keyCode)
{
	return (!previousKeyStates[keyCode] && mCurrentKeyStates[keyCode]);
}

bool InputManager::GetKey(int scanCode)
{
	return mCurrentKeyStates[scanCode];
}

bool InputManager::GetKeyUp(int keyCode)
{
	return (previousKeyStates[keyCode] && !mCurrentKeyStates[keyCode]);
}

bool InputManager::GetMouseButtonDown(int button)
{
	return (!(previousMouseState & SDL_BUTTON(button)) && (currentMouseState & SDL_BUTTON(button)));
}

bool InputManager::GetMouseButton(int button)
{
	return currentMouseState & SDL_BUTTON(button);
}

bool InputManager::GetMouseButtonUp(int button)
{
	return ((previousMouseState & SDL_BUTTON(button)) && !(currentMouseState & SDL_BUTTON(button)));
}

float InputManager::GetJoystickAxis(int axis)
{
	currentJoystickState = SDL_JoystickGetAxis(gameController, axis);
	float value = 0;

	if (currentJoystickState < -JOYSTICK_DEAD_ZONE)
		value = (currentJoystickState + JOYSTICK_DEAD_ZONE) / (32768.0 - JOYSTICK_DEAD_ZONE);
	else if (currentJoystickState > JOYSTICK_DEAD_ZONE)
		value = (currentJoystickState - JOYSTICK_DEAD_ZONE) / (32767.0 - JOYSTICK_DEAD_ZONE);

	return value;
}

int InputManager::GetJoystickAxisRaw(int axis)
{
	currentJoystickState = SDL_JoystickGetAxis(gameController, axis);
	int value = 0;

	if (currentJoystickState < -JOYSTICK_DEAD_ZONE)
		value = -1;
	else if (currentJoystickState > JOYSTICK_DEAD_ZONE)
		value = 1;

	return value;
}

bool InputManager::GetJoystickButtonDown(int button)
{
	return (!previousButtonStates[button] && currentButtonStates[button]);
}

bool InputManager::GetJoystickButton(int button)
{
	return currentButtonStates[button];
}

bool InputManager::GetJoystickButtonUp(int button)
{
	return (previousButtonStates[button] && !currentButtonStates[button]);
}

void InputManager::Destroy()
{
	mCurrentKeyStates = NULL;

	delete currentButtonStates;
	currentButtonStates = NULL;
	delete previousButtonStates;
	previousButtonStates = NULL;

	SDL_JoystickClose(gameController);
	gameController = NULL;

	SDL_Quit();

	DestroySingleton();
}

/*****************************************************************************/

//SDL_SCANCODE_UP
//SDL_SCANCODE_DOWN
//SDL_SCANCODE_LEFT
//SDL_SCANCODE_RIGHT