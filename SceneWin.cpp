#include "SceneWin.h"
#include <iostream>
#include "VideoManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "FontManager.h"
#include "GameState.h"

SceneWin::SceneWin()
{
    _winID = -1;
}

SceneWin::~SceneWin()
{
}

void SceneWin::Init()
{
    _winID = ResourceManager::GetInstance()->LoadAndGetGraphicID("images/win.png");
}

void SceneWin::ReInit()
{
    _reInit = false;
}

void SceneWin::Update()
{
    InputManager* inputManager = InputManager::GetInstance();
    SceneDirector* sceneDirector = SceneDirector::GetInstance();
    GameState* gameState = GameState::GetInstance();

    if (inputManager->GetPause()) {
        inputManager->SetPause(false);
        inputManager->SetPlayerActions(InputManager::WAITING_SELECTION);
        gameState->SetGameOver(false);
        gameState->SetScore(0);
        sceneDirector->ChangeScene(SceneEnum::MAIN, true);
    }
}

void SceneWin::Render()
{
    FontManager* fontManager = FontManager::GetInstance();
    VideoManager* videoManager = VideoManager::GetInstance();
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    videoManager->ClearScreen(0x00000000);
    videoManager->RenderGraphic(_winID, 100, 300, resourceManager->GetGraphicWidth(_winID), resourceManager->GetGraphicHeight(_winID));
    fontManager->RenderText(1, "Press ESC to return to main menu", { 255, 255, 255, 255 }, SCREEN_WIDTH / 5, 250);
    int score = GameState::GetInstance()->GetScore();
    std::string scoreText = std::to_string(score);
    fontManager->RenderText(1, scoreText, { 0, 255, 0, 255 }, SCREEN_WIDTH - 200, 300);
    videoManager->UpdateScreen();
}
