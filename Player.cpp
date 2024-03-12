#include "Player.h"
#include "ResourceManager.h"
#include "VideoManager.h"

#define RECT_WIDTH 32
#define RECT_HEIGHT 32

Player* Player::_pInstance = nullptr;

void Player::Init()
{

	InputManager* inputManager = InputManager::GetInstance();
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	TimerManager* timerManager = TimerManager::GetInstance();

	_sprite = resourceManager->LoadAndGetGraphicID("images/entities.png");

	_cutRect.x = 0;
	_cutRect.y = 0;

	_drawRect.x = 0;
	_drawRect.y = 0;

	_position.x = 0;
	_position.y = 0;

	State _currentState = AN_IDLE;
	_player = PL_WARRIOR;
	int playerPos = _player  * 32;
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
	_animations[AN_DEAD].Init(32 * 32, playerPos, RECT_WIDTH, RECT_HEIGHT, 1, 1);

	_currentAnimation = 0;
	_currentState = AN_IDLE;
	_life = 0;
	_endurance = 0;
	_strength = 0;
	_speed = 0;
	_shootCooldown = 0;
	_player = 0;
	_lastNonIdleState = AN_IDLE;
	_timerManager->Init();
}

void Player::LoadCharacter()
{
	switch (_player) {
	case PL_WARRIOR:
		_life = 500;
		_endurance = 3;
		_strength = 4.5f;
		_speed = 0.75f;
		break;
	case PL_VALKYRIE:
		_life = 400;
		_endurance = 3.5f;
		_strength = 4.5f;
		_speed = 1.0f;
		break;
	case PL_WIZARD:
		_life = 650;
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 1.75f;
		break;
	case PL_ELF:
		_life = 450;
		_endurance = 2.5f;
		_strength = 3.25f;
		_speed = 1.75f;
		break;
	default:
		break;
	}
}

void Player::Update()
{
	InputManager* inputManager = InputManager::GetInstance();
	State newState = _currentState;

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
				_currentState = AN_SHOOTING;
				break;
			case InputManager::DIR_IDLE:
				_lastNonIdleState = _currentState;
				_currentState = AN_IDLE;
				break;
			default:
			break;
		}


		

		switch (_currentState) {
		case Entity::AN_IDLE:
		_currentAnimation = AN_IDLE;
			switch (_lastNonIdleState) {
				case Entity::AN_UP:
					_animations[AN_IDLE].changeIdlePos(0);
					break;
				case Entity::AN_UP_RIGHT:
					_animations[AN_IDLE].changeIdlePos(32);
					break;
				case Entity::AN_RIGHT:
					_animations[AN_IDLE].changeIdlePos(32 * 2);
					break;
				case Entity::AN_DOWN_RIGHT:
					_animations[AN_IDLE].changeIdlePos(32 * 3);
					break;
				case Entity::AN_DOWN:
					_animations[AN_IDLE].changeIdlePos(32 * 4);
					break;
				case Entity::AN_DOWN_LEFT:
					_animations[AN_IDLE].changeIdlePos(32 * 5);
					break;
				case Entity::AN_LEFT:
					_animations[AN_IDLE].changeIdlePos(32 * 6);
					break;
				case Entity::AN_UP_LEFT:
					_animations[AN_IDLE].changeIdlePos(32 * 7);
					break;
				default:
					break;
			}
			break;

		case Entity::AN_LEFT:
			_currentAnimation = AN_LEFT;
			_position.x--;
			break;
		case Entity::AN_RIGHT:
			_currentAnimation = AN_RIGHT;
			_position.x++;
			break;
		case Entity::AN_UP:
			_currentAnimation = AN_UP;
			_position.y--;
			break;
		case Entity::AN_DOWN:
			_currentAnimation = AN_DOWN;
			_position.y++;
			break;
		case Entity::AN_SHOOTING:
			_currentAnimation = AN_SHOOTING;
			Shoot();
			break;
		case Entity::AN_DEAD:
			_currentAnimation = AN_DEAD;
			break;
		case Entity::AN_UP_LEFT:
			_currentAnimation = AN_UP_LEFT;
			_position.x--;
			_position.y--;
			break;
		case Entity::AN_UP_RIGHT:
			_currentAnimation = AN_UP_RIGHT;
			_position.x++;
			_position.y--;
			break;
		case Entity::AN_DOWN_LEFT:
			_currentAnimation = AN_DOWN_LEFT;
			_position.x--;
			_position.y++;
			break;
		case Entity::AN_DOWN_RIGHT:
			_currentAnimation = AN_DOWN_RIGHT;
			_position.x++;
			_position.y++;
			break;
		default:
			break;
		}



		_animations[_currentAnimation].Update();
}

void Player::Render()
{
	Animation::ImageCut frame = _animations[_currentAnimation].GetFrame();
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->RenderGraphic(_sprite, _position.x, _position.y, RECT_WIDTH, RECT_HEIGHT, frame.x, frame.y);
}

void Player::SetState(State state)
{
}

void Player::Shoot()
{

}
