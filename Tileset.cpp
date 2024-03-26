#include "Tileset.h"
#include "ResourceManager.h"

Tileset::Tileset()
{
	_tileWidth = 0;
	_tileHeight = 0;
	_graphicID = 0;
}

Tileset::~Tileset()
{
}

int Tileset::LoadTileset(const char* filename)
{
	_graphicID = ResourceManager::GetInstance()->LoadAndGetGraphicID(filename);
	if (_graphicID < 0)
		return -1;

	return 0;
}
