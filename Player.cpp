#include "Player.h"
#include "ResourceManager.h"
#include "VideoManager.h"
#include "Timer.h"
#include <iostream>

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

Player* Player::_pInstance = NULL;

Player::Player()
{
	_player = GameState::PL_WARRIOR;
	_currentIdleState = AN_IDLE;
	_currentState = AN_IDLE;
	_currentAnimation = 0;
	_lastNonIdleState = AN_IDLE;
	_score = 0;
	_playerState = AN_IDLE;
	_life = 0;
	_endurance = 0;
	_strength = 0;
	_speed = 0;
	_shootCooldown = 0;
	_pShootTimer = 0;
	_position.x = 0;
	_position.y = 0;
	_sprite = 0;
	_cutRect.x = 0;
	_cutRect.y = 0;
	_drawRect.x = 0;
	_drawRect.y = 0;
	_bullets.clear();
}

void Player::Init()
{
	InputManager* inputManager = InputManager::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();

	_sprite = resourceManager->LoadAndGetGraphicID("images/entities.png");

	_cutRect.x = 0;
	_cutRect.y = 0;

	_drawRect.x = 0;
	_drawRect.y = 0;

	_position.x = 450;
	_position.y = 300;

	_currentAnimation = 0;
	_currentState = AN_IDLE;
	_life = 0;
	_endurance = 0;
	_strength = 0;
	_speed = 0;
	_shootCooldown = 0;
	_lastNonIdleState = AN_IDLE;
	_player = GameState::PL_WARRIOR;

	_collider = new CollisionManager::Collider();
	_collider->x = _position.x + (_width / 2);
	_collider->y = _position.y + (_height / 2);
	_collider->width = _width;
	_collider->height = _height;
	_collider->type = CollisionManager::CT_PLAYER;
	_collider->collisionsTag = CollisionManager::CT_ENEMY | CollisionManager::CT_WALL;

	_collisionManager->AddCollider(_collider);
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
		_life = 500;
		_endurance = 3;
		_strength = 4.5f;
		_speed = 10;
		break;
	case GameState::PL_VALKYRIE:
		_life = 400;
		_endurance = 3.5f;
		_strength = 4.5f;
		_speed = 10;
		break;
	case GameState::PL_WIZARD:
		_life = 650;
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 20;
		break;
	case GameState::PL_ELF:
		_life = 450;
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 20;
		break;
	default:
		break;
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

	_collider->x = _position.x + (_width / 2);
	_collider->y = _position.y + (_height / 2);
}

void Player::CheckPlayerCollisions()
{
	if (_collider->collisions.size() > 0) {
		for (int i = 0; i < _collider->collisions.size(); i++) {
			/*if (_collider->collisions[i].id == CollisionManager::CT_ENEMY) {
				_life -= 10;
				if (_life <= 0) {
					_currentState = AN_DEAD;
					_currentAnimation = AN_DEAD;
				}
			} else */
			if (_collider->collisions[i].id == CollisionManager::CT_WALL) {
				std::cout << "Wall collision" << std::endl;
				switch (_currentState) {
				case Entity::AN_UP:
					_position.y += _speed;
					break;
				case Entity::AN_UP_RIGHT:
					_position.x -= _speed;
					_position.y += _speed;
					break;
				case Entity::AN_RIGHT:
					_position.x -= _speed;
					break;
				case Entity::AN_DOWN_RIGHT:
					_position.x -= _speed;
					_position.y -= _speed;
					break;
				case Entity::AN_DOWN:
					_position.y -= _speed;
					break;
				case Entity::AN_DOWN_LEFT:
					_position.x += _speed;
					_position.y -= _speed;
					break;
				case Entity::AN_LEFT:
					_position.x += _speed;
					break;
				case Entity::AN_UP_LEFT:
					_position.x += _speed;
					_position.y += _speed;
					break;
				default:
					break;
				}
			}
		}
	}

	_collider->x = _position.x + (_width / 2);
	_collider->y = _position.y + (_height / 2);
}

void Player::Update()
{
	UpdateInput();
	UpdateState();
	CheckPlayerCollisions();
	_animations[_currentAnimation].Update();
	SpawnBullet();
}

void Player::CheckShootDirection()
{
	switch (_currentState) {
	case Entity::AN_SHOOTING_UP:
		_currentAnimation = AN_SHOOTING_UP;
		break;
	case Entity::AN_SHOOTING_UP_RIGHT:
		_currentAnimation = AN_SHOOTING_UP_RIGHT;
		break;
	case Entity::AN_SHOOTING_RIGHT:
		_currentAnimation = AN_SHOOTING_RIGHT;
		break;
	case Entity::AN_SHOOTING_DOWN_RIGHT:
		_currentAnimation = AN_SHOOTING_DOWN_RIGHT;
		break;
	case Entity::AN_SHOOTING_DOWN:
		_currentAnimation = AN_SHOOTING_DOWN;
		break;
	case Entity::AN_SHOOTING_DOWN_LEFT:
		_currentAnimation = AN_SHOOTING_DOWN_LEFT;
		break;
	case Entity::AN_SHOOTING_LEFT:
		_currentAnimation = AN_SHOOTING_LEFT;
		break;
	case Entity::AN_SHOOTING_UP_LEFT:
		_currentAnimation = AN_SHOOTING_UP_LEFT;
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
	Shoot();
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

void Player::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
}

void Player::Shoot()
{
	//currentTime
	//if (currentTime - _shootTimer > _shootCooldown)
 	_bullets.push_back(new Bullet{_position.x, _position.y, 1});
}

void Player::SpawnBullet()
{
	std::vector<Bullet*>::iterator it = _bullets.begin();
	while (it != _bullets.end()) {
		Bullet* bullet = *it;
		bullet->pos.x += bullet->dir.x * bullet->speed;
		bullet->pos.y += bullet->dir.y * bullet->speed;

		RenderBullets(*bullet);
		if (bullet->pos.x < 0 || bullet->pos.x > 640 || bullet->pos.y < 0 || bullet->pos.y > 480) {
			delete bullet;
			it = _bullets.erase(it);
		}
		else
			++it;
	}

}

void Player::RenderBullets(const Bullet& bullet)
{
	VideoManager* videoManager = VideoManager::GetInstance();
}
