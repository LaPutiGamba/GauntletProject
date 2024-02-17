#pragma once
#include <SDL.h>

class InputManager
{
private:
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
	int GetDirection() { return _direction; }
	bool GetPause() { return _bPause; }
	static InputManager* GetInstance() {
		if (_pInstance == NULL) {
			_pInstance = new InputManager;
		}

		return _pInstance;
	}
};

