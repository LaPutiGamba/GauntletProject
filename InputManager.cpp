#include "InputManager.h"
#include <iostream>

InputManager* InputManager::_pInstance = NULL;


InputManager::InputManager()
{
	_direction = DIR_IDLE;
	_playerActions = WAITING_SELECTION;
	_bPause = false;
	_key1 = DIR_IDLE;
	_key2 = DIR_IDLE;
	_specialKey = DIR_IDLE;
}

InputManager::~InputManager()
{
}

void InputManager::CheckFreeKeys(Direction dir)
{
	
		if (_key1 == DIR_IDLE && _key1 != dir && _key2 != dir) {
			_key1 = dir;
		} else if (_key2 == DIR_IDLE && _key1 != DIR_IDLE && _key1 != dir && _key2 != dir) {
			_key2 = dir;
		}

		int result = _key1 + _key2;
		if (result == 3 || result == 24)
			_key2 = DIR_IDLE;
}

void InputManager::FreeKeys(Direction dir)
{
	if (dir == DIR_SHOOTING) {
		_key1 = DIR_IDLE;
		_key2 = DIR_IDLE;
		_direction = DIR_IDLE;
	} else {
		if (_key1 == dir) {
			_key1 = DIR_IDLE;
		}
		else if (_key2 == dir) {
			_key2 = DIR_IDLE;
		}
		else if (_key1 == _key2) {
			_key2 = DIR_IDLE;
		}
		else {
			_key1 = DIR_IDLE;
			_key2 = DIR_IDLE;
		}
	}
}

void InputManager::Update()
{
	SDL_Event event;
	SDL_Scancode key;
	bool quit = false;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			key = event.key.keysym.scancode;
			switch (key) {
			case SDL_SCANCODE_1:
				_playerActions = SELECT_VALKYRIE;
				break;
			case SDL_SCANCODE_2:
				_playerActions = SELECT_ELF;
				break;
			case SDL_SCANCODE_3:
				_playerActions = SELECT_WIZARD;
				break;
			case SDL_SCANCODE_4:
				_playerActions = SELECT_WARRIOR;
				break;
			case SDL_SCANCODE_ESCAPE:
				_playerActions = KEY_ESC;
				break;

			case SDL_SCANCODE_W:
				if (_key1 != DIR_UP && _key2 != DIR_UP)
				InputManager::CheckFreeKeys(DIR_UP);
				break;
			case SDL_SCANCODE_S:
				if (_key1 != DIR_DOWN && _key2 != DIR_DOWN)
				InputManager::CheckFreeKeys(DIR_DOWN);
				break;
			case SDL_SCANCODE_A:
				if (_key1 != DIR_LEFT && _key2 != DIR_LEFT)
				InputManager::CheckFreeKeys(DIR_LEFT);
				break;
			case SDL_SCANCODE_D:
				if (_key1 != DIR_RIGHT && _key2 != DIR_RIGHT)
				InputManager::CheckFreeKeys(DIR_RIGHT);
				break;
			case SDL_SCANCODE_SPACE:
				_specialKey = DIR_SHOOTING;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			key = event.key.keysym.scancode;
			switch (key) {
			case SDL_SCANCODE_W:
				if (_key1 == DIR_UP || _key2 == DIR_UP)
				InputManager::FreeKeys(DIR_UP);
				break;
			case SDL_SCANCODE_S:
				if (_key1 == DIR_DOWN || _key2 == DIR_DOWN)
				InputManager::FreeKeys(DIR_DOWN);
				break;
			case SDL_SCANCODE_A:
				if (_key1 == DIR_LEFT || _key2 == DIR_LEFT)
				InputManager::FreeKeys(DIR_LEFT);
				break;
			case SDL_SCANCODE_D:
				if (_key1 == DIR_RIGHT || _key2 == DIR_RIGHT)
				InputManager::FreeKeys(DIR_RIGHT);
				break;
			case SDL_SCANCODE_SPACE:
				_specialKey = DIR_IDLE;
				InputManager::FreeKeys(DIR_SHOOTING);
				break;
			default:
				break;
			}
			break;
		}
	}

	int result = _key1 + _key2 + _specialKey;

	if (_direction != DIR_SHOOTING)
	_direction = static_cast<Direction>(result);

	//std::cout << "Direction: " << _direction << std::endl;
}
