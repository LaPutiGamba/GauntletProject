#pragma once
#include <map>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/*
	ResourceManager class: Handles the load and management of the graphics in the game
*/
class ResourceManager
{
private:
	std::vector<SDL_Texture*> _graphicsVector; /* Vector that stores Textures. Useful in render methods and sequential access */
	std::map<std::string, Sint32> _idMap; /* Map that stores ID. Links strings to ID, Useful for check if graphic is has been loaded previously */
	Uint32 _firstFreeSlot; /* First free slot in the _graphicsVector */
	static ResourceManager* _pInstance; /* Singleton instance */

public:
	/*
		Desctructor
	*/
	~ResourceManager() {}

	/*
		Deletes a graphic from the ResourceManager map
		\param Filepath to the graphic
	*/
	void RemoveGraphic(const char* file);

	/*
		Gets the graphic ID from file name. Use addGraphic if it needs to load image from the disc
		\param Filepath to the graphic
		\return ID of the graphic
	*/
	Sint32 LoadAndGetGraphicID(const char* file);

	/*
		Gets the graphic path given an ID graphic
		\param ID of the graphic 
		\return Filepath to the graphic 
	*/
	std::string GetGraphicPathByID(Sint32 ID);

	/*
		Returns width and Height of a Surface
		\param ID of the graphic
		\param Width (return) for width value
		\param Height (return) for height value
	*/
	void GetGraphicSize(Sint32 img, int &width, int &height);

	/*
		Returns width of a Surface
		\param ID of the graphic
		\return Width of the graphic
	*/
	Uint16 GetGraphicWidth(Sint32 img);

	/*
		Returns height of a Surface
		\param ID of the graphic
		\return Height of the graphic
	*/
	Uint16 GetGraphicHeight(Sint32 img);

	/*
		Returns the SDL_Texture of the graphic. Only for render methods
		\param ID of the graphic
		\return SDL_Texture pointer to the graphic
	*/
	SDL_Texture* GetGraphicByID(Sint32 ID);

	/*
		Change general Alpha value to paint a concrete surface
		\param ID of the graphic
		\param Alpha Value from transparent (0) to opaque (255)
	*/
	void SetAlphaGraphic(Sint32 ID, Uint8 alphaValue);

	/*
		Prints the path to loaded graphics
	*/
	void PrintLoadedGraphics();

	/*
		Create a new surface graphic to the ResourceManager
		\param Name for the graphic
		\param Width Width for the graphic
		\param Height Height for the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 CreateGraphic(const char* name, Uint16 width, Uint16 height);

	/*
		Gets Singleton instance
		\return Instance of ResourceManager (Singleton)
	*/
	static ResourceManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new ResourceManager();
		return _pInstance;
	}

protected:
	/*
		Constructor of an empty ResourceManager.Singleton mode
	*/
	ResourceManager() { _firstFreeSlot = 0; }

private:
	/*
		Loads from disc and adds a graphic to the ResourceManager 
		\param Filepath to the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 AddGraphic(const char* file);
	
	/*
		Searches the first NULL in _graphicsVector and updates _firstFreeSlot to store its position
	*/
	void UpdateFirstFreeSlotGraphic();
};