#pragma once
#include "Enemy.h"

class EnemyGhost :	public Enemy
{
public:
	EnemyGhost();
	~EnemyGhost();

	void Init() override;
	void Update() override;
	void Render() override;
};