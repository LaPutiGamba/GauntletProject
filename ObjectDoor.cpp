#include "ObjectDoor.h"
#include "SoundManager.h"
#include "SceneDirector.h"

ObjectDoor::ObjectDoor()
{
}

void ObjectDoor::Init()
{
    Object::Init();

    _collider->x = _position.x;
    _collider->y = _position.y;

    _animations[AN_IDLE].Init(12 * RECT_WIDTH, 9 * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, 1, 0);
}

void ObjectDoor::Update()
{
    _animations[_currentAnimation].Update();
}

void ObjectDoor::UseInteraction()
{
    auto* soundManager = SoundManager::GetInstance();
    const int channel = soundManager->PlayFromStart(soundManager->LoadAndGetSoundID("sounds/openDoor.ogg"), 0);
    soundManager->SetVolume(channel, 5);

    SceneDirector::GetInstance()->ChangeScene(SceneEnum::WIN);

    _camera->SetX(0);
    _camera->SetY(0);

    _bDeletable = true;
}
