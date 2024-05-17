#include "Player.h"
#include "VideoManager.h"
#include "Timer.h"
#include <iostream>
#include "MapManager.h"
#include "Enemy.h"

Player* Player::_pInstance = NULL;

Player::Player()
{
	_player = GameState::PL_WARRIOR;
	_currentIdleState = AN_IDLE;
	_currentState = AN_IDLE;
	_currentAnimation = 0;
	_lastNonIdleState = AN_IDLE;
	_playerState = AN_IDLE;
	_endurance = 0;
	_strength = 0;
	_speed = 0;
	_shootCooldown = 0;
	_position = { 0, 0 };
	_sprite = 0;
	_cutRect = { 0, 0 };
	_drawRect = { 0, 0 };
	_shootDirection = { 0, 0 };
	_lastPosition = { 0, 0 };
	_bullets.clear();
}

void Player::Init()
{
	Entity::Init();

	InputManager* inputManager = InputManager::GetInstance();

	_cutRect = { 0, 0 };
	_drawRect = { 0, 0 };

	_position = { 550, 300 };

	_currentAnimation = 0;
	_currentState = AN_IDLE;
	_endurance = 0;
	_strength = 0;
	_speed = 0;
	_shootCooldown = 250;
	_lastNonIdleState = AN_IDLE;
	_player = GameState::PL_WARRIOR;

	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->type = CollisionManager::CT_PLAYER;
	_collider->collisionsTag = CollisionManager::CT_ENEMY | CollisionManager::CT_WALL | CollisionManager::CT_OBJECT;

	_collisionManager->AddCollider(_collider);
	_lastPosition = _position;
	_shootTimer.Init();
	_lifeTimer.Init();
	_killEnemyTimer.Init();
}

void Player::LoadCharacter()
{
	_player = GameState::GetInstance()->GetPlayerSelected();
	int playerPos = _player * 32;
	_animations[AN_IDLE].Init(0, playerPos, RECT_WIDTH, RECT_HEIGHT, 1, 1);
	_animations[AN_UP].Init(0, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_RIGHT].Init(32, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_RIGHT].Init(32 * 2, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_RIGHT].Init(32 * 3, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN].Init(32 * 4, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_DOWN_LEFT].Init(32 * 5, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_LEFT].Init(32 * 6, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_UP_LEFT].Init(32 * 7, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_SHOOTING].Init(32 * _currentState, playerPos, RECT_WIDTH, RECT_HEIGHT, 3, 8);
	_animations[AN_SHOOTING_UP] = _animations[AN_UP];
	_animations[AN_SHOOTING_UP_RIGHT] = _animations[AN_UP_RIGHT];
	_animations[AN_SHOOTING_RIGHT] = _animations[AN_RIGHT];
	_animations[AN_SHOOTING_DOWN_RIGHT] = _animations[AN_DOWN_RIGHT];
	_animations[AN_SHOOTING_DOWN] = _animations[AN_DOWN];
	_animations[AN_SHOOTING_DOWN_LEFT] = _animations[AN_DOWN_LEFT];
	_animations[AN_SHOOTING_LEFT] = _animations[AN_LEFT];
	_animations[AN_SHOOTING_UP_LEFT] = _animations[AN_UP_LEFT];
	_animations[AN_DEAD].Init(32 * 32, playerPos, RECT_WIDTH, RECT_HEIGHT, 1, 1);

	switch (_player) {
	case GameState::PL_WARRIOR:
		GameState::GetInstance()->SetLife(500);
		_endurance = 3;
		_strength = 4.5f;
		_speed = 10;
		break;
	case GameState::PL_VALKYRIE:
		GameState::GetInstance()->SetLife(400);
		_endurance = 3.5f;
		_strength = 4.5f;
		_speed = 10;
		break;
	case GameState::PL_WIZARD:
		GameState::GetInstance()->SetLife(650);
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 20;
		break;
	case GameState::PL_ELF:
		GameState::GetInstance()->SetLife(450);
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 20;
		break;
	default:
		break;
	}
}

