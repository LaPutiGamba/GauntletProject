#pragma once
#include "Entity.h"
#include "Player.h"

class Enemy : public Entity
{
protected:
	int _life; ///< Life of the enemy
	int _speed; ///< Speed of the enemy
	int _damage; ///< Damage that the enemy does
	State _state; ///< State of the enemy
	Player* _player; ///< Player
	Position _playerPosition; ///< Player position
	Position _lastPosition; ///< Last position of the enemy

	bool _bIsAlive; ///< If the enemy is alive

public:
	Enemy();
	~Enemy();

	void Init() override;
    void Update() override;

    void UseInteraction() override;

	void SetPlayer(Player* player) { _player = player; }

	/// \brief Set the state of the enemy
	/// \param state The state of the enemy
	void SetEnemyState(State state);

	/// \brief Go to the player position
	void GoToPlayer();

	/// \brief Check if the enemy is colliding with the player or walls
	void CheckEnemyCollision();
};

