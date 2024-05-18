#include <iostream>
#include "SceneMain.h"
#include "VideoManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "FontManager.h"
#include "Player.h"
#include "GameState.h"

using namespace std;

SceneMain::SceneMain()
{
    _menuID = -1;

    _pFontManager = nullptr;
    _pVideoManager = nullptr;
    _pInputManager = nullptr;
    _pSoundManager = nullptr;
    _pResourceManager = nullptr;
}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
    _pFontManager = FontManager::GetInstance();
    _pVideoManager = VideoManager::GetInstance();
    _pInputManager = InputManager::GetInstance();
    _pSoundManager = SoundManager::GetInstance();
    _pResourceManager = ResourceManager::GetInstance();

    const char* resourcesPath[] = {
        "images/tileset.png",
        "images/entities.png"
    };
    const char* soundsPath[] = {
        "sounds/collectFood.ogg",
        "sounds/collectGold.ogg",
        "sounds/collectKey.ogg",
        "sounds/collectPotion.ogg",
        "sounds/exitLevel.ogg",
        "sounds/femalePain.ogg",
        "sounds/femalePain2.ogg",
        "sounds/malePain.ogg",
        "sounds/malePain2.ogg",
        "sounds/fireElf.ogg",
        "sounds/fireValkyrie.ogg",
        "sounds/fireWarrior.ogg",
        "sounds/fireWizard.ogg",
        "sounds/generatorDeath.ogg",
        "sounds/highscore.ogg",
        "sounds/monsterDeath.ogg",
        "sounds/monsterDeath2.ogg",
        "sounds/monsterDeath3.ogg",
        "sounds/openDoor.ogg",
        "sounds/weak.ogg"
    };
    vector<pair<string, int>> fonts = {
        { "fonts/gauntletMenu.ttf", 100 },
        { "fonts/gauntletMenu.ttf", 30 },
    };

    // Init the video manager
    _pVideoManager->Init();
    // Init the sound manager
    _pSoundManager->Init();
    // Init the font manager
    _pFontManager->Init();

    _menuID = _pResourceManager->LoadAndGetGraphicID("images/menuBackground.png");

    // Load all the resources
    for (const char* filePath : resourcesPath)
        _pResourceManager->LoadAndGetGraphicID(filePath);

    // Load all the sounds
    for (const char* filePath : soundsPath)
        _pSoundManager->LoadAndGetSoundID(filePath);

    // Load all the fonts
    for (const auto& font : fonts)
        _pFontManager->LoadAndGetFontID(font.first, font.second);

    _pResourceManager->PrintLoadedGraphics();
    _pSoundManager->PrintLoadedSounds();
    _pFontManager->PrintLoadedFonts();
}

void SceneMain::ReInit()
{
    _reInit = false;
}

void SceneMain::Update()
{
    // Update the input manager
    _pInputManager->Update();

    switch (_pInputManager->GetPlayerActions()) {
    case InputManager::SELECT_WARRIOR:
        GameState::GetInstance()->SetPlayerSelected(GameState::PL_WARRIOR);
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::GAME, true);
        break;
    case InputManager::SELECT_VALKYRIE:
        GameState::GetInstance()->SetPlayerSelected(GameState::PL_VALKYRIE);
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::GAME, true);
        break;
    case InputManager::SELECT_WIZARD:
        GameState::GetInstance()->SetPlayerSelected(GameState::PL_WIZARD);
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::GAME, true);
        break;
    case InputManager::SELECT_ELF:
        GameState::GetInstance()->SetPlayerSelected(GameState::PL_ELF);
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::GAME, true);
        break;
    case InputManager::SELECT_HIGHSCORE:
        SceneDirector::GetInstance()->ChangeScene(SceneEnum::HIGHSCORE, true);
        break;
    default:
        break;
    }
}

void SceneMain::Render()
{
    _pVideoManager->ClearScreen(0x00000000);
    _pVideoManager->RenderGraphic(_menuID, 11, 16, 768, 768);
    _pFontManager->RenderText(1, "Press 5 to see the HIGHSCORE", { 0, 0, 40, 255 }, ((SCREEN_WIDTH / 2) - 175), 27.5);
    _pFontManager->RenderText(0, "GAUNTLET", { 0, 0, 40, 255 }, (SCREEN_WIDTH / 2 - 210), 100);
    _pFontManager->RenderText(1, "Press 1", { 200, 0, 0, 255 }, 75, 620);
    _pFontManager->RenderText(1, "VALKYRIE", { 140, 0, 0, 255 }, 52, 657);
    _pFontManager->RenderText(1, "Press 2", { 0, 80, 0, 255 }, 260, 620);
    _pFontManager->RenderText(1, "ELF", { 0, 120, 0, 255 }, 276, 657);
    _pFontManager->RenderText(1, "Press 3", { 80, 80, 0, 255 }, 440, 620);
    _pFontManager->RenderText(1, "WIZARD", { 120, 120, 0, 255 }, 435, 657);
    _pFontManager->RenderText(1, "Press 4", { 0, 0, 200, 255 }, 630, 620);
    _pFontManager->RenderText(1, "WARRIOR", { 0, 0, 140, 255 }, 617, 657);
    _pVideoManager->UpdateScreen();
}