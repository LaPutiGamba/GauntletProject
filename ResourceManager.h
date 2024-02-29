#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/// \class ResourceManager
/// \brief Handles the load and management of the graphics in the game
class ResourceManager
{
private:
	std::vector<SDL_Texture*> _graphicsVector; ///< Vector that stores Textures. Useful in render methods and sequential access
	std::map<std::string, Sint32> _idMap; ///< Map that stores ID. Links strings to ID, Useful for check if graphic is has been loaded previously
	Uint32 _firstFreeSlot; ///< First free slot in the _graphicsVector 
	static ResourceManager* _pInstance; ///< Singleton instance 

public:
	~ResourceManager() {}

	///	\brief Deletes a graphic from the _idMap and _graphicsVector
	///	\param Filepath to the graphic
	void RemoveGraphic(const char* file);

	///	\brief Gets the graphic ID from file name. Use AddGraphic if it needs to load image from the disc
	/// \see AddGraphic(const char* file)
	///	\param Filepath to the graphic
	///	\return ID of the graphic
	Sint32 LoadAndGetGraphicID(const char* file);

	///	\brief Gets the graphic path given an ID graphic
	///	\param ID of the graphic 
	///	\return Filepath to the graphic 
	std::string GetGraphicPathByID(Sint32 ID);

	///	\brief Returns width and height of a Surface
	///	\param ID of the graphic
	///	\param Width (return) for width value
	///	\param Height (return) for height value
	void GetGraphicSize(Sint32 img, int &width, int &height);

	///	\brief Returns width of a Surface
	///	\param ID of the graphic
	///	\return Width of the graphic
	Uint16 GetGraphicWidth(Sint32 img);

	///	\brief Returns height of a Surface
	///	\param ID of the graphic
	///	\return Height of the graphic
	Uint16 GetGraphicHeight(Sint32 img);

	///	\brief Returns the SDL_Texture of the graphic. Only for render methods
	///	\param ID of the graphic
	///	\return SDL_Texture pointer to the graphic
	SDL_Texture* GetGraphicByID(Sint32 ID);

	///	\brief Change general Alpha value to paint a concrete surface
	///	\param ID of the graphic
	///	\param Alpha Value from transparent (0) to opaque (255)
	void SetAlphaGraphic(Sint32 ID, Uint8 alphaValue);

	///	\brief Prints the path to loaded graphics
	void PrintLoadedGraphics();

	///	\brief Create a new surface graphic to the _idMap and _graphicsVector
	///	\param Name for the graphic
	///	\param Width Width for the graphic
	///	\param Height Height for the graphic
	///	\return -1 if there's an error when loading
	Sint32 CreateGraphic(const char* name, Uint16 width, Uint16 height);

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static ResourceManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new ResourceManager();
		return _pInstance;
	}

protected:
	ResourceManager() { _firstFreeSlot = 0; }

private:
	///	\brief Loads from disc and adds a graphic to the _graphicsVector 
	///	\param Filepath to the graphic
	///	\return -1 if there's an error when loading
	Sint32 AddGraphic(const char* file);
	
	///	\brief Searches the first NULL in _graphicsVector and updates _firstFreeSlot to store its position
	void UpdateFirstFreeSlotGraphic();
};