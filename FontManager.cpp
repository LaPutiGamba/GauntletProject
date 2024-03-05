#include "FontManager.h"

FontManager* FontManager::_pInstance = NULL;

bool FontManager::Init()
{
	if (TTF_Init() == -1) 
		return false;

	return true;
}

int FontManager::LoadFont(std::string path, int size)
{
	std::map<std::string, int>::iterator it = _idMap.find(path);
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
	_idMap[path] = _fontVector.size() - 1;

	return _fontVector.size() - 1;
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

void FontManager::RenderText(int id, std::string text, SDL_Color color, int x, int y, SDL_Surface* surface)
{
	SDL_Surface* surfaceText;
	surfaceText = TTF_RenderText_Solid(_fontVector[id].font, text.c_str(), color);
	
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_BlitSurface(surfaceText, NULL, surface, &destRect);
	SDL_FreeSurface(surfaceText);
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
