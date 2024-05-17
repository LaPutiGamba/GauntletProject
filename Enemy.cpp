#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "GameState.h"
#include <iostream>

Enemy::Enemy()
{
	_bIsAlive = false;
	_damage = 1;
	_life = 1;
	_speed = 1;
	_state = State::AN_IDLE;

}

Enemy::~Enemy()
{
	
}

void Enemy::Init()
{
	Entity::Init();
	
	_sprite = ResourceManager::GetInstance()->LoadAndGetGraphicID("images/entities.png");
	
	_position.x = 0;
	_position.y = 0;
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
	CheckEnemyCollision();
	_playerPosition = _player->GetPosition();
	GoToPlayer();
	_animations[_currentAnimation].Update();
	if (_currentAnimation == AN_DEAD && _animations[_currentAnimation].IsFinished()) {
		_bDeletable = true;
	}
	_lastPosition = _position;
	_collider->x = _position.x;
	_collider->y = _position.y;
}

void Enemy::CheckEnemyCollision()
{
	if (_currentAnimation == AN_DEAD) {
		return;
	}
	if (_collider->collisions.size() > 0) {
		for (int i = 0; i < _collider->collisions.size(); i++) {
			if (_collider->collisions[i].id == CollisionManager::CT_WALL) {
				if (_collider->colliderX) {
					_position.x = _lastPosition.x;
					_collider->x = _position.x;
				}
				else if (_collider->colliderY) {
					_position.y = _lastPosition.y;
					_collider->y = _position.y;
				}
				else {
					_position = _lastPosition;
				}
			}
		}
	}
}

void Enemy::GoToPlayer()
{
	if (_currentAnimation == AN_DEAD) {
		return;
	}
	if (_playerPosition.x < _position.x) {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP_LEFT;
			_currentState = AN_UP_LEFT;
		}
		else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN_LEFT;
			_currentState = AN_DOWN_LEFT;
		}
		else {
			_currentAnimation = AN_LEFT;
			_currentState = AN_LEFT;
		}
	}
	else if (_playerPosition.x > _position.x) {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP_RIGHT;
			_currentState = AN_UP_RIGHT;
		}
		else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN_RIGHT;
			_currentState = AN_DOWN_RIGHT;
		}
		else {
			_currentAnimation = AN_RIGHT;
			_currentState = AN_RIGHT;
		}
	}
	else {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP;
			_currentState = AN_UP;
		}
		else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN;
			_currentState = AN_DOWN;
		}
	}
	switch (_currentAnimation)
	{
		case AN_UP:
			_position.y -= 1;
			break;
		case AN_UP_RIGHT:
			_position.x += 1;
			_position.y -= 1;
			break;
		case AN_RIGHT:
			_position.x += 1;
			break;
		case AN_DOWN_RIGHT:
			_position.x += 1;
			_position.y += 1;
			break;
		case AN_DOWN:
			_position.y += 1;
			break;
		case AN_DOWN_LEFT:
			_position.x -= 1;
			_position.y += 1;
			break;
		case AN_LEFT:
			_position.x -= 1;
			break;
		case AN_UP_LEFT:
			_position.x -= 1;
			_position.y -= 1;
			break;
	}
}

void Enemy::SetEnemyState(State state)
{
	if (_currentAnimation == AN_DEAD) {
		return;
	}
	_currentAnimation = state;
	if (state == AN_DEAD) {
		GameState::GetInstance()->AddScore(200);
		GameState::GetInstance()->AddKills();
		_collisionManager->RemoveCollider(_collider);
		delete _collider;
	}
	

}



