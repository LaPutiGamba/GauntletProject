#include "SceneGame.h"
#include "SceneDirector.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "FontManager.h"
#include "MapManager.h"
#include "Player.h"
#include "EnemyGhost.h"
#include "ObjectChest.h"
#include "ObjectDoor.h"
#include "EnemyGenerator.h"
#include "TinyXML2/tinyxml2.h"
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;
using namespace tinyxml2;

SceneGame::SceneGame()
{
    _actualMapID = -1;
    _player = nullptr;
    _playerSelected = GameState::PL_WARRIOR;

    _pEnemies.resize(0);
    _pObjects.resize(0);

    _playerName = "";
    _bIsNameSet = false;
    _selectedKeyboardKey = 65;
	_seconds = 0;
	_minutes = 0;

    _camera = new Camera();
}

SceneGame::~SceneGame()
{

}

void SceneGame::SaveScore(string name, int points)
{
    fstream fileHandler;

    // Adding the points to the points list file of the top 10 best punctuations.
    fileHandler.open("ScoreList.txt", ios::app); // Opening the file in the reading mode.

    fileHandler << name << "|" << points << ",";

    fileHandler.close(); // Closing the file. 
}

void SceneGame::Init()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    MapManager* mapManager = MapManager::GetInstance();

    _actualMapID = mapManager->LoadAndGetMapID("maps/map1.tmx");
    mapManager->AddCollisionToLayer(_actualMapID, LAYERSNUM - 1);

    _player = Player::GetInstance();
    VideoManager::GetInstance()->SetCamera(_camera);
    _camera->SetPlayer(_player);
    mapManager->SetCamera(_camera);
    _player->Init();

    ReadLevelInfo("maps/map1Info.tmx");
    const size_t enemiesLength = _pEnemies.size();
    for (size_t i = 0; i < enemiesLength; i++)
        _pEnemies[i]->Init();
    const size_t objectsLength = _pObjects.size();
    for (size_t i = 0; i < objectsLength; i++) {
        _pObjects[i]->Init();

        if (_pObjects[i]->GetType() == Object::ObjectType::OBJ_ENEMY_GENERATOR) {
            auto* generator = dynamic_cast<EnemyGenerator*>(_pObjects[i]);
            generator->SelectGenerator("EnemyGhostGenerator", 1);
        }
    }
    _seconds = 0;
    _minutes = 0;
    _timer.Init();
}

void SceneGame::ReInit()
{
    _reInit = false;
    
    Init();
    _player->LoadCharacter();
}

void SceneGame::Update()
{
    InputManager* inputManager = InputManager::GetInstance();
    CollisionManager* collisionManager = CollisionManager::GetInstance();
    SceneDirector* sceneDirector = SceneDirector::GetInstance();
    GameState* gameState = GameState::GetInstance();

    if (gameState->IsGameOver()) {
        _camera->SetX(0);
        _camera->SetY(0);
        if (!_playerName.empty())
            SaveScore(_playerName, gameState->GetScore());
        sceneDirector->ChangeScene(SceneEnum::GAMEOVER, true);
    } else {
        if (!_bIsNameSet) {
            switch (inputManager->GetPlayerActions()) {
            case InputManager::SELECT_BACK:
                if (!_playerName.empty())
                    _playerName.pop_back();
                break;
            case InputManager::SELECT_EXIT:
                _bIsNameSet = true;
                break;
            default:
                break;
            }

            if (inputManager->GetDirection() == InputManager::DIR_LEFT) {
                if (_selectedKeyboardKey == 65)
                    _selectedKeyboardKey = 90;
                else
                    _selectedKeyboardKey--;

                inputManager->FreeKeys(InputManager::DIR_LEFT);
            } else if (inputManager->GetDirection() == InputManager::DIR_RIGHT) {
                if (_selectedKeyboardKey == 90)
                    _selectedKeyboardKey = 65;
                else
                    _selectedKeyboardKey++;

                inputManager->FreeKeys(InputManager::DIR_RIGHT);
            }

            if (inputManager->GetSpecialKey() == InputManager::DIR_SHOOTING) {
                if (_playerName.size() < 9)
                    _playerName += static_cast<char>(_selectedKeyboardKey);
                else
                    inputManager->SetPlayerActions(InputManager::SELECT_EXIT);
            }
        } else {
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

            _camera->Update();
            collisionManager->Update();

            size_t enemiesLength = _pEnemies.size();
            for (size_t i = 0; i < enemiesLength; i++) {
                _pEnemies[i]->Update();

                if (_pEnemies[i]->IsDeletable()) {
                    _pEnemies[i]->Destroy();
                    delete _pEnemies[i];
                    _pEnemies.erase(_pEnemies.begin() + i);
                    enemiesLength--;
                    i--;

                    _player->GetCollider()->collisions.clear();
                }
            }

            size_t objectsLength = _pObjects.size();
            for (size_t i = 0; i < objectsLength; i++) {
                _pObjects[i]->Update();

                if (_pObjects[i]->IsDeletable()) {
                    _pObjects[i]->Destroy();
                    delete _pObjects[i];
                    _pObjects.erase(_pObjects.begin() + i);
                    objectsLength--;
                    i--;

                    _player->GetCollider()->collisions.clear();
                }
            }

          _player->Update();
        }
    }
    if (_timer.GetTicks() < 1000) {
        return;
    }
    _seconds++;
	if (_seconds >= 60) {
		_minutes++;
		_seconds = 0;
	}
	_timer.StartTimer();
}

