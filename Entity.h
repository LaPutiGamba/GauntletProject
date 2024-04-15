#pragma once
#include "Animation.h"
#include "SDL.h"
#include "CollisionManager.h"

class Entity
{
public:
	struct Position
	{
		int x;
		int y;
	};

	enum State
	{
		AN_IDLE,
		AN_LEFT,
		AN_RIGHT,
		AN_UP,
		AN_DOWN,
		AN_SHOOTING,
		AN_DEAD,
		AN_UP_LEFT,
		AN_UP_RIGHT,
		AN_DOWN_LEFT,
		AN_DOWN_RIGHT,
		AN_SHOOTING_UP,
		AN_SHOOTING_DOWN,
		AN_SHOOTING_LEFT,
		AN_SHOOTING_RIGHT,
		AN_SHOOTING_UP_LEFT,
		AN_SHOOTING_UP_RIGHT,
		AN_SHOOTING_DOWN_LEFT,
		AN_SHOOTING_DOWN_RIGHT,
		AN_SIZE
	};

protected:
	Position _position; /// Position of the entity divided into x and y
	int _width, _height; /// The width and height of the entity
	int _sprite; /// The sprite of the entity
	Position _cutRect; /// The rectangle that will be cut from the sprite
	Position _drawRect; /// The rectangle that will be drawn to the screen
	Animation _animations[AN_SIZE];	/// The animations of the entity
	int _currentAnimation; /// The current animation of the entity
	State _currentState; /// The current state of the entity
	CollisionManager* _collisionManager; ///< The collision manager of the entity
	CollisionManager::Collider* _collider; ///< The collider of the entity
	
public:
	Entity();
	~Entity();
	
	/// \brief Set the x position of the entity
	/// \param x The x position
	void SetX(int x);

	/// \brief Get the x position of the entity
	/// \return The x position
	int GetX() { return _position.x; }

	/// \brief Set the y position of the entity
	/// \param y The y position
	void SetY(int y);

	/// \brief Get the y position of the entity
	/// \return The y position
	int GetY() { return _position.y; }

	/// \brief Set the position of the entity
	/// \param x The x position
	/// \param y The y position
	void SetPosition(int x, int y);

	/// \brief Set the position of the entity
	/// \return The position
	Position GetPosition() { return _position; }
};

