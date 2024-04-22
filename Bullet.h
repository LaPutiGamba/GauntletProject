#pragma once
#include "Entity.h"
class Bullet :	public Entity
{
private:
	//Bullet properties
	int _speed; ///Speed of the bullet
	Position _direction; ///Direction of the bullet
	int _damage; ///Damage of the bullet
	int _player; ///Player number of the bullet
	bool _bDeletable; ///If the bullet is deletable
	bool _bIsMoving; ///If the bullet is moving
public:
	Bullet();
	~Bullet();

	void Init() override;
	void Update() override;
	void Render() override;

	void CheckCollision();

	void SetDirection(Position dir) { _direction = dir; }
	void SetSpeed(int speed) { _speed = speed; }
	void SetDamage(int damage) { _damage = damage; }
	void SetPosition(Position pos) { _position = pos; }
	void SetPosition(int x, int y) { _position.x = x; _position.y = y; }
	void SetPlayer(int player) { _player = player; }
	bool IsDeletable() { return _bDeletable; }
};

