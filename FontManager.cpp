#include "FontManager.h"
#include "VideoManager.h"
#include <iostream>

FontManager* FontManager::_pInstance = NULL;

bool FontManager::Init()
{
	if (TTF_Init() == -1) 
		return false;

	return true;
}

int FontManager::LoadAndGetFontID(std::string path, int size)
{
	std::map<std::string, int>::iterator it = _idMap.find(path + std::to_string(size));
	if (it != _idMap.end())
		return it->second;
	
	TTF_Font* ttf = TTF_OpenFont(path.c_str(), size);
	if (ttf == NULL)
		return -1;

	Font font;
	font.font = ttf;
	font.size = size;
	font.path = path;

	_fontVector.push_back(font);
    int fontVectorSize = static_cast<int>(_fontVector.size());
	_idMap[path + std::to_string(size)] = fontVectorSize - 1;

	return fontVectorSize - 1;
}

void FontManager::RemoveFont(int id)
{
	if (id < 0 || id >= _fontVector.size())
		return;

	TTF_CloseFont(_fontVector[id].font);

	_idMap.erase(_fontVector[id].path);
	_fontVector.erase(_fontVector.begin() + id);
}

void FontManager::RemoveFont(std::string path)
{
	std::map<std::string, int>::iterator it = _idMap.find(path);
	if (it != _idMap.end())
		RemoveFont(it->second);
}

void FontManager::RenderText(int id, std::string text, SDL_Color color, int x, int y)
{
	VideoManager* videoManager = VideoManager::GetInstance();
	SDL_Surface* surfaceText;
	surfaceText = TTF_RenderText_Solid(_fontVector[id].font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(videoManager->GetRenderer(), surfaceText);
	
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = surfaceText->w;
	destRect.h = surfaceText->h;

	if (texture)
		SDL_RenderCopy(videoManager->GetRenderer(), texture, NULL, &destRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surfaceText);
}

void FontManager::PrintLoadedFonts()
{
	std::map<std::string, Sint32>::iterator it;
	it = _idMap.begin();
	std::cout << "----------------- ALL LOADED FONTS -----------------\n";
	while (it != _idMap.end()) {
		std::cout << it->first << std::endl;
		it++;
	}
	std::cout << "----------------------------------------------------\n";
}

void FontManager::CleanUp()
{
	for (size_t i = 0; i < _fontVector.size(); i++)
		TTF_CloseFont(_fontVector[i].font);

	_fontVector.clear();
	_idMap.clear();
	//En caso de cerrar todos los SDL: TTF_Quit();
}

void FontManager::Close()
{
	CleanUp();
	TTF_Quit();
}
