#pragma once
#include "Entity.h"
class Enemy :	public Entity
{

protected:
	int _life;
	int _speed;
	int _damage;
	State _state;
	Position _playerPosition;

	bool _bIsAlive;

public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	Position GetPosition() { return _position; }
	void SetPosition(Position position) { _position = position; }
	void SetEnemyState(State state) { _currentAnimation = state; }
	void GoToPlayer();


};

