#pragma once
#include "Object.h"

/// \class EnemyGenerator
/// \brief The enemy generator class
class EnemyGenerator : public Object
{
private:
	int _typeOfEnemy; ///< The type of enemy
	float _spawnTime; ///< The time between spawns

public:
	EnemyGenerator();
	~EnemyGenerator() {}

	void Init() override;
	void SelectGenerator(const char* typeOfEnemy, int level);
	void UseInteraction() override;
};