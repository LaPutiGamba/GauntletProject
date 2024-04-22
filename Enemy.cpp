#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	_sprite = resourceManager->LoadAndGetGraphicID("images/entities.png");
	
	_bIsAlive = true;
	_collider = new CollisionManager::Collider();
	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->width = _width;
	_collider->height = _height;
	_collider->type = CollisionManager::CT_ENEMY;
	_collider->collisionsTag = CollisionManager::CT_BULLET | CollisionManager::CT_PLAYER | CollisionManager::CT_WALL;
	_collider->entity = this;

	_collisionManager->AddCollider(_collider);

	_animations[AN_DEAD].Init(14 * 32, 9 * 32, 32, 32, 5, 1);
}

void Enemy::Update()
{
	if (_currentAnimation == AN_DEAD && _animations[_currentAnimation].IsFinished()) {
		_bIsAlive = false;
	}
}

void Enemy::GoToPlayer()
{

}


