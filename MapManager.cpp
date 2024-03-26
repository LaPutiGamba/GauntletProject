#include "MapManager.h"
#include "TinyXML2/tinyxml2.h"
#include "VideoManager.h"

using namespace tinyxml2;

MapManager* MapManager::_pInstance = NULL;

MapManager::MapManager()
{
	_maps.clear();
	_cameraX = 0;
	_cameraY = 0;
}

MapManager::~MapManager()
{
}

int MapManager::LoadAndGetMapID(const char* filename)
{
	Map newMap;

	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
		return -1;

	XMLElement* map = doc.FirstChildElement("map");
	if (map == NULL)
		return -1;

	map->QueryIntAttribute("width", &newMap._width);
	map->QueryIntAttribute("height", &newMap._height);
	map->QueryIntAttribute("tilewidth", &newMap._tileWidth);
	map->QueryIntAttribute("tileheight", &newMap._tileHeight);

	XMLElement* tileset = map->FirstChildElement("tileset");
	if (tileset == NULL)
		return -1;

	newMap._tileset.LoadTileset(tileset->FirstChildElement("image")->Attribute("source"));
	newMap._tileset.SetTileWidth(newMap._tileWidth);
	newMap._tileset.SetTileHeight(newMap._tileHeight);

	XMLElement* layer = map->FirstChildElement("layer");
	for (int i = 0; i < LAYERSNUM; i++) {
		std::string data = layer->FirstChildElement("data")->GetText();

		int pos = 0;
		int nextPos = 0;
		
		while (nextPos != std::string::npos) {
			nextPos = data.find(',', pos);
			
			if (nextPos != std::string::npos) {
				int value = std::stoi(data.substr(pos, nextPos - pos));
				newMap._layers[i].push_back(value);
				pos = nextPos + 1;
			} else {
				int value = std::stoi(data.substr(pos, data.length() - pos));
				newMap._layers[i].push_back(value);
			}
		}

		layer = layer->NextSiblingElement("layer");
	}

	_maps.push_back(newMap);
	return (_maps.size() - 1);
}

void MapManager::Render(int mapID)
{
	SDL_Rect rectS, rectT;
	int ID;
	int cellX, cellY;
	int tileW = _maps[mapID]._tileset.GetTileWidth();
	int tileH = _maps[mapID]._tileset.GetTileHeight();
	int tileSP = 0;

	int initTileX = _cameraX / tileW;
	int lastTileX = ((2 + SCREEN_WIDTH) / tileW) + initTileX;
	if (lastTileX > _maps[mapID]._width)
		lastTileX = _maps[mapID]._width;

	int initTileY = _cameraY / tileH;
	int lastTileY = ((2 + SCREEN_HEIGHT) / tileH) + initTileY;
	if (lastTileY > _maps[mapID]._height)
		lastTileY = _maps[mapID]._height;

	for (int i = 0; i < LAYERSNUM; i++) {
		for (int tmY = 0; tmY < _maps[mapID]._height; tmY++) {
			for (int tmX = initTileX; tmX < lastTileX; tmX++) {
				rectT.x = tmX * tileW;
				rectT.y = tmY * tileH;
				rectT.w = tileW;
				rectT.h = tileH;

				ID = _maps[mapID]._layers[i][tmY * _maps[mapID]._width + tmX] - 1;

				if (ID >= 0) {
					cellX = ID % 16;
					cellY = ID / 16;
					rectS.x = cellX * tileW + tileSP * cellX;
					rectS.y = cellY * tileW + tileSP * cellY;
					rectS.w = tileW;
					rectS.h = tileH;
					rectT.x -= _cameraX;
					SDL_RenderCopy(VideoManager::GetInstance()->GetRenderer(), _maps[mapID]._tileset.GetTexture(), &rectS, &rectT);
				}
			}
		}
	}
}