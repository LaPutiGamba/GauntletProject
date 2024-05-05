#include "Enemy.h"
#include "CollisionManager.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	Entity::Init();

	_bIsAlive = true;

	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->type = CollisionManager::CT_ENEMY;
	_collider->collisionsTag = CollisionManager::CT_BULLET | CollisionManager::CT_PLAYER | CollisionManager::CT_WALL;

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


