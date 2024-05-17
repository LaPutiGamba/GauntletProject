#include "SceneGame.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "MapManager.h"
#include "SceneDirector.h"
#include <iostream>
#include "GameState.h"
using namespace std;


SceneGame::SceneGame()
{
	_actualMapID = -1;
	_player = nullptr;
	_playerSelected = GameState::PL_WARRIOR;
}

SceneGame::~SceneGame()
{

}

void SceneGame::InitEnemies()
{
	for (size_t i = 0; i < 20; i++)
	{
		EnemyGhost* ghost = new EnemyGhost();
		ghost->Init();
		ghost->SetPosition({ (int)i * 150, (int)i * 150 });
		ghost->SetPlayer(_player);
		_enemyList.push_back(ghost);
	}
	for (size_t i = 0; i < 10; i++)
	{
		EnemyDoggy* doggy = new EnemyDoggy();
		doggy->Init();
		doggy->SetPosition({ (int)i * 100, (int)i * 100 });
		doggy->SetPlayer(_player);
		_enemyList.push_back(doggy);
	}
}

void SceneGame::Init()
{
	MapManager* mapManager = MapManager::GetInstance();
	VideoManager* videoManager = VideoManager::GetInstance();

	_actualMapID = mapManager->LoadAndGetMapID("maps/map2.tmx");
	mapManager->AddCollisionToLayer(_actualMapID, LAYERSNUM - 1);
	_player = Player::GetInstance();
	videoManager->SetCamera(&_camera);
	_camera.SetPlayer(_player);
	mapManager->SetCamera(&_camera);
	_player->Init();
	InitEnemies();
}

void SceneGame::ReInit()
{
	_reInit = false;
	
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->SetCamera(&_camera);
	_player->LoadCharacter();
}

void SceneGame::UpdateEnemies()
{
	size_t enemySize = _enemyList.size();
	for (size_t i = 0; i < enemySize; i++)
	{
		_enemyList[i]->Update();
		if (_enemyList[i]->IsDeletable()) {
			delete _enemyList[i];
			_enemyList.erase(_enemyList.begin() + i);
			i--;
			enemySize--;
		}
	}

	enemySize = _enemyList2.size();
	for (size_t i = 0; i < enemySize; i++)
	{
		_enemyList2[i]->Update();
		if (_enemyList2[i]->IsDeletable()) {
			delete _enemyList2[i];
			_enemyList2.erase(_enemyList2.begin() + i);
			i--;
			enemySize--;
		}
	}
}

void SceneGame::Update()
{
	InputManager* inputManager = InputManager::GetInstance();
	CollisionManager* collisionManager = CollisionManager::GetInstance();

	SceneDirector* sceneDirector = SceneDirector::GetInstance();
	GameState* gameState = GameState::GetInstance();

	if (inputManager->GetPlayerActions() != InputManager::WAITING_SELECTION) {
		switch (inputManager->GetPlayerActions()) {
		case InputManager::SELECT_WARRIOR:
			_playerSelected = GameState::PL_WARRIOR;
			break;
		case InputManager::SELECT_VALKYRIE:
			_playerSelected = GameState::PL_VALKYRIE;
			break;
		case InputManager::SELECT_WIZARD:
			_playerSelected = GameState::PL_WIZARD;
			break;
		case InputManager::SELECT_ELF:
			_playerSelected = GameState::PL_ELF;
			break;
		default:
			break;
		}
	}

	_camera.Update();
	collisionManager->Update();
	_player->Update();
	UpdateEnemies();

	PrintInfo();
	if (GameState::GetInstance()->IsGameOver())
		sceneDirector->ChangeScene(SceneEnum::GAMEOVER, false);

}

void SceneGame::RenderEnemies()
{
	size_t enemySize = _enemyList.size();
	for (size_t i = 0; i < enemySize; i++)
	{
		_enemyList[i]->Render();
	}

	enemySize = _enemyList2.size();
	for (size_t i = 0; i < enemySize; i++)
	{
		_enemyList2[i]->Render();
	}
}
void SceneGame::PrintInfo()
{
	system("cls");
	std::cout << "Player Info" << std::endl;
	std::cout << "Score: " << GameState::GetInstance()->GetScore() << std::endl;
	std::cout << "Life: " << GameState::GetInstance()->GetLife() << std::endl;
	std::cout << "Kills: " << GameState::GetInstance()->GetKills() << std::endl;
}
void SceneGame::Render()
{
	VideoManager* videoManager = VideoManager::GetInstance();
	MapManager* mapManager = MapManager::GetInstance();

	videoManager->ClearScreen(0x00000000);
	mapManager->Render(_actualMapID);
	_player->Render();
	RenderEnemies();
	videoManager->UpdateScreen();
}