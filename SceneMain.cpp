#include "SceneMain.h"
#include "VideoManager.h"
#include "ResourceManager.h"
#include "SoundManager.h"

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

    // Init the video manager
    videoManager->Init();

    // Load all the resources
    for (const char* filePath : resourcesPath) {
        resourceManager->LoadAndGetGraphicID(filePath);
    }

    // Load all the sounds
    for (const char* filePath : soundsPath) {
		soundManager->LoadAndGetSoundID(filePath);
	}

    soundManager->PrintLoadedSounds();
    resourceManager->PrintLoadedGraphics();
}