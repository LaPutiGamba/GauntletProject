#pragma once
//Child class of Entity
#include "Entity.h"
#include "InputManager.h"
#include "Timer.h"
#include <Vector>
#include "CollisionManager.h"
#include "GameState.h"
#include "Bullet.h"

class Player : public Entity
{
private:
	//Player Stats
	GameState::PlayerSelected _player; ///Player's type
	int _life; ///Player's life
	int _score; ///Player's score
	int _endurance; ///Player's endurance
	int _strength; ///Player's strength
	int _speed; ///Player's speed
	//Bullet variables
	int _shootCooldown; ///Player's shoot cooldown
	std::vector<Bullet*> _bullets; ///Player's bullets
	Position _shootDirection; ///Player's shoot direction
	Timer _shootTimer; ///Player's shoot timer
	//Player's states
	State _playerState; ///Player's state
	State _currentIdleState; ///Player's current idle state
	State _lastNonIdleState; ///Player's last non idle state
	Position _lastPosition; ///Player's last position
	//Singleton
	static Player* _pInstance; ///< Singleton instance

protected:
	Player();

public:
	~Player() {}

	/// \brief Initializes the player
	void Init() override;

	/// \brief Loads the player with the stats of the selected character
	void LoadCharacter();

private:
	/// \brief Updates the player's input
	void UpdateInput();

	/// \brief Updates the player's position
	void UpdateState();

	void UpdatePlayerMovement();

public:
	/// \brief Check the player collisions
	void CheckPlayerCollisions();

	/// \brief Calls the player's update functions
	void Update() override;

	/// \brief Gets the player's speed
	int GetSpeed() { return _speed; }

	/// \brief If the player stop movement, check the last non idle state
	/// \param n The last non idle state
	/// \param st The current state
	void CheckLastNonIdleState(int n, State st);

	/// \brief Check the player's position to shoot
	void CheckShootDirection();

	/// \brief Shoots a bullet and sets the shoot cooldown
	void Shoot();

	/// \brief Renders the player
	void Render() override;

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static Player* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new Player();
		return _pInstance;
	}
};
