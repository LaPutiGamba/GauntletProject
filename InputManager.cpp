#include "InputManager.h"

InputManager* InputManager::_pInstance = NULL;

InputManager::InputManager()
{
	_direction = DIR_IDLE;
	_playerActions = WAITING_SELECTION;
	_bPause = false;
}

InputManager::~InputManager()
{
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
				_playerActions = SELECT_WARRIOR;
				break;
			case SDL_SCANCODE_2:
				_playerActions = SELECT_VALKYRIE;
				break;
			case SDL_SCANCODE_3:
				_playerActions = SELECT_WIZARD;
				break;
			case SDL_SCANCODE_4:
				_playerActions = SELECT_ELF;
				break;


			case SDL_SCANCODE_W:
				switch (_direction) {
				case DIR_LEFT:
					_direction = DIR_UP_LEFT;
					break;
				case DIR_RIGHT:
					_direction = DIR_UP_RIGHT;
					break;
				default:
					_direction = DIR_UP;
					break;
				}
				break;
			case SDL_SCANCODE_S:
				switch (_direction) {
				case DIR_LEFT:
					_direction = DIR_DOWN_LEFT;
					break;
				case DIR_RIGHT:
					_direction = DIR_DOWN_RIGHT;
					break;
				default:
					_direction = DIR_DOWN;
					break;
				}
				break;
			case SDL_SCANCODE_A:
				switch (_direction) {
				case DIR_UP:
					_direction = DIR_UP_LEFT;
					break;
				case DIR_DOWN:
					_direction = DIR_DOWN_LEFT;
					break;
				default:
					_direction = DIR_LEFT;
					break;
				}
				break;
			case SDL_SCANCODE_D:
				switch (_direction) {
				case DIR_UP:
					_direction = DIR_UP_RIGHT;
					break;
				case DIR_DOWN:
					_direction = DIR_DOWN_RIGHT;
					break;
				default:
					_direction = DIR_RIGHT;
					break;
				}
				break;
			case SDL_SCANCODE_SPACE:
				_direction = DIR_SHOOTING;
				break;
			case SDL_SCANCODE_ESCAPE:
				_bPause = true;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			key = event.key.keysym.scancode;
			switch (key) {
			case SDL_SCANCODE_W:
				switch (_direction) {
				case DIR_UP_LEFT:
					_direction = DIR_LEFT;
					break;
				case DIR_UP_RIGHT:
					_direction = DIR_RIGHT;
					break;
				default:
					_direction = DIR_IDLE;
					break;
				}
				break;
			case SDL_SCANCODE_S:
				switch (_direction) {
				case DIR_DOWN_LEFT:
					_direction = DIR_LEFT;
					break;
				case DIR_DOWN_RIGHT:
					_direction = DIR_RIGHT;
					break;
				default:
					_direction = DIR_IDLE;
					break;
				}
				break;
			case SDL_SCANCODE_A:
				switch (_direction) {
				case DIR_UP_LEFT:
					_direction = DIR_UP;
					break;
				case DIR_DOWN_LEFT:
					_direction = DIR_DOWN;
					break;
				default:
					_direction = DIR_IDLE;
					break;
				}
				break;
			case SDL_SCANCODE_D:
				switch (_direction) {
				case DIR_UP_RIGHT:
					_direction = DIR_UP;
					break;
				case DIR_DOWN_RIGHT:
					_direction = DIR_DOWN;
					break;
				default:
					_direction = DIR_IDLE;
					break;
				}
				break;
			case SDL_SCANCODE_SPACE:
				_direction = DIR_IDLE;
				break;
			default:
				break;
			}
			break;
		}
	}
}
