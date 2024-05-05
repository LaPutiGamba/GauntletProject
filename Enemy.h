#pragma once
#include "Entity.h"

class Enemy :	public Entity
{

protected:
	int _life;
	int _speed;
	int _damage;
	Position _playerPosition;

	bool _bIsAlive;

public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void GoToPlayer();
};

