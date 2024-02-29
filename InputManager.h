#pragma once
#include <SDL.h>

/// \class InputManager
/// \brief Handles the input from the player
class InputManager
{
private:
	int _direction; ///< Direction that the player is heading to
	bool _bPause; ///< Pause state
	static InputManager* _pInstance; ///< Singleton instance

public:
	~InputManager();

	/// \brief Updates the input manager. It must be called once per frame
	void Update();

	///	\brief Returns the direction that the player is heading to
	///	\return Direction
	int GetDirection() { return _direction; }
	
	///	\brief Returns the pause state
	///	\return Pause state
	bool GetPause() { return _bPause; }

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static InputManager* GetInstance() {
		if (_pInstance == NULL) {
			_pInstance = new InputManager;
		}

		return _pInstance;
	}

protected:
	InputManager();

private:
	///	\enum Direction
	///	\brief Enumerated type for the direction that the player is heading to
	/// \note DIR_IDLE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_UP_LEFT, DIR_UP_RIGHT, DIR_DOWN_LEFT, DIR_DOWN_RIGHT, DIR_SHOOTING
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

