#include "Bullet.h"
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
	Entity::Init();

	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->type = CollisionManager::CT_BULLET;
	_collider->collisionsTag = CollisionManager::CT_ENEMY | CollisionManager::CT_WALL;

	_collisionManager->AddCollider(_collider);
	_animations[AN_UP].Init(24 * 32, _player * 32, 32, 32, 1, 1);
	_animations[AN_UP_RIGHT].Init(RECT_WIDTH * (24 + 1), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_RIGHT].Init(RECT_WIDTH * (24 + 2), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_DOWN_RIGHT].Init(RECT_WIDTH * (24 + 3), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_DOWN].Init(RECT_WIDTH * (24 + 4), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_DOWN_LEFT].Init(RECT_WIDTH * (24 + 5), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_LEFT].Init(RECT_WIDTH * (24 + 6), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_UP_LEFT].Init(RECT_WIDTH * (24 + 7), RECT_HEIGHT * _player, RECT_WIDTH, RECT_HEIGHT, 1, 1);
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
	bool deleteBullet = false;
	MapManager* mapManager = MapManager::GetInstance();
	if (_collider->collisions.size() > 0) {
		for (int i = 0; i < _collider->collisions.size(); i++) {
			if (_collider->collisions[i].id == CollisionManager::CT_WALL || _collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				_currentAnimation = AN_DEAD;
				_bIsMoving = false;
				deleteBullet = true;
			}
			if (_collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				Enemy* enemy = (Enemy*)_collider->collisions[i].entity;
			    if (enemy)
				  enemy->SetEnemyState(AN_DEAD);
				deleteBullet = true;
			}
			if (_collider->collisions[i].id == CollisionManager::CT_PLAYER && _player == 5) {
				GameState::GetInstance()->AddLife(-20);
				deleteBullet = true;
			}
		}
	}
	if (deleteBullet) {
		_collisionManager->RemoveCollider(_collider);
		delete _collider;
	}
}

void Bullet::SetPosition(int x, int y, int state)
{
	 _currentAnimation = (State)state; 
	 _position.x = x;
	 _position.y = y;
}