void Player::Update()
{

	CheckPlayerCollisions();
	UpdatePlayerMovement();
	_animations[_currentAnimation].Update();
	UpdatePlayerBullets();
	UpdatePlayerLife();
	if (GameState::GetInstance()->GetLife() <= 0) {
		_currentState = AN_DEAD;
		_currentAnimation = AN_DEAD;
		GameState::GetInstance()->SetGameOver(true);
	}
}
void Player::UpdateInput()
{
	InputManager* inputManager = InputManager::GetInstance();

	switch (inputManager->GetDirection()) {
	case InputManager::DIR_UP:
		_currentState = AN_UP;
		break;
	case InputManager::DIR_UP_RIGHT:
		_currentState = AN_UP_RIGHT;
		break;
	case InputManager::DIR_RIGHT:
		_currentState = AN_RIGHT;
		break;
	case InputManager::DIR_DOWN_RIGHT:
		_currentState = AN_DOWN_RIGHT;
		break;
	case InputManager::DIR_DOWN:
		_currentState = AN_DOWN;
		break;
	case InputManager::DIR_DOWN_LEFT:
		_currentState = AN_DOWN_LEFT;
		break;
	case InputManager::DIR_LEFT:
		_currentState = AN_LEFT;
		break;
	case InputManager::DIR_UP_LEFT:
		_currentState = AN_UP_LEFT;
		break;
    case InputManager::DIR_SHOOTING:
		switch (_currentIdleState)
		{
			case Entity::AN_UP:
				_currentState = AN_SHOOTING_UP;
				break;
			case Entity::AN_UP_RIGHT:
				_currentState = AN_SHOOTING_UP_RIGHT;
				break;
			case Entity::AN_RIGHT:
				_currentState = AN_SHOOTING_RIGHT;
				break;
			case Entity::AN_DOWN_RIGHT:
				_currentState = AN_SHOOTING_DOWN_RIGHT;
				break;
			case Entity::AN_DOWN:
				_currentState = AN_SHOOTING_DOWN;
				break;
			case Entity::AN_DOWN_LEFT:
				_currentState = AN_SHOOTING_DOWN_LEFT;
				break;
			case Entity::AN_LEFT:
				_currentState = AN_SHOOTING_LEFT;
				break;
			case Entity::AN_UP_LEFT:
				_currentState = AN_SHOOTING_UP_LEFT;
				break;
		default:
			break;
		}
        break;
	case InputManager::DIR_SHOOTING_UP:
		_currentState = AN_SHOOTING_UP;
		break;
	case InputManager::DIR_SHOOTING_UP_RIGHT:
		_currentState = AN_SHOOTING_UP_RIGHT;
		break;
	case InputManager::DIR_SHOOTING_RIGHT:
		_currentState = AN_SHOOTING_RIGHT;
		break;
	case InputManager::DIR_SHOOTING_DOWN_RIGHT:
		_currentState = AN_SHOOTING_DOWN_RIGHT;
		break;
	case InputManager::DIR_SHOOTING_DOWN:
		_currentState = AN_SHOOTING_DOWN;
		break;
	case InputManager::DIR_SHOOTING_DOWN_LEFT:
		_currentState = AN_SHOOTING_DOWN_LEFT;
		break;
	case InputManager::DIR_SHOOTING_LEFT:
		_currentState = AN_SHOOTING_LEFT;
		break;
	case InputManager::DIR_SHOOTING_UP_LEFT:
		_currentState = AN_SHOOTING_UP_LEFT;
		break;
	case InputManager::DIR_IDLE:
		_lastNonIdleState = _currentState;
		_currentState = AN_IDLE;
		break;
	default:
		break;
	}
}

void Player::UpdateState()
{
	if (_currentAnimation != AN_DEAD) {
		switch (_currentState) {
		case Entity::AN_IDLE:
			_currentAnimation = AN_IDLE;
			CheckLastNonIdleState(_lastNonIdleState, AN_IDLE);
			CheckShootDirection();
			break;
		case Entity::AN_LEFT:
			_currentAnimation = AN_LEFT;
			_position.x -= _speed;
			break;
		case Entity::AN_RIGHT:
			_currentAnimation = AN_RIGHT;
			_position.x += _speed;
			break;
		case Entity::AN_UP:
			_currentAnimation = AN_UP;
			_position.y -= _speed;
			break;
		case Entity::AN_DOWN:
			_currentAnimation = AN_DOWN;
			_position.y += _speed;
			break;
		case Entity::AN_DEAD:
			_currentAnimation = AN_DEAD;
			break;
		case Entity::AN_UP_LEFT:
			_currentAnimation = AN_UP_LEFT;
			_position.x -= _speed;
			_position.y -= _speed;
			break;
		case Entity::AN_UP_RIGHT:
			_currentAnimation = AN_UP_RIGHT;
			_position.x += _speed;
			_position.y -= _speed;
			break;
		case Entity::AN_DOWN_LEFT:
			_currentAnimation = AN_DOWN_LEFT;
			_position.x -= _speed;
			_position.y += _speed;
			break;
		case Entity::AN_DOWN_RIGHT:
			_currentAnimation = AN_DOWN_RIGHT;
			_position.x += _speed;
			_position.y += _speed;
			break;
		default:
			CheckShootDirection();
			break;
		}
	}
}

