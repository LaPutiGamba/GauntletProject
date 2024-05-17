#include "SceneGame.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "MapManager.h"
#include "SceneDirector.h"
#include "Player.h"
#include "EnemyGhost.h"
#include "ObjectChest.h"
#include "EnemyGenerator.h"
#include "TinyXML2/tinyxml2.h"
#include <iostream>
#include "GameState.h"
using namespace std;
using namespace tinyxml2;


SceneGame::SceneGame()
{
	_actualMapID = -1;
	_player = nullptr;
	_playerSelected = GameState::PL_WARRIOR;

	_enemies.resize(0);
	_objects.resize(0);
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

	_actualMapID = mapManager->LoadAndGetMapID("maps/map1.tmx");
	mapManager->AddCollisionToLayer(_actualMapID, LAYERSNUM - 1);

	_player = Player::GetInstance();
	videoManager->SetCamera(&_camera);
	_camera.SetPlayer(_player);
	mapManager->SetCamera(&_camera);
	_player->Init();
	//InitEnemies();

	ReadLevelInfo("maps/map1Info.tmx");
	size_t enemiesLength = _enemies.size();
	for (size_t i = 0; i < enemiesLength; i++)
		_enemies[i].Init();
	size_t objectsLength = _objects.size();
	for (size_t i = 0; i < objectsLength; i++) {
		_objects[i]->Init();

		if (_objects[i]->GetType() == Object::ObjectType::OBJ_ENEMY_GENERATOR) {
			EnemyGenerator* generator = dynamic_cast<EnemyGenerator*>(_objects[i]);
			generator->SelectGenerator("EnemyGhostGenerator", 1);
		}
	}
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

	size_t enemiesLength = _enemies.size();
	for (size_t i = 0; i < enemiesLength; i++)
		_enemies[i].Update();

	size_t objectsLength = _objects.size();
	for (size_t i = 0; i < objectsLength; i++) {
		_objects[i]->Update();

		if (_objects[i]->ShouldDestroy()) {
			_objects[i]->Destroy();
			delete _objects[i];
			_objects.erase(_objects.begin() + i);
			objectsLength--;
			i--;

			_player->GetCollider()->collisions.clear();
		}
	}

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

	size_t enemiesLength = _enemies.size();
	for (size_t i = 0; i < enemiesLength; i++)
		_enemies[i].Render();

	size_t objectsLength = _objects.size();
	for (size_t i = 0; i < objectsLength; i++)
		_objects[i]->Render();

	_player->Render();
	RenderEnemies();
	videoManager->UpdateScreen();
}

int SceneGame::ReadLevelInfo(const char* filename)
{
	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
		return -1;

	XMLElement* map = doc.FirstChildElement("map");
	if (map == NULL)
		return -1;

	XMLElement* player = map->FirstChildElement("player");
	if (player != NULL)
		_player->SetPosition({ player->IntAttribute("x"), player->IntAttribute("y") });

	XMLElement* enemies = map->FirstChildElement("enemies");
	if (enemies != NULL) {
		XMLElement* enemy = enemies->FirstChildElement("enemy");

		while (enemy != NULL) {
			Enemy enemyToCreate;

			const XMLAttribute* typeAttribute = enemy->FindAttribute("type");
			string type = typeAttribute->Value();
			if (type == "ghost")
				enemyToCreate = EnemyGhost();

			size_t enemiesToCreate = stoi(enemy->GetText());
			for (size_t i = 0; i < enemiesToCreate; i++) {
				int widthMin = enemy->IntAttribute("widthMin");
				int widthMax = enemy->IntAttribute("widthMax");
				int heightMin = enemy->IntAttribute("heightMin");
				int heightMax = enemy->IntAttribute("heightMax");

				int randomX = rand() % (widthMax - widthMin + 1) + widthMin;
				int randomY = rand() % (heightMax - heightMin + 1) + heightMin;

				if (MapManager::GetInstance()->GetIDFromLayer(0, randomX, randomY) < 10) {
					enemyToCreate.SetPosition({ randomX, randomY });
					_enemies.push_back(enemyToCreate);
				}
			}

			enemy = enemy->NextSiblingElement("enemy");
		}
	}

	XMLElement* objects = map->FirstChildElement("objects");
	if (objects != NULL) {
		XMLElement* object = objects->FirstChildElement("object");

		while (object != NULL) {
			const XMLAttribute* attribute = object->FindAttribute("type");
			Object* objectToCreate = nullptr;

			string type = attribute->Value();
			// Normal objects
			if (type == "chest")
				objectToCreate = new ObjectChest();
			
			// Generators
			if (type == "enemyGhostGenerator") {
				objectToCreate = new EnemyGenerator();
				objectToCreate->SetType(Object::ObjectType::OBJ_ENEMY_GENERATOR);
			}

			if (objectToCreate) {
				objectToCreate->SetPosition({ object->IntAttribute("x"), object->IntAttribute("y") });
				_objects.push_back(objectToCreate);
			}

			object = object->NextSiblingElement("object");
		}
	}

	return 0;
}