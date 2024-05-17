#include "EnemyDoggy.h"
#include "VideoManager.h"
#include "GameState.h"

EnemyDoggy::EnemyDoggy()
{
	_bullets.clear();
}

EnemyDoggy::~EnemyDoggy()
{
}

void EnemyDoggy::Init()
{
	Enemy::Init();

	_animations[AN_UP].Init(0, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_RIGHT].Init(32, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_RIGHT].Init(32 * 2, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_RIGHT].Init(32 * 3, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN].Init(32 * 4, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_LEFT].Init(32 * 5, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_LEFT].Init(32 * 6, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_LEFT].Init(32 * 7, RECT_WIDTH * 5, RECT_WIDTH, RECT_HEIGHT, 3, 8);

	_currentAnimation = AN_DOWN_RIGHT;

	_position.x = 600;
	_position.y = 400;
	_shootCooldown = 1000;

	_shootTimer.Init();

	

}

void EnemyDoggy::Update()
{
	Enemy::Update();
	CheckShootDirection();
	UpdateDoggyBullets();


}

void EnemyDoggy::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
	for (size_t i = 0; i < _bullets.size(); i++) {
 		_bullets[i]->Render();
	}
}

void EnemyDoggy::UpdateDoggyBullets()
{
	size_t bulletsSize = _bullets.size();
	for (size_t i = 0; i < bulletsSize; i++) {
		_bullets[i]->Update();
		if (_bullets[i]->IsDeletable()) {
			delete _bullets[i];
			_bullets.erase(_bullets.begin() + i);
			bulletsSize--;
		}
	}
}

void EnemyDoggy::CheckShootDirection()
{
	switch (_currentAnimation) {
	case Entity::AN_UP:
		_shootDirection.x = 0;
		_shootDirection.y = -1;
		break;
	case Entity::AN_UP_RIGHT:
		_shootDirection.x = 1;
		_shootDirection.y = -1;
		break;
	case Entity::AN_RIGHT:
		_shootDirection.x = 1;
		_shootDirection.y = 0;
		break;
	case Entity::AN_DOWN_RIGHT:
		_shootDirection.x = 1;
		_shootDirection.y = 1;
		break;
	case Entity::AN_DOWN:
		_shootDirection.x = 0;
		_shootDirection.y = 1;
		break;
	case Entity::AN_DOWN_LEFT:
		_shootDirection.x = -1;
		_shootDirection.y = 1;
		break;
	case Entity::AN_LEFT:
		_shootDirection.x = -1;
		_shootDirection.y = 0;
		break;
	case Entity::AN_UP_LEFT:
		_shootDirection.x = -1;
		_shootDirection.y = -1;
		break;

	}
	Shoot();
}

void EnemyDoggy::Shoot()
{
	if (_shootTimer.GetTicks() < _shootCooldown) {
		return;
	}
	_shootTimer.StartTimer();
	Bullet* bullet = new Bullet();
	bullet->SetPlayer(GameState::EN_DOGGY);
	bullet->Init();
	bullet->SetPosition(_position.x + _shootDirection.x * 32, _position.y + _shootDirection.y * 32, (int)_currentState - 1);
	bullet->SetDirection(_shootDirection);
	bullet->SetSpeed(20);
	bullet->SetBulletColliderTags(CollisionManager::CT_PLAYER | CollisionManager::CT_WALL);
	_bullets.push_back(bullet);
}