void SceneGame::PrintKeyboard()
{
    FontManager* fontManager = FontManager::GetInstance();

    fontManager->RenderText(0, "Enter your name: ", { 255, 255, 255, 255 }, 90, (SCREEN_HEIGHT / 2 - 250));
    if (!_playerName.empty())
        fontManager->RenderText(0, _playerName, { 255, 0, 0, 255 }, 100, (SCREEN_HEIGHT / 2 - 150));

    string keys = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 9; i++) {
        int xPos = 50 + 74 * i;
        fontManager->RenderText(0, string(1, keys[i]), { 255, 255, 255, 255 }, xPos, (SCREEN_HEIGHT / 2 - 50));
    }
    fontManager->RenderText(0, string(1, keys[9]), { 255, 255, 255, 255 }, (60 + (74 * 8)) + 40, (SCREEN_HEIGHT / 2 - 50));
    for (int i = 0; i < 9; i++) {
        int xPos = 70 + 74 * i;
        fontManager->RenderText(0, string(1, keys[i + 10]), { 255, 255, 255, 255 }, xPos, (SCREEN_HEIGHT / 2 + 50));
    }
    for (int i = 0; i < 7; i++) {
        int xPos = 140 + 74 * i;
        fontManager->RenderText(0, string(1, keys[i + 19]), { 255, 255, 255, 255 }, xPos, (SCREEN_HEIGHT / 2 + 150));
    }

    string selectedKey = string(1, _selectedKeyboardKey);
    if (_selectedKeyboardKey >= 65 && _selectedKeyboardKey <= 73)
        fontManager->RenderText(0, selectedKey, { 255, 0, 0, 255 }, 50 + (74 * (selectedKey[0] - 65)), (SCREEN_HEIGHT / 2 - 50));
    else if (_selectedKeyboardKey == 74)
        fontManager->RenderText(0, selectedKey, { 255, 0, 0, 255 }, (60 + (74 * 8)) + 40, (SCREEN_HEIGHT / 2 - 50));
    else if (_selectedKeyboardKey >= 75 && _selectedKeyboardKey <= 83)
        fontManager->RenderText(0, selectedKey, { 255, 0, 0, 255 }, 70 + (74 * (selectedKey[0] - 75)), (SCREEN_HEIGHT / 2 + 50));
    else if (_selectedKeyboardKey >= 84 && _selectedKeyboardKey <= 90)
        fontManager->RenderText(0, selectedKey, { 255, 0, 0, 255 }, 140 + (74 * (selectedKey[0] - 84)), (SCREEN_HEIGHT / 2 + 150));
}

void SceneGame::Render()
{
    VideoManager* videoManager = VideoManager::GetInstance();
    FontManager* fontManager = FontManager::GetInstance();

    videoManager->ClearScreen(0x00000000);
    
    if (!_bIsNameSet) {
        PrintKeyboard();
    } else {
        MapManager::GetInstance()->Render(_actualMapID);

        const size_t enemiesLength = _pEnemies.size();
        for (size_t i = 0; i < enemiesLength; i++)
          _pEnemies[i]->Render();

        const size_t objectsLength = _pObjects.size();
        for (size_t i = 0; i < objectsLength; i++)
            _pObjects[i]->Render();

        _player->Render();

        // Print text state in white color
        fontManager->RenderText(1, "Score: ", { 255, 255, 255, 255 }, 10, 10);
        // Print the score in blue purple color
        fontManager->RenderText(1, to_string(GameState::GetInstance()->GetScore()), { 128, 0, 128, 255 }, 100, 10);
        // Print text Player in white color
        fontManager->RenderText(1, "Player: ", { 255, 255, 255, 255 }, 10, 40);
        // If player is valkyrie print in red color, if player is warrior print in blue, if player is wizard print in yellow, if player is elf print in green
        switch (_playerSelected) {
        case GameState::PL_WARRIOR:
            fontManager->RenderText(1, "War", { 0, 0, 255, 255 }, 100, 40);
            break;
        case GameState::PL_VALKYRIE:
            fontManager->RenderText(1, "Valk", { 255, 0, 0, 255 }, 100, 40);
            break;
        case GameState::PL_WIZARD:
            fontManager->RenderText(1, "Wiz", { 255, 255, 0, 255 }, 100, 40);
            break;
        case GameState::PL_ELF:
            fontManager->RenderText(1, "Elf", { 0, 255, 0, 255 }, 100, 40);
            break;
        }

        // Print text Life in white color
        fontManager->RenderText(1, "Life: ", { 255, 255, 255, 255 }, 10, 70);
        // Print the life in red color
        fontManager->RenderText(1, to_string(GameState::GetInstance()->GetLife()), { 255, 0, 0, 255 }, 100, 70);
	    // Print text Time in white color
	    fontManager->RenderText(1, "Time: ", { 255, 255, 255, 255 }, 600, 10);
        // Print the time in green color
	    fontManager->RenderText(1, to_string(_minutes) + ":" + to_string(_seconds), { 0, 255, 0, 255 }, 700, 10);
    }

    videoManager->UpdateScreen();
}

