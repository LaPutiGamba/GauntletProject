#pragma once
#include "Scene.h"
#include "Player.h"
#include "EnemyGhost.h"
#include "EnemyDoggy.h"
#include "Camera.h"
#include "GameState.h"
#include <vector>

class SceneGame : public Scene
{
private:
	int _actualMapID; ///< The actual map ID
	Player* _player; ///< The player
	Camera _camera; ///< The camera
	std::vector<Enemy*> _enemyList; ///< The enemy
	std::vector<Enemy*> _enemyList2; ///< The enemy

	void InitEnemies();
	void UpdateEnemies();
	void RenderEnemies();
	void PrintInfo();
	std::vector<class Enemy> _enemies; ///< The enemies array
	std::vector<class Object*> _objects; ///< The objects array

protected:
	GameState::PlayerSelected _playerSelected; ///< The selected player

public:
	SceneGame();
	~SceneGame();

	void Init() override;
	void ReInit() override;
	void Update() override;
	void Render() override;

	Camera* GetCamera() { return &_camera; }

	int ReadLevelInfo(const char* filename);
};