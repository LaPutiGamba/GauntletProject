#pragma once
#include "Enemy.h"
class EnemyGhost :	public Enemy
{
	static EnemyGhost* _pInstance;

public:
	EnemyGhost();
	~EnemyGhost();

	void Init();
	void Update();
	void Render();


};

