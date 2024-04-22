#include "Bullet.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "MapManager.h"
#include <iostream>
#include "Enemy.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	_collider = new CollisionManager::Collider();
	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->width = _width;
	_collider->height = _height;
	_collider->type = CollisionManager::CT_BULLET;
	_collider->collisionsTag = CollisionManager::CT_ENEMY | CollisionManager::CT_WALL;
	_collider->entity = this;

	_collisionManager->AddCollider(_collider);
	_sprite = resourceManager->LoadAndGetGraphicID("images/entities.png");
	_animations[AN_UP].Init(24 * 32, _player * 32, 32, 32, 1, 1);
	_animations[AN_UP_RIGHT].Init(RECT_WIDTH * (24 + 1), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_DEAD].Init(19 * 32, 9 * 32, 32, 32, 4, 1);
	_bDeletable = false;
	_bIsMoving = true;
}

void Bullet::Update()
{
	if (_bIsMoving) {
		_position.x += _direction.x * _speed;
		_position.y += _direction.y * _speed;
	}

	CheckCollision();
	_animations[_currentAnimation].Update();

	_collider->x = _position.x;
	_collider->y = _position.y;
	if (_currentAnimation == AN_DEAD && _animations[_currentAnimation].IsFinished()) {
		_bDeletable = true;
	}
}

void Bullet::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
}

void Bullet::CheckCollision()
{
	MapManager* mapManager = MapManager::GetInstance();
	if (_collider->collisions.size() > 0) {
		for (int i = 0; i < _collider->collisions.size(); i++) {
			/*if (_collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				_life -= 10;
				if (_life <= 0) {
					_currentState = AN_DEAD;
					_currentAnimation = AN_DEAD;
				}
			} else */
			if (_collider->collisions[i].id == CollisionManager::CT_WALL || _collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				_currentAnimation = AN_DEAD;
				_bIsMoving = false;
			}
			if (_collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				Enemy* enemy = (Enemy*)_collider->collisions[i].entity;
				enemy->SetEnemyState(AN_DEAD);
			}
		}
	}
}
