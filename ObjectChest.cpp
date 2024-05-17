#include "ObjectChest.h"
#include "Player.h"

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
	Player* player = Player::GetInstance();
	player->SetScore(player->GetScore() + 100);

	_bDestroy = true;
}
