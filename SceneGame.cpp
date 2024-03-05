#include "SceneGame.h"
#include "InputManager.h"
#include <iostream>

using namespace std;

SceneGame::SceneGame()
{
	_playerSelected = WARRIOR;
}

SceneGame::~SceneGame()
{

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
}