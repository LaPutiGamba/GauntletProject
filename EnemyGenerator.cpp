#include "EnemyGenerator.h"
#include "Enemy.h"
#include "GameState.h"

EnemyGenerator::EnemyGenerator()
{
	_typeOfEnemy = 0;
	_spawnTime = 0.0f;
}

void EnemyGenerator::Init()
{
	Object::Init();

	_collider->x = _position.x;
	_collider->y = _position.y;

	_spawnTime = 3.0f;
}

void EnemyGenerator::SelectGenerator(const char* typeOfEnemy, int level)
{
	if (typeOfEnemy == "EnemyGhostGenerator") {
		_typeOfEnemy = 1;

		switch (level) {
		case 1:
			_animations[AN_IDLE].Init(34 * RECT_WIDTH, 4 * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, 1, 0);
			break;
		case 2:
			_animations[AN_IDLE].Init(33 * RECT_WIDTH, 4 * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, 1, 0);
			break;
		case 3:
			_animations[AN_IDLE].Init(32 * RECT_WIDTH, 4 * RECT_HEIGHT, RECT_WIDTH, RECT_HEIGHT, 1, 0);
			break;
		}
	}
}

void EnemyGenerator::UseInteraction()
{
	GameState::GetInstance()->AddScore(-100);
}
