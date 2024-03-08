#pragma once

#include <SDL.h>
#include <string>

class Tileset
{
private:
	int _tileWidth; ///< The width of the tiles
	int _tileHeight; ///< The height of the tiles
	int _graphicID; ///< The graphic ID of the tileset (ResourceManager)

	SDL_Texture* _pTilesetTexture; ///< The texture of the tileset

public:
	Tileset();
	~Tileset();

	/// \brief Load a tileset from a file
	/// \param filename The file to load
	/// \return 0 if success, -1 if error
	int LoadTileset(const char* filename);

	/// \brief Set the tile width
	/// \param width The width of the tiles
	void SetTileWidth(int width) { _tileWidth = width; }

	/// \brief Set the tile height
	/// \param height The height of the tiles
	void SetTileHeight(int height) { _tileHeight = height; }

	/// \brief Get the tile width
	/// \return The tile width
	int GetTileWidth() { return _tileWidth; }

	/// \brief Get the tile height
	/// \return The tile height
	int GetTileHeight() { return _tileHeight; }

	/// \brief Get the texture of the tileset
	/// \return The texture of the tileset
	SDL_Texture* GetTexture() { return _pTilesetTexture; }
};