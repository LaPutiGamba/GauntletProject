#include "SceneGame.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "MapManager.h"
#include <iostream>

using namespace std;

SceneGame::SceneGame()
{
	_playerSelected = WARRIOR;
	_actualMapID = -1;
}

SceneGame::~SceneGame()
{

}

void SceneGame::Init()
{
	MapManager* mapManager = MapManager::GetInstance();
	_actualMapID = mapManager->LoadAndGetMapID("maps/map1.tmx");
}

void SceneGame::ReInit()
{
	_reInit = false;
}

void SceneGame::Update()
{
	InputManager* inputManager = InputManager::GetInstance();

	if (inputManager->GetPlayerActions() != InputManager::WAITING_SELECTION) {
		switch (inputManager->GetPlayerActions()) {
			case InputManager::SELECT_WARRIOR:
				_playerSelected = WARRIOR;
				break;
			case InputManager::SELECT_VALKYRIE:
				_playerSelected = VALKYRIE;
				break;
			case InputManager::SELECT_WIZARD:
				_playerSelected = WIZARD;
				break;
			case InputManager::SELECT_ELF:
				_playerSelected = ELF;
				break;
			default:
				break;
		}
	}
}

void SceneGame::Render()
{
	VideoManager* videoManager = VideoManager::GetInstance();
	MapManager* mapManager = MapManager::GetInstance();

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
	}

	videoManager->ClearScreen(0x00000000);
	mapManager->Render(_actualMapID);
	videoManager->UpdateScreen();
}