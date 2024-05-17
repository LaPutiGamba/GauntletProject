#pragma once
#include "Enemy.h"
class EnemyGhost :	public Enemy
{
	static EnemyGhost* _pInstance;

public:
	EnemyGhost();
	~EnemyGhost();

	void Init() override;
	void Update() override;
	void Render() override;
	

};

