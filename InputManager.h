#pragma once
#include <SDL.h>

/// \class InputManager
/// \brief Handles the input from the player
class InputManager
{
public:
	///	\enum Direction
	///	\brief Enumerated type for the direction that the player is heading to
	/// \note DIR_IDLE, DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_UP_LEFT, DIR_UP_RIGHT, DIR_DOWN_LEFT, DIR_DOWN_RIGHT, DIR_SHOOTING
	enum Direction {
		DIR_IDLE,
		DIR_UP = 1,
		DIR_DOWN = 2,
		DIR_LEFT = 8,
		DIR_RIGHT = 16,
		DIR_UP_LEFT = 9,
		DIR_UP_RIGHT = 17,
		DIR_DOWN_LEFT = 10,
		DIR_DOWN_RIGHT = 18,
		DIR_SHOOTING = 32,
		DIR_SHOOTING_UP = 32+DIR_UP,
		DIR_SHOOTING_DOWN = 32+DIR_DOWN,
		DIR_SHOOTING_LEFT = 32+DIR_LEFT,
		DIR_SHOOTING_RIGHT = 32+DIR_RIGHT,
		DIR_SHOOTING_UP_LEFT = 32+DIR_UP_LEFT,
		DIR_SHOOTING_UP_RIGHT = 32+DIR_UP_RIGHT,
		DIR_SHOOTING_DOWN_LEFT = 32+DIR_DOWN_LEFT,
		DIR_SHOOTING_DOWN_RIGHT = 32+DIR_DOWN_RIGHT
	};

	

	enum PlayerActions {
		WAITING_SELECTION,
		SELECT_VALKYRIE,
		SELECT_ELF,
		SELECT_WIZARD,
		SELECT_WARRIOR,
		SELECT_HIGHSCORE,
		SELECT_BACK,
		SELECT_EXIT
	};

private:
	Direction _direction; ///< Direction that the player is heading to
	Direction _key1; ///< Key 1
	Direction _key2; ///< Key 2
	Direction _specialKey; ///< Special key
	PlayerActions _playerActions; ///< Player actions that triggers with inputs
	bool _bPause; ///< Pause state
	static InputManager* _pInstance; ///< Singleton instance

public:
	~InputManager();

	/// \brief Updates the input manager. It must be called once per frame
	void Update();

	///	\brief Returns the direction that the player is heading to
	///	\return Direction
	Direction GetDirection() { return _direction; }

	/// \brief Returns the special key
	/// \return Special key
	Direction GetSpecialKey() { return _specialKey; }

	///	\brief Returns the player actions
	///	\return Player actions
	PlayerActions GetPlayerActions() { return _playerActions; }
	
	///	\brief Sets the pause state
	///	\param pause Pause state
	void SetPause(bool pause) { _bPause = pause; }

	///	\brief Returns the pause state
	///	\return Pause state
	bool GetPause() { return _bPause; }

	///	\brief Checks the free keys
	///	\param dir Direction
	void CheckFreeKeys(Direction dir);

	///	\brief Frees the keys
	///	\param dir Direction
	void FreeKeys(Direction dir);

	///	\brief Sets the player actions
	///	\param playerActions Player actions
	void SetPlayerActions(PlayerActions playerActions) { _playerActions = playerActions; }

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
};

