#include "MapManager.h"

#include <iostream>
#include <ostream>

#include "TinyXML2/tinyxml2.h"
#include "VideoManager.h"

using namespace tinyxml2;

MapManager* MapManager::_pInstance = NULL;

MapManager::MapManager()
{
	_maps.clear();
	_camera = nullptr;
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
			nextPos = static_cast<int>(data.find(',', pos));
			
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
	return static_cast<int>(_maps.size()) - 1;
}

void MapManager::AddCollisionToLayer(int mapID, int layerID)
{
	_maps[mapID]._colliders.clear();
	
	for (int tmY = 0; tmY < _maps[mapID]._height; tmY++) {
		for (int tmX = 0; tmX < _maps[mapID]._width; tmX++) {
			int ID = _maps[mapID]._layers[layerID][tmY * _maps[mapID]._width + tmX] - 1;
			if (ID >= 0) {
				CollisionManager::Collider* collider = new CollisionManager::Collider();
				collider->x = tmX * _maps[mapID]._tileWidth;
				collider->y = tmY * _maps[mapID]._tileHeight;
				collider->width = _maps[mapID]._tileWidth;
				collider->height = _maps[mapID]._tileHeight;
				collider->type = CollisionManager::CT_WALL;
				collider->collisionsTag = CollisionManager::CT_PLAYER | CollisionManager::CT_ENEMY | CollisionManager::CT_BULLET;
				_maps[mapID]._colliders.push_back(collider);
				CollisionManager::GetInstance()->AddCollider(collider);
			}
		}
	}
}

int MapManager::GetIDFromLayer(int currentMap, int layer, int posX, int posY)
{
	int tileX = posX / _maps[0]._width;
	int tileY = posY / _maps[0]._height;
	return _maps[currentMap]._layers[layer][tileY * _maps[0]._width + tileX];
}

void MapManager::Render(int mapID)
{
	SDL_Rect rectS, rectT;
	int ID;
	int cellX, cellY;
	int tileW = _maps[mapID]._tileset.GetTileWidth();
	int tileH = _maps[mapID]._tileset.GetTileHeight();
	int tileSP = 0;

	for (int i = 0; i < LAYERSNUM; i++) {
		for (int tmY = 0; tmY < _maps[mapID]._height; tmY++) {
			for (int tmX = 0; tmX < _maps[mapID]._width; tmX++) {
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
					VideoManager::GetInstance()->RenderGraphic(_maps[mapID]._tileset.GetTextureID(), rectT.x, rectT.y, rectT.w, rectT.h, rectS.x, rectS.y);
				}
			}
		}
	}
}