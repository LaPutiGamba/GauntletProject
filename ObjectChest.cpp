#include "ObjectChest.h"
#include "GameState.h"
#include "SoundManager.h"

ObjectChest::ObjectChest()
{
}

void ObjectChest::Init()
{
	Object::Init();

	_collider->x = _position.x;
	_collider->y = _position.y;

	_animations[AN_IDLE].Init(7 * RECT_WIDTH, 9 * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, 3, 1);
}

void ObjectChest::Update()
{
	_animations[_currentAnimation].Update();
}

void ObjectChest::UseInteraction()
{
	GameState::GetInstance()->AddScore(100);
	auto* soundManager = SoundManager::GetInstance();

	int channel = soundManager->PlayFromStart(soundManager->LoadAndGetSoundID("sounds/collectGold.ogg"), 0);
    soundManager->SetVolume(channel, 5);
	_bDeletable = true;
}
