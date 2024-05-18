#include "SceneGame.h"
#include "SceneDirector.h"
#include "InputManager.h"
#include "VideoManager.h"
#include "FontManager.h"
#include "MapManager.h"
#include "Player.h"
#include "EnemyGhost.h"
#include "ObjectChest.h"
#include "EnemyGenerator.h"
#include "TinyXML2/tinyxml2.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
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
    srand((time_t)time((time_t* const)nullptr));

    MapManager* mapManager = MapManager::GetInstance();

    _actualMapID = mapManager->LoadAndGetMapID("maps/map1.tmx");
    mapManager->AddCollisionToLayer(_actualMapID, LAYERSNUM - 1);

    _player = Player::GetInstance();
    VideoManager::GetInstance()->SetCamera(&_camera);
    _camera.SetPlayer(_player);
    mapManager->SetCamera(&_camera);
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
        _camera.SetX(0);
        _camera.SetY(0);
        sceneDirector->ChangeScene(SceneEnum::GAMEOVER, true);
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

            if (!_bIsNameSet) {
                switch (inputManager->GetPlayerActions()) {
                case InputManager::SELECT_BACK:
                    if (!_playerName.empty())
                        _playerName.pop_back();
                    break;
                case InputManager::SELECT_EXIT:
                    if (!_bIsNameSet) {
                        //SaveScore(_playerName, GameState::GetInstance()->GetScore());
                        _bIsNameSet = true;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        if (!_bIsNameSet) {
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
        }

        _camera.Update();
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
    }

    videoManager->UpdateScreen();
}

int SceneGame::ReadLevelInfo(const char* filename)
{
    _pEnemies.clear();
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
            const XMLAttribute* typeAttribute = enemy->FindAttribute("type");
            string type = typeAttribute->Value();

            size_t enemiesToCreate = stoi(enemy->GetText());
            int widthMin, widthMax, heightMin, heightMax;
            int randomY, randomX;
            for (size_t i = 0; i < enemiesToCreate; i++) {
                Enemy* enemyToCreate = nullptr;
                if (type == "ghost")
                    enemyToCreate = new EnemyGhost();

                widthMin = enemy->IntAttribute("widthMin");
                widthMax = enemy->IntAttribute("widthMax");
                heightMin = enemy->IntAttribute("heightMin");
                heightMax = enemy->IntAttribute("heightMax");

                randomX = rand() % (widthMax - widthMin + 1) + widthMin;
                randomY = rand() % (heightMax - heightMin + 1) + heightMin;

                bool isColliding = true;
                while (isColliding) {
                    isColliding = false;
                    for (const auto& enemyCheck : _pEnemies) {
                        if (enemyCheck->GetPosition().x == randomX && enemyCheck->GetPosition().y == randomY) {
                            isColliding = true;
                            randomX = rand() % (widthMax - widthMin + 1) + widthMin;
                            randomY = rand() % (heightMax - heightMin + 1) + heightMin;
                            break;
                        }
                    }
                }

                while (MapManager::GetInstance()->GetIDFromLayer(LAYERSNUM - 1, randomX, randomY) < 10) {
                    randomX = rand() % (widthMax - widthMin + 1) + widthMin;
                    randomY = rand() % (heightMax - heightMin + 1) + heightMin;
                }

                enemyToCreate->SetPosition({ randomX, randomY });
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