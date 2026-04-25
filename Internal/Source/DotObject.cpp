#include "DotObject.h"
#include "GraphicManager.h"
#include "TimeManager.h"

DotObject::DotObject(Vector2 _pos, bool _canMove, bool _collider, string _name) : Object()
{
	pos = _pos;

	//Initialize the velocity
	velocity = Vector2(0, 0);

	spritePath = "../../../../Media/cabezaFerran.bmp";

	sound = new AudioClip("../../../../Media/Sound/high.wav");
	music = new AudioClip("../../../../Media/Sound/music.wav", true, true);

	if (_canMove)
	{
		testText = new Text("../../../../Media/Fonts/lazy.ttf", 32, { 0, 0, 0 }, Vector2(GraphicManager::GetInstance().GetScreenWidth() / 2, GraphicManager::GetInstance().GetScreenHeight() / 2), Vector2(0.5, 0.5));
		testText->SetText("Hellooo, this is my text!");
	}

	collider = new BoxCollider(Vector2(111, 111), Vector2(0, 0), !_collider, this, "Dot");
	//colliders.push_back(&collider);

	canMove = _canMove;

	name = _name;
}

void DotObject::UpdateVelocity()
{
	bool keyPressed = false;

	velocity = Vector2(0, 0);

	velocity = Vector2(InputManager::GetInstance().GetJoystickAxis(0), InputManager::GetInstance().GetJoystickAxis(1));

	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_UP))
	{
		velocity = Vector2(velocity.GetX(), -DOT_VEL);
	}
	else if (InputManager::GetInstance().GetKey(SDL_SCANCODE_DOWN))
	{
		velocity = Vector2(velocity.GetX(), DOT_VEL);
	}

	if (InputManager::GetInstance().GetKey(SDL_SCANCODE_LEFT))
	{
		velocity = Vector2(-DOT_VEL, velocity.GetY());
	}
	else if (InputManager::GetInstance().GetKey(SDL_SCANCODE_RIGHT))
	{
		velocity = Vector2(DOT_VEL, velocity.GetY());
	}

	//velocity = Vector2(1, 1);
}

void DotObject::move()
{
	//Move the dot left or right
	pos += velocity.GetNormalized() * DOT_VEL * TimeManager::GetInstance().GetDeltaTime();

	//If the dot went too far to the left or right
	if ((pos.GetX() < GetWidth() / 2) || (pos.GetX() + GetWidth() / 2 > GraphicManager::GetInstance().GetScreenWidth()))
	{
		//Move back
		pos -= Vector2(velocity.GetNormalized().GetX() * DOT_VEL * TimeManager::GetInstance().GetDeltaTime(), 0);
	}

	//If the dot went too far up or down
	if ((pos.GetY() < GetHeight() / 2) || (pos.GetY() + GetHeight() / 2 > GraphicManager::GetInstance().GetScreenHeight()))
	{
		//Move back
		pos -= Vector2(0, velocity.GetNormalized().GetY() * DOT_VEL * TimeManager::GetInstance().GetDeltaTime());
	}
}

void DotObject::Start()
{
	Object::Start();

	velocity = Vector2(0, 0);

	printf("%d\n", SaveManager::GetInstance().GetInt("A", 0));
	SaveManager::GetInstance().SetInt("A", 3);
}

void DotObject::Update()
{
	Object::Update();

	UpdateVelocity();
	if (canMove)
		move();

	if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_I))
		rotation += 45;

	if (canMove)
	{
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_R))
		{
			testText->SetText("sdjlkfj");
			testText->SetActive(!testText->GetIsActive());
			music->Play();
		}
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_P))
			music->Pause();
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_G))
			sound->Play();
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_T))
			music->Stop();
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_F))
			EngineManager::GetInstance().Quit();
		if (InputManager::GetInstance().GetJoystickButtonDown(0))
		{
			//pos = Vector2(0, 0);
			EngineManager::GetInstance().Quit();
		}

		if (pos == Vector2(0, 0))
		{
			printf("Sheeeeesh\n");
		}
	}

	float fps = 1.0 / TimeManager::GetInstance().GetDeltaTime();
	printf("%f\n", fps);
	//testText->SetText(to_string(fps));

	if (TimeManager::GetInstance().GetTime() > 2)
	{
		//EngineManager::GetInstance().Quit();
	}

	if (collider->isTrigger())
	{
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_A))
		{
			SetActive(!isActive());
			printf("Now i'm %d\n", isActive());
		}

		if (InputManager::GetInstance().GetKeyUp(SDL_SCANCODE_M))
			printf("Key up\n");

		if (InputManager::GetInstance().GetMouseButtonDown(3))
			printf("Mouse down\n");

		if (InputManager::GetInstance().GetMouseButton(1))
			printf("Mouse hold\n");

		if (InputManager::GetInstance().GetMouseButtonUp(2))
			printf("Mouse up\n");
	}
}

void DotObject::Destroy()
{
	if (collider != NULL)
	{
		collider = NULL;
	}

	if (music != NULL)
	{
		music = NULL;
	}

	if (sound != NULL)
	{
		sound = NULL;
	}

	if (testText != NULL)
	{
		testText = NULL;
	}

	Object::Destroy();
}

void DotObject::OnCollisionEnter(Collider* _other)
{
	Object::OnCollisionEnter(_other);
}

void DotObject::OnCollisionExit(Collider* _other)
{
	Object::OnCollisionExit(_other);
}

void DotObject::OnCollisionStay(Collider* _other)
{
	Object::OnCollisionStay(_other);
}

void DotObject::OnTriggerEnter(Collider* _other)
{
	Object::OnTriggerEnter(_other);

	if (collider->isTrigger())
	{
		printf("Being destroyed\n");
		Destroy();
	}
}