#include "ResourceManager.h"
#include "VideoManager.h"
#include <iostream>

ResourceManager* ResourceManager::_pInstance = NULL;

Sint32 ResourceManager::AddGraphic(const char* file)
{
	SDL_Texture* loadedTexture = NULL;
		
	loadedTexture = IMG_LoadTexture(VideoManager::GetInstance()->GetRenderer(), file);

	Sint32 returnValue = -1;

	if (loadedTexture != NULL) {
		SDL_SetTextureBlendMode(loadedTexture, SDL_BLENDMODE_BLEND);

		if (_firstFreeSlot == _graphicsVector.size()) {
			_graphicsVector.push_back(loadedTexture);
			_firstFreeSlot++;
			returnValue = (Sint32)(_graphicsVector.size() - 1);
			_idMap.insert(std::pair<std::string, Sint32>(file, returnValue));
		} else {
			_graphicsVector.at(_firstFreeSlot) = loadedTexture;
			returnValue = _firstFreeSlot;
			UpdateFirstFreeSlotGraphic();
			_idMap.insert(std::pair<std::string, Sint32>(file, returnValue));
		}
	}

	return returnValue;
}

void ResourceManager::UpdateFirstFreeSlotGraphic()
{
	_firstFreeSlot = -1;

	for (Uint32 i = 0; i < _graphicsVector.size(); i++) {
		if (_graphicsVector.at(i) == NULL)
			_firstFreeSlot = i;
	}

	if (_firstFreeSlot == -1) _firstFreeSlot = (Uint32)_graphicsVector.size();
}

void ResourceManager::RemoveGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.find(file);

	if (it == _idMap.end()) {
		std::cout << "There's no file with that name loaded. Can't delete it." << std::endl;
		return;
	}

	Uint32 ID = it->second;

	SDL_DestroyTexture(GetGraphicByID(ID));

	_graphicsVector.at(ID) = NULL;
	_idMap.erase(file);
	UpdateFirstFreeSlotGraphic();
}

Sint32 ResourceManager::LoadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.find(file);

	Sint32 returnValue = -1;
	if (it != _idMap.end()) {
		return it->second;
	} else {
		Sint32 index = AddGraphic(file);

		if (index != -1) 
			returnValue = index;
	}

	return returnValue;
}

std::string ResourceManager::GetGraphicPathByID(Sint32 ID)
{
	if (ID < 0 || ID >= static_cast<Sint32>(_graphicsVector.size())) 
		return "NULL";

	for (std::map<std::string, Sint32>::iterator it = _idMap.begin(); it != _idMap.end(); it++) {
		if (it->second == ID) 
			return it->first;
	}
	return "NULL";
}

void ResourceManager::GetGraphicSize(Sint32 img, int &width, int &height)
{
	SDL_Texture* imgTexture = GetGraphicByID(img);
	if (imgTexture != NULL) {
		SDL_QueryTexture(imgTexture, NULL, NULL, &width, &width);
	} else {
		width = 0;
		height = 0;
	}
}

Uint16 ResourceManager::GetGraphicWidth(Sint32 img)
{
	SDL_Texture* imgTexture = GetGraphicByID(img);
	if (imgTexture != NULL) {
		int width;
		SDL_QueryTexture(GetGraphicByID(img), NULL, NULL, &width, NULL);
		return (Uint16)width;
	}
	return 0;
}

Uint16 ResourceManager::GetGraphicHeight(Sint32 img)
{
	SDL_Texture* imgTexture = GetGraphicByID(img);
	if (imgTexture != NULL) {
		int height;
		SDL_QueryTexture(GetGraphicByID(img), NULL, NULL, NULL, &height);
		return (Uint16)height;
	}
	return 0;
}

SDL_Texture* ResourceManager::GetGraphicByID(Sint32 ID)
{
	if (ID < 0) 
		return NULL;
	else if (ID < static_cast<Sint32>(_graphicsVector.size())) 
		return _graphicsVector[ID];
	else 
		return NULL;
}

void ResourceManager::SetAlphaGraphic(Sint32 ID, Uint8 alphaValue)
{
	SDL_SetTextureAlphaMod(GetGraphicByID(ID), alphaValue);
}

void ResourceManager::PrintLoadedGraphics()
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.begin();
	std::cout << "----------------- ALL LOADED GRAPICHS -----------------\n";
	while (it != _idMap.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << "-------------------------------------------------------\n";
}

Sint32 ResourceManager::CreateGraphic(const char* name, Uint16 width, Uint16 height)
{
	if (!width || !height) return 0;

	SDL_Surface* newSurface = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(VideoManager::GetInstance()->GetRenderer(), newSurface);

	Uint32 returnValue = -1;
	if (_firstFreeSlot == _graphicsVector.size()) {
		_graphicsVector.push_back(newTexture);
		_firstFreeSlot++;
		returnValue = (Sint32)(_graphicsVector.size() - 1);
		_idMap.insert(std::pair<std::string, Sint32>(name, returnValue));
	} else {
		_graphicsVector.at(_firstFreeSlot) = newTexture;
		returnValue = _firstFreeSlot;
		UpdateFirstFreeSlotGraphic();
		_idMap.insert(std::pair<std::string, Sint32>(name, returnValue));
	}

	SDL_FreeSurface(newSurface);

	return returnValue;
}