int SceneGame::ReadLevelInfo(const char* filename)
{
    for (auto* enemy : _pEnemies) {
        enemy->Destroy();
        delete enemy;
    }
    _pEnemies.clear();
    for (auto* object : _pObjects) {
        object->Destroy();
        delete object;
    }
    _pObjects.clear();

    XMLDocument doc;
    if (doc.LoadFile(filename) != XML_SUCCESS)
        return -1;

    XMLElement* map = doc.FirstChildElement("map");
    if (map == nullptr)
        return -1;

    XMLElement* player = map->FirstChildElement("player");
    if (player != nullptr)
        _player->SetPosition({ player->IntAttribute("x"), player->IntAttribute("y") });

    XMLElement* enemies = map->FirstChildElement("enemies");
    if (enemies != nullptr) {
        XMLElement* enemy = enemies->FirstChildElement("enemy");

        while (enemy != nullptr) {
            std::vector<Entity::Position> uniquePositions;
            int widthMin, widthMax, heightMin, heightMax;
            widthMin = enemy->IntAttribute("widthMin");
            widthMax = enemy->IntAttribute("widthMax");
            heightMin = enemy->IntAttribute("heightMin");
            heightMax = enemy->IntAttribute("heightMax");

            const XMLAttribute* typeAttribute = enemy->FindAttribute("type");
            string type = typeAttribute->Value();

            size_t enemiesToCreate = stoi(enemy->GetText());

            for (size_t i = 0; i < enemiesToCreate; i++) {
                Enemy* enemyToCreate = nullptr;
                if (type == "ghost")
                    enemyToCreate = new EnemyGhost();

                int randomX, randomY;
                Entity::Position position;
                bool isValid;

                do {
                    isValid = true;

                    randomX = rand() % (widthMax - widthMin + 1) + widthMin;
                    randomY = rand() % (heightMax - heightMin + 1) + heightMin;
                    position = { randomX, randomY };

                    int id = MapManager::GetInstance()->GetIDFromLayer(_actualMapID, 0, randomX, randomY);
                    if (id >= 10 || id <= 0) 
                        isValid = false;

                    for (const auto pos : uniquePositions) {
                        if (pos.x == position.x && pos.y == position.y) {
                            isValid = false;
                            break;
                        }
                    }
                } while (!isValid);

                uniquePositions.push_back(position);
                enemyToCreate->SetPosition(position);
                enemyToCreate->SetMapID(_actualMapID);
                _pEnemies.push_back(enemyToCreate);
            }

            enemy = enemy->NextSiblingElement("enemy");
        }
    }

    XMLElement* objects = map->FirstChildElement("objects");
    if (objects != nullptr) {
        XMLElement* object = objects->FirstChildElement("object");

        while (object != nullptr) {
            const XMLAttribute* attribute = object->FindAttribute("type");
            Object* objectToCreate = nullptr;

            string type = attribute->Value();
            // Normal objects
            if (type == "chest")
                objectToCreate = new ObjectChest();

            // Doors
            if (type == "door") {
                objectToCreate = new ObjectDoor();
                dynamic_cast<ObjectDoor*>(objectToCreate)->SetCamera(_camera);
            }

            // Generators
            if (type == "enemyGhostGenerator") {
                objectToCreate = new EnemyGenerator();
                objectToCreate->SetType(Object::ObjectType::OBJ_ENEMY_GENERATOR);
            }

            if (objectToCreate) {
                objectToCreate->SetPosition({ object->IntAttribute("x"), object->IntAttribute("y") });
                _pObjects.push_back(objectToCreate);
            }

            object = object->NextSiblingElement("object");
        }
    }

    return 0;
}