#include "SceneMain.h"
#include "VideoManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "SceneDirector.h"
#include "FontManager.h"
#include <iostream>

using namespace std;

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
    VideoManager* videoManager = VideoManager::GetInstance();
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    SoundManager* soundManager = SoundManager::GetInstance();
    FontManager* fontManager = FontManager::GetInstance();

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
    videoManager->Init();
    // Init the sound manager
    soundManager->Init();
    // Init the font manager
    fontManager->Init();

    _menuID = resourceManager->LoadAndGetGraphicID("images/menuBackground.png");

    // Load all the resources
    for (const char* filePath : resourcesPath)
        resourceManager->LoadAndGetGraphicID(filePath);

    // Load all the sounds
    for (const char* filePath : soundsPath)
        soundManager->LoadAndGetSoundID(filePath);

    // Load all the fonts
    for (const auto& font : fonts)
        fontManager->LoadAndGetFontID(font.first, font.second);

    resourceManager->PrintLoadedGraphics();
    soundManager->PrintLoadedSounds();
    fontManager->PrintLoadedFonts();
}

void SceneMain::ReInit()
{
    _reInit = false;
}

void SceneMain::Update()
{
	InputManager* inputManager = InputManager::GetInstance();
    SceneDirector* sceneDirector = SceneDirector::GetInstance();

    // Update the input manager
	inputManager->Update();

    switch (inputManager->GetDirection()) {
    case InputManager::DIR_UP:
		cout << "UP" << endl;
		break;
    case InputManager::DIR_DOWN:
        cout << "DOWN" << endl;
        break;
    case InputManager::DIR_LEFT:
        cout << "LEFT" << endl;
	    break;
    case InputManager::DIR_RIGHT:
        cout << "RIGHT" << endl;
		break;
    default:
        break;
    }

    switch (inputManager->GetPlayerActions()) {
    case InputManager::SELECT_WARRIOR:
        sceneDirector->ChangeScene(SceneEnum::GAME, false);
		break;
	case InputManager::SELECT_VALKYRIE:
        sceneDirector->ChangeScene(SceneEnum::GAME, false);
		break;
    case InputManager::SELECT_WIZARD:
        sceneDirector->ChangeScene(SceneEnum::GAME, false);
        break;
    case InputManager::SELECT_ELF:
        sceneDirector->ChangeScene(SceneEnum::GAME, false);
		break;
    default:
        break;
    }
}

void SceneMain::Render()
{
    VideoManager* videoManager = VideoManager::GetInstance();
    ResourceManager* resourceManager = ResourceManager::GetInstance();
    FontManager* fontManager = FontManager::GetInstance();
    
    videoManager->ClearScreen(0x00000000);
    videoManager->RenderGraphic(_menuID, 11, 16, 768, 768);
    fontManager->RenderText(0, "GAUNTLET", { 0, 0, 40, 255 }, (SCREEN_WIDTH / 2 - 210), 100);
    fontManager->RenderText(1, "VALKYRIE", { 140, 0, 0, 255 }, 52, 657);
    fontManager->RenderText(1, "ELF", { 0, 120, 0, 255 }, 276, 657);
    fontManager->RenderText(1, "WIZARD", { 120, 120, 0, 255 }, 435, 657);
    fontManager->RenderText(1, "WARRIOR", { 0, 0, 140, 255}, 617, 657);
    videoManager->UpdateScreen();
}