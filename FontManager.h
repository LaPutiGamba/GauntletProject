#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include <map>

class FontManager
{
public:
	struct Font {
		TTF_Font* font;
		int size;
		std::string path;
	};

private:
	std::vector<Font> _fontVector; ///< Vector of fonts, used to keep track of fonts
	//std::vector<std::pair<std::string, int>> _idMap; ///< Map of fonts, stores the path of the font and the id of the font
	std::map<std::string, int> _idMap; ///< Map of fonts, stores the path of the font and the id of the font
	static FontManager* _pInstance; ///< Singleton instance

public:
	~FontManager() {};

	/// \brief Initializes the font manager
	/// \return True if the font manager was initialized successfully, false otherwise
	bool Init();

	///	\brief Loads a font from a file
	/// \param path The path of the font to be loaded
	/// \param size The size of the font to be loaded
	/// \return The id of the font that was loaded
	int LoadAndGetFontID(std::string path, int size);

	/// \brief Deletes a font from the font vector and the id map
	/// \param id The id of the font to be deleted
	void RemoveFont(int id);

	/// \brief Deletes a font from the font vector and the id map
	/// \param path The path of the font to be deleted
	void RemoveFont(std::string path);

	/// \brief Renders text to a surface
	/// \param id The id of the font to be used
	/// \param text The text to be rendered
	/// \param color The color of the text
	/// \param x The x position of the text
	/// \param y The y position of the text
	void RenderText(int id, std::string text, SDL_Color color, int x, int y);

	///	\brief Prints the path to loaded fonts
	void PrintLoadedFonts();
	
	/// \brief Cleans up the vector and map
	void CleanUp();

	/// \brief Closes the font manager
	void Close();

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static FontManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new FontManager();
		return _pInstance;
	}
protected:
	FontManager() {};
};

