#include "SoundManager.h"
#include <SDL_mixer.h>
#include <iostream>

SoundManager* SoundManager::_pInstance = NULL;

SoundManager::SoundManager()
{
    Init();
}

bool SoundManager::Init()
{
    // Initialization flag
    bool success = true;

	// Initialize MP3 and OGG loading
	int imgFlags = MIX_INIT_MP3 | MIX_INIT_OGG;
	if (!(Mix_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image could not initialize! SDL_image Error: \n" << Mix_GetError();
		success = false;
	} else {
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
			// Initialize SDL Mixer
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: \n" << Mix_GetError();
			success = false;
		} else {
			if (Mix_AllocateChannels(128) <= 0) {
				std::cout << "Could not allocate channels! SDL_mixer Error: \n" << Mix_GetError();
				success = false;
			}
		}
	}

    return success;
}

void SoundManager::RemoveSound(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.find(file);

	if (it == _idMap.end()) {
		std::cout << "There's no file with that name loaded. Can't delete it." << std::endl;
		return;
	}

	Uint32 ID = it->second;

	Mix_FreeChunk(_soundsVector.at(ID));

	_soundsVector.at(ID) = NULL;
	_idMap.erase(file);
	UpdateFirstFreeSlotGraphic();
}

Sint32 SoundManager::LoadAndGetSoundID(const char* _file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.find(_file);

	Sint32 returnValue = -1;
	if (it != _idMap.end()) {
		return it->second;
	} else {
		Sint32 index = AddSound(_file);

		if (index != -1)
			returnValue = index;
	}
	return returnValue;
}

std::string SoundManager::GetSoundPathByID(Sint32 ID)
{
	if (ID < 0 || ID >= static_cast<Sint32>(_soundsVector.size()))
		return "NULL";

	for (std::map<std::string, Sint32>::iterator it = _idMap.begin(); it != _idMap.end(); it++) {
		if (it->second == ID)
			return it->first;
	}
	return "NULL";
}

Mix_Chunk* SoundManager::GetSoundByID(Sint32 ID)
{
	if (ID < 0)
		return NULL;
	else if (ID < static_cast<Sint32>(_soundsVector.size()))
		return _soundsVector[ID];
	else
		return NULL;
}

void SoundManager::PrintLoadedSounds()
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.begin();
	std::cout << "------------------ ALL LOADED SOUNDS ------------------\n";
	while (it != _idMap.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << "-------------------------------------------------------\n";
}

Sint32 SoundManager::AddSound(const char* file)
{
	Mix_Chunk* loadedSound = NULL;

	loadedSound = Mix_LoadWAV(file);

	Sint32 returnValue = -1;

	if (loadedSound != NULL) {
		if (_firstFreeSlot == _soundsVector.size()) {
			_soundsVector.push_back(loadedSound);
			_firstFreeSlot++;
			returnValue = (Sint32)(_soundsVector.size() - 1);
			_idMap.insert(std::pair<std::string, Sint32>(file, returnValue));
		} else {
			_soundsVector.at(_firstFreeSlot) = loadedSound;
			returnValue = _firstFreeSlot;
			UpdateFirstFreeSlotGraphic();
			_idMap.insert(std::pair<std::string, Sint32>(file, returnValue));
		}
	}

	return returnValue;
}

void SoundManager::UpdateFirstFreeSlotGraphic()
{
	_firstFreeSlot = -1;

	for (Uint32 i = 0; i < _soundsVector.size(); i++) {
		if (_soundsVector.at(i) == NULL)
			_firstFreeSlot = i;
	}

	if (_firstFreeSlot == -1) _firstFreeSlot = (Uint32)_soundsVector.size();
}

int SoundManager::PlayFromStart(int ID, int loops)
{
	return Mix_PlayChannel(-1, _soundsVector.at(ID), loops);
}

int SoundManager::Play(int ID, int second, int loops)
{
	int returnValue = -1;

    if (int channel = Mix_PlayChannel(-1, _soundsVector.at(ID), loops) != -1) {
		if (Mix_SetPosition(channel, second, 0))
			returnValue = channel;
	}

	return returnValue;
}

void SoundManager::Pause(int ID)
{
	Mix_Pause(ID);
}

void SoundManager::Resume(int ID)
{
	Mix_Resume(ID);
}

int SoundManager::Stop(int ID)
{
	return Mix_HaltChannel(ID);
}

int SoundManager::SetVolume(int ID, int volume)
{
	return Mix_Volume(ID, volume);
}