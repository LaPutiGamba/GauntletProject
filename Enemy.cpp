#include "Enemy.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "MapManager.h"
#include "GameState.h"
#include "SoundManager.h"
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

	_player = GameState::GetInstance()->GetPlayer();
	
	_sprite = ResourceManager::GetInstance()->LoadAndGetGraphicID("images/entities.png");
	
	_bIsAlive = true;

	_collider->x = _position.x;
	_collider->y = _position.y;
	_collider->type = CollisionManager::CT_ENEMY;
	_collider->collisionsTag = CollisionManager::CT_BULLET | CollisionManager::CT_PLAYER | CollisionManager::CT_WALL;

	_collisionManager->AddCollider(_collider);

	_animations[AN_DEAD].Init(14 * 32, 9 * 32, 32, 32, 5, 1);
}

void Enemy::UseInteraction()
{
    Entity::UseInteraction();

	GameState::GetInstance()->AddLife(-20);
	SetEnemyState(AN_DEAD);
}

void Enemy::Update()
{
	_playerPosition = _player->GetPosition();
	GoToPlayer();

    _animations[_currentAnimation].Update();
	if (_currentAnimation == AN_DEAD && _animations[_currentAnimation].IsFinished())
		_bDeletable = true;
    
	_lastPosition = _position;
	_collider->x = _position.x;
	_collider->y = _position.y;
	//cout position
	std::cout << "Enemy position: " << _position.x << " " << _position.y << std::endl;
}

void Enemy::GoToPlayer()
{
	if (_currentAnimation == AN_DEAD)
		return;
	
	if (_playerPosition.x < _position.x) {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP_LEFT;
			_currentState = AN_UP_LEFT;
		} else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN_LEFT;
			_currentState = AN_DOWN_LEFT;
		} else {
			_currentAnimation = AN_LEFT;
			_currentState = AN_LEFT;
		}
	} else if (_playerPosition.x > _position.x) {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP_RIGHT;
			_currentState = AN_UP_RIGHT;
		} else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN_RIGHT;
			_currentState = AN_DOWN_RIGHT;
		} else {
			_currentAnimation = AN_RIGHT;
			_currentState = AN_RIGHT;
		}
	} else {
		if (_playerPosition.y < _position.y) {
			_currentAnimation = AN_UP;
			_currentState = AN_UP;
		} else if (_playerPosition.y > _position.y) {
			_currentAnimation = AN_DOWN;
			_currentState = AN_DOWN;
		}
	}

	int layer;
	switch (_currentAnimation) {
	case AN_UP:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x, _position.y - 1);
	    if (layer != 0)
		    _position.y -= 1;
		break;
	case AN_UP_RIGHT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x + 1, _position.y - 1);
	    if (layer != 0) {
		    _position.x += 1;
		    _position.y -= 1;
		}
		break;
	case AN_RIGHT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x + 1, _position.y);
	    if (layer != 0)
		    _position.x += 1;
	    break;
	case AN_DOWN_RIGHT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x + 1, _position.y + 1);
	    if (layer != 0) {
		    _position.x += 1;
		    _position.y += 1;
		}
	    break;
	case AN_DOWN:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x, _position.y + 1);
	    if (layer != 0)
		    _position.y += 1;
	    break;
	case AN_DOWN_LEFT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x - 1, _position.y + 1);
	    if (layer != 0) {
		    _position.x -= 1;
		    _position.y += 1;
	    }
	    break;
	case AN_LEFT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x - 1, _position.y);
	    if (layer != 0)
		    _position.x -= 1;
	    break;
	case AN_UP_LEFT:
		layer = MapManager::GetInstance()->GetIDFromLayer(_mapID, 0, _position.x - 1, _position.y - 1);
	    if (layer != 0) {
		    _position.x -= 1;
		    _position.y -= 1;
	    }
	    break;
	default:
	    break;
	}
	std::cout << "Layer: " << layer << std::endl;
}

void Enemy::SetEnemyState(const State state)
{
	SoundManager* soundManager = SoundManager::GetInstance();
	if (_currentAnimation == AN_DEAD) 
		return;
	
	_currentAnimation = state;
	if (state == AN_DEAD) {
		int channel = soundManager->PlayFromStart(soundManager->LoadAndGetSoundID("sounds/monsterDeath.ogg"), 0);
        soundManager->SetVolume(channel, 5);
		GameState::GetInstance()->AddScore(200);
		GameState::GetInstance()->AddKills();
		_collisionManager->RemoveCollider(_collider);
		delete _collider;
	}
}