void Player::UpdatePlayerMovement()
{
	_lastPosition = _position;
	UpdateInput();
	UpdateState();
	_collider->x = _position.x;
	_collider->y = _position.y;
}

void Player::UpdatePlayerLife()
{
	if (_lifeTimer.GetTicks() < 1000) {
		return;
	}
	_lifeTimer.StartTimer();
	GameState::GetInstance()->AddLife(-10);
}


void Player::CheckPlayerCollisions()
{
	int saveX = _position.x;
	int saveY = _position.y;
	if (_collider->collisions.size() > 0) {
		for (int i = 0; i < _collider->collisions.size(); i++) {
			if (_collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				if (_killEnemyTimer.GetTicks() < 2000) {
					continue;
				}
				_killEnemyTimer.StartTimer();
				GameState::GetInstance()->AddLife(-100);
				Enemy* enemy = (Enemy*)_collider->collisions[i].entity;
				enemy->SetEnemyState(AN_DEAD);
				
			} else 
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
			if (_collider->collisions[i].id == CollisionManager::CT_OBJECT) {
				_collider->collisions[i].entity->UseInteraction();
			}
		}
	}


}

void Player::CheckLastNonIdleState(int n, State st)
{
	switch (n) {
	case Entity::AN_UP:
		_animations[st].ChangeIdlePos(0);
		_currentIdleState = AN_UP;
		break;
	case Entity::AN_UP_RIGHT:
		_animations[st].ChangeIdlePos(32);
		_currentIdleState = AN_UP_RIGHT;
		break;
	case Entity::AN_RIGHT:
		_animations[st].ChangeIdlePos(32 * 2);
		_currentIdleState = AN_RIGHT;
		break;
	case Entity::AN_DOWN_RIGHT:
		_animations[st].ChangeIdlePos(32 * 3);
		_currentIdleState = AN_DOWN_RIGHT;
		break;
	case Entity::AN_DOWN:
		_animations[st].ChangeIdlePos(32 * 4);
		_currentIdleState = AN_DOWN;
		break;
	case Entity::AN_DOWN_LEFT:
		_animations[st].ChangeIdlePos(32 * 5);
		_currentIdleState = AN_DOWN_LEFT;
		break;
	case Entity::AN_LEFT:
		_animations[st].ChangeIdlePos(32 * 6);
		_currentIdleState = AN_LEFT;
		break;
	case Entity::AN_UP_LEFT:
		_animations[st].ChangeIdlePos(32 * 7);
		_currentIdleState = AN_UP_LEFT;
		break;
	case Entity::AN_SHOOTING_UP:
		_animations[st].ChangeIdlePos(0);
		_currentIdleState = AN_SHOOTING_UP;
		break;
	case Entity::AN_SHOOTING_UP_RIGHT:
		_animations[st].ChangeIdlePos(32);
		_currentIdleState = AN_SHOOTING_UP_RIGHT;
		break;
	case Entity::AN_SHOOTING_RIGHT:
		_animations[st].ChangeIdlePos(32 * 2);
		_currentIdleState = AN_SHOOTING_RIGHT;
		break;
	case Entity::AN_SHOOTING_DOWN_RIGHT:
		_animations[st].ChangeIdlePos(32 * 3);
		_currentIdleState = AN_SHOOTING_DOWN_RIGHT;
		break;
	case Entity::AN_SHOOTING_DOWN:
		_animations[st].ChangeIdlePos(32 * 4);
		_currentIdleState = AN_SHOOTING_DOWN;
		break;
	case Entity::AN_SHOOTING_DOWN_LEFT:
		_animations[st].ChangeIdlePos(32 * 5);
		_currentIdleState = AN_SHOOTING_DOWN_LEFT;
		break;
	case Entity::AN_SHOOTING_LEFT:
		_animations[st].ChangeIdlePos(32 * 6);
		_currentIdleState = AN_SHOOTING_LEFT;
		break;
	case Entity::AN_SHOOTING_UP_LEFT:
		_animations[st].ChangeIdlePos(32 * 7);
		_currentIdleState = AN_SHOOTING_UP_LEFT;
		break;
	default:
		break;
	}
}

