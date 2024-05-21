#pragma once

#include "Tileset.h"
#include <vector>
#include "Camera.h"
#include "CollisionManager.h"

#define LAYERSNUM 2 ///< The number of layers of the map

class MapManager
{
public:
	struct Map {
		int _width; ///< The width of the map
		int _height; ///< The height of the map

		Tileset _tileset; ///< The tileset used by the map
		int _tileWidth; ///< The width of the tiles
		int _tileHeight; ///< The height of the tiles

		std::vector<int> _layers[LAYERSNUM]; ///< The layers of the map
		std::vector<CollisionManager::Collider*> _colliders; ///< The colliders of the map
	};

private:
	std::vector<Map> _maps; ///< The maps
	Camera* _camera; ///< The camera
	static MapManager* _pInstance; ///< Singleton instance 

public:
	~MapManager();

	/// \brief Load a map from a file
	/// \param filename The file to load
	/// \return ID of the map if success, -1 if error
	int LoadAndGetMapID(const char* filename);

	/// \brief Add collision to a layer
	/// \param mapID ID of the map
	/// \param ID of the layer to add the collision
	void AddCollisionToLayer(int mapID, int layerID);

	/// \brief Render the map
	void Render(int mapID);

	/// \brief Get the width of the map
	/// \param ID The ID of the map
	/// \return The width of the map
	int GetWidth(int ID) { return _maps[ID]._width; }

	/// \brief Get the height of the map
	/// \param ID The ID of the map
	/// \return The height of the map
	int GetHeight(int ID) { return _maps[ID]._height; }

	/// \brief Get the width of the tile
	/// \param ID The ID of the map
	/// \return The width of the tile
	int GetTileWidth(int ID) { return _maps[ID]._tileWidth; }

	/// \brief Get the height of the tile
	/// \param ID The ID of the map
	/// \return The height of the tile
	int GetTileHeight(int ID) { return _maps[ID]._tileHeight; }

	/// \brief Get the ID of the tile from a layer
    ///	\param CurrentMap The current map
	/// \param Layer The layer to get the ID from
	/// \param PosX The x position of the tile
	/// \param PosY The y position of the tile
	/// \return The ID of the tile
	int GetIDFromLayer(int currentMap, int layer, int posX, int posY);

	void SetCamera(Camera* camera) { _camera = camera; }

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static MapManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new MapManager();
		return _pInstance;
	}

protected:
	MapManager();
};