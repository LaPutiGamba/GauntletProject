#pragma once
#include "Entity.h"
#include "Player.h"

/// \class Enemy
///	\brief Class for the enemies
class Enemy : public Entity
{
protected:
	int _life; ///< Life of the enemy
	int _speed; ///< Speed of the enemy
	int _damage; ///< Damage that the enemy does
    int _mapID; ///< Map ID of the enemy
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

    /// \brief Set the id of the current map
    ///	\param mapID The id of the current map
    void SetMapID(int mapID) { _mapID = mapID; }

    /// \brief Set the player to follow
    ///	\param player The player to follow
	void SetPlayer(Player* player) { _player = player; }

	/// \brief Set the state of the enemy
	/// \param state The state of the enemy
	void SetEnemyState(State state);

	/// \brief Go to the player position
	void GoToPlayer();
};