void Player::UpdatePlayerBullets()
{
	size_t bulletsSize = _bullets.size();
	for (size_t i = 0; i < bulletsSize; i++)
	{
		_bullets[i]->Update();
		if (_bullets[i]->IsDeletable())
		{
			delete _bullets[i];
			_bullets.erase(_bullets.begin() + i);
			i--;
			bulletsSize--;
		}
	}
}

void Player::CheckShootDirection()
{
	switch (_currentState) {
	case Entity::AN_SHOOTING_UP:
		_currentAnimation = AN_SHOOTING_UP;
		_shootDirection.x = 0;
		_shootDirection.y = -1;
		break;
	case Entity::AN_SHOOTING_UP_RIGHT:
		_currentAnimation = AN_SHOOTING_UP_RIGHT;
		_shootDirection.x = 1;
		_shootDirection.y = -1;
		break;
	case Entity::AN_SHOOTING_RIGHT:
		_currentAnimation = AN_SHOOTING_RIGHT;
		_shootDirection.x = 1;
		_shootDirection.y = 0;
		break;
	case Entity::AN_SHOOTING_DOWN_RIGHT:
		_currentAnimation = AN_SHOOTING_DOWN_RIGHT;
		_shootDirection.x = 1;
		_shootDirection.y = 1;
		break;
	case Entity::AN_SHOOTING_DOWN:
		_currentAnimation = AN_SHOOTING_DOWN;
		_shootDirection.x = 0;
		_shootDirection.y = 1;
		break;
	case Entity::AN_SHOOTING_DOWN_LEFT:
		_currentAnimation = AN_SHOOTING_DOWN_LEFT;
		_shootDirection.x = -1;
		_shootDirection.y = 1;
		break;
	case Entity::AN_SHOOTING_LEFT:
		_currentAnimation = AN_SHOOTING_LEFT;
		_shootDirection.x = -1;
		_shootDirection.y = 0;
		break;
	case Entity::AN_SHOOTING_UP_LEFT:
		_currentAnimation = AN_SHOOTING_UP_LEFT;
		_shootDirection.x = -1;
		_shootDirection.y = -1;
		break;
	case Entity::AN_IDLE:
		switch (_currentIdleState)
		{
		case Entity::AN_SHOOTING_UP:
			_currentIdleState = AN_UP;
			break;
		case Entity::AN_SHOOTING_DOWN:
			_currentIdleState = AN_DOWN;
			break;
		case Entity::AN_SHOOTING_LEFT:
			_currentIdleState = AN_LEFT;
			break;
		case Entity::AN_SHOOTING_RIGHT:
			_currentIdleState = AN_RIGHT;
			break;
		case Entity::AN_SHOOTING_UP_LEFT:
			_currentIdleState = AN_UP_LEFT;
			break;
		case Entity::AN_SHOOTING_UP_RIGHT:
			_currentIdleState = AN_UP_RIGHT;
			break;
		case Entity::AN_SHOOTING_DOWN_LEFT:
			_currentIdleState = AN_DOWN_LEFT;
			break;
		case Entity::AN_SHOOTING_DOWN_RIGHT:
			_currentIdleState = AN_DOWN_RIGHT;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	if (_currentAnimation != 0) {
		Shoot();
	}
}

void Player::Shoot()
{
	if (_shootTimer.GetTicks() < _shootCooldown) {
		return;
	}
	_shootTimer.StartTimer();
	Bullet* bullet = new Bullet();
	bullet->SetPlayer(_player);
	bullet->Init();
	bullet->SetPosition(_position.x + _shootDirection.x * 32, _position.y + _shootDirection.y * 32, (int)_currentState - 1);
	bullet->SetDirection(_shootDirection);
	bullet->SetSpeed(20);
	_bullets.push_back(bullet);
}

void Player::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
	size_t bulletsSize = _bullets.size();

	for (size_t i = 0; i < bulletsSize; i++)
		_bullets[i]->Render();
}

