#include "SceneGame.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "MapManager.h"
#include <iostream>

using namespace std;

SceneGame::SceneGame()
{
	_actualMapID = -1;
	_player = nullptr;
}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	MapManager* mapManager = MapManager::GetInstance();
	VideoManager* videoManager = VideoManager::GetInstance();
	_player = Player::GetInstance();

	_actualMapID = mapManager->LoadAndGetMapID("maps/map1.tmx");
	videoManager->SetCamera(&_camera);
	_camera.SetPlayer(_player);
	mapManager->SetCamera(&_camera);
	_player->Init();
}

void SceneGame::ReInit()
{
	_reInit = false;
	
	VideoManager* videoManager = VideoManager::GetInstance();
	videoManager->SetCamera(&_camera);
	_player->LoadCharacter();
}

void SceneGame::Update()
{
	InputManager* inputManager = InputManager::GetInstance();

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
	_player->Update();
}

void SceneGame::Render()
{
	VideoManager* videoManager = VideoManager::GetInstance();
	MapManager* mapManager = MapManager::GetInstance();
	/*
	switch (_playerSelected) {
		case WARRIOR:
			cout << "WARRIOR" << endl;
			break;
		case VALKYRIE:
			cout << "VALKYRIE" << endl;
			break;
		case WIZARD:
			cout << "WIZARD" << endl;
			break;
		case ELF:
			cout << "ELF" << endl;
			break;
		default:
			break;
	}*/

	videoManager->ClearScreen(0x00000000);
	mapManager->Render(_actualMapID);
	_player->Render();
	videoManager->UpdateScreen();
}