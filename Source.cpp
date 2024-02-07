#include <iostream>
#include "VideoManager.h"
#include "SoundManager.h"
#include <SDL.h>

using namespace std;

int main(int argc, char* args[]) {
	bool _end = false;
	SDL_Event _events;

	VideoManager* videoManager = VideoManager::GetInstance();
	SoundManager* soundManager = SoundManager::GetInstance();

	// Init of the instances
	videoManager->Init();
	soundManager->Init();

	int firstFighter, secondFighter, thirdFighter;
	firstFighter = soundManager->LoadAndGetSoundID("./Assets/sound1.mp3");
	secondFighter = soundManager->LoadAndGetSoundID("./Assets/sound2.mp3");
	thirdFighter = soundManager->LoadAndGetSoundID("./Assets/sound3.mp3");
	soundManager->PrintLoadedSounds();
	soundManager->RemoveSound("./Assets/sound1.mp3");
	soundManager->PrintLoadedSounds();
	secondFighter = soundManager->LoadAndGetSoundID("./Assets/sound2.mp3");
	soundManager->PrintLoadedSounds();

	while (!_end) {
		while (SDL_PollEvent(&_events)) {
			switch (_events.type) {
			case SDL_KEYDOWN:
				switch (_events.key.keysym.scancode) {
				case SDL_SCANCODE_1:
					soundManager->PlayFromStart(firstFighter);
					break;
				case SDL_SCANCODE_2:
					soundManager->PlayFromStart(secondFighter);
					break;
				case SDL_SCANCODE_3:
					soundManager->PlayFromStart(thirdFighter);
					break;
				case SDL_SCANCODE_4:
					soundManager->Pause(firstFighter);
					break;
				case SDL_SCANCODE_5:
					soundManager->Pause(secondFighter);
					break;
				case SDL_SCANCODE_6:
					soundManager->Pause(thirdFighter);
					break;
				case SDL_SCANCODE_7:
					soundManager->Resume(firstFighter);
					break;
				case SDL_SCANCODE_8:
					soundManager->Resume(secondFighter);
					break;
				case SDL_SCANCODE_9:
					soundManager->Resume(thirdFighter);
					break;
				case SDL_SCANCODE_0:
					soundManager->PrintLoadedSounds();
					break;
				case SDL_SCANCODE_ESCAPE:
					_end = true;
					break;
				default:
					break;
				}
				break;
			case SDL_QUIT:
				_end = true;
				break;
			}
		}
	}

	videoManager->Close();

	return 0;
}