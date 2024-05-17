#pragma once
#include "Enemy.h"
#include "VideoManager.h"
#include "Bullet.h"
#include "Timer.h"
#include <vector>

class EnemyDoggy : public Enemy
{
private:
	static EnemyDoggy* _pInstance;	
	int _shootCooldown; ///Player's shoot cooldown
	std::vector<Bullet*> _bullets; ///Player's bullets
	Position _shootDirection; ///Player's shoot direction
	Timer _shootTimer; ///Player's shoot timer

public:
	EnemyDoggy();
	~EnemyDoggy();

	void Init() override;
	void Update() override;
	void Render() override;

	void UpdateDoggyBullets();
	void CheckShootDirection();
	void Shoot();
};

