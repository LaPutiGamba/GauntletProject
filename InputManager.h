#pragma once
#include <SDL.h>

class InputManager
{
private:
	//All the possible key events
	enum Direction {
		DIR_IDLE,
		DIR_UP,
		DIR_DOWN,
		DIR_LEFT,
		DIR_RIGHT,
		DIR_UP_LEFT,
		DIR_UP_RIGHT,
		DIR_DOWN_LEFT,
		DIR_DOWN_RIGHT,
		DIR_SHOOTING
	};

	static InputManager* _pInstance;
	InputManager();

public:
	int _direction;
	bool _bPause;

	~InputManager();

	void Update();
	int getDirection() { return _direction; }
	bool getPause() { return _bPause; }
	static InputManager* getInstance() {
		if (_pInstance == NULL) {
			_pInstance = new InputManager;
		}
	}
};

