#include "SceneGameOver.h"
#include <iostream>
#include "VideoManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "FontManager.h"
#include "GameState.h"

void SceneGameOver::Init()
{
    _ripID = ResourceManager::GetInstance()->LoadAndGetGraphicID("images/rip.png");
}

void SceneGameOver::ReInit()
{
    _reInit = false;
}

void SceneGameOver::Update()
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

void SceneGameOver::Render()
{
    FontManager* fontManager = FontManager::GetInstance();
	VideoManager* videoManager = VideoManager::GetInstance();
    ResourceManager* resourceManager = ResourceManager::GetInstance();

    videoManager->ClearScreen(0x00000000);
    videoManager->RenderGraphic(_ripID, 100, 300, resourceManager->GetGraphicWidth(_ripID), resourceManager->GetGraphicHeight(_ripID));
    fontManager->RenderText(0, "GAME OVER", { 255, 0, 0, 255 }, SCREEN_WIDTH/5, 150);
    fontManager->RenderText(1, "Press ESC to return to main menu", { 255, 255, 255, 255 }, SCREEN_WIDTH/5, 250);
    int score = GameState::GetInstance()->GetScore();
    std::string scoreText = std::to_string(score);
    fontManager->RenderText(1, scoreText.c_str(), { 0, 255, 0, 255 }, SCREEN_WIDTH-200, 300);
    videoManager->UpdateScreen();
}
