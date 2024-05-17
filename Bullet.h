#pragma once
#include "Entity.h"
class Bullet :	public Entity
{
private:
	//Bullet properties
	int _speed; ///< Speed of the bullet
	Position _direction; ///< Direction of the bullet
	int _damage; ///< Damage of the bullet
	int _player; ///< Player number of the bullet
	bool _bIsMoving; ///< If the bullet is moving
public:
	Bullet();
	~Bullet();

	/// \brief Init the bullet
	void Init() override;

	/// \brief Update the bullet
	void Update() override;

	/// \brief Render the bullet
	void Render() override;

	/// \brief Check if the bullet is colliding with something
	void CheckCollision();

	/// \brief Set the direction of the bullet
	/// \param dir The direction of the bullet
	void SetDirection(Position dir) { _direction = dir; }

	/// \brief Set the speed of the bullet
	/// \param speed The speed of the bullet
	void SetSpeed(int speed) { _speed = speed; }

	/// \brief Set the damage of the bullet
	/// \param damage The damage of the bullet
	void SetDamage(int damage) { _damage = damage; }

	/// \brief Set the position of the bullet
	/// \param pos The position of the bullet
	void SetPosition(Position pos) { _position = pos; }

	/// \brief Set the position of the bullet
	/// \param x The x position of the bullet
	/// \param y The y position of the bullet
	/// \param state The state of the bullet
	void SetPosition(int x, int y, int state);

	/// \brief Set the player number of the bullet
	/// \param player The player number of the bullet
	void SetPlayer(int player) { _player = player; }

	void SetBulletColliderTags(int tag) { _collider->collisionsTag = tag; }


};

