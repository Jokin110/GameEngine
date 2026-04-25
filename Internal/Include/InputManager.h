#pragma once

#include "Singleton.h"
#include "SDL.h"

/**
Input Manager class
*/
class InputManager :public Singleton<InputManager>
{
  /*****************************************************************************/
  friend class Singleton<InputManager>;
  /*****************************************************************************/

private:
	//Analog joystick dead zone
	const int JOYSTICK_DEAD_ZONE = 8000;

	// Keyboard state
	const Uint8* mCurrentKeyStates;
	Uint8 previousKeyStates[282];

	Uint32 currentMouseState;
	Uint32 previousMouseState;

	SDL_Joystick* gameController;
	Sint16 currentJoystickState;

	Uint8* currentButtonStates;
	Uint8* previousButtonStates;
	int numberOfButtons;

	// Private constructor to avoid more than one instance
	InputManager();

public:
  
	bool Init();

	void Update();
	void LateUpdate();

	bool GetKeyDown(int key);
	bool GetKey(int scanCode);
	bool GetKeyUp(int key);

	bool GetMouseButtonDown(int button);
	bool GetMouseButton(int button);
	bool GetMouseButtonUp(int button);

	float GetJoystickAxis(int axis);
	int GetJoystickAxisRaw(int axis);

	bool GetJoystickButtonDown(int button);
	bool GetJoystickButton(int button);
	bool GetJoystickButtonUp(int button);

	void Destroy();
};