#include "InputManager.h"

InputManager::InputManager()
{
	_direction = DIR_IDLE;
	_bPause = NULL;
}

InputManager::~InputManager()
{
}

void InputManager::Update()
{
	SDL_Event event;
	SDL_Scancode tecla;
	bool quit = false;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			tecla = event.key.keysym.scancode;
			switch (tecla) {
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
			tecla = event.key.keysym.scancode;
			switch (tecla) {
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
