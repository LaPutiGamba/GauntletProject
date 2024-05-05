#include "Object.h"
#include "VideoManager.h"

Object::Object()
{
	_type = OBJ_SIZE;
	_bDestroy = false;
}

void Object::Init()
{
	Entity::Init();

	_collider->type = CollisionManager::CT_OBJECT;
	_collider->collisionsTag = CollisionManager::CT_PLAYER;

	_collisionManager->AddCollider(_collider);
}

void Object::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
}