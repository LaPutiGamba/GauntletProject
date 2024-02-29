#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1020

/// \class VideoManager
/// \brief Handles the load and management of the graphics in the game
class VideoManager
{
private:
	SDL_Window* _window; ///< Window to render the screen
	SDL_Renderer* _renderer; ///< Renderer to render the screen
	SDL_Texture* _screenTexture; ///< Texture to render the screen
	static VideoManager* _pInstance; ///< Singleton instance 

public:
	~VideoManager() {}

	/// \brief Initialize the window, the screen surface and the image
	/// \return True if all went well, false if something fails
	bool Init();

	/// \brief Renders the selected grapich based on the params
	/// \param Image id 
	/// \param X and Y of the destination source 
	/// \param W and H of the source
	void RenderGraphic(int _img, int _posX, int _posY, int _width, int _height);

	/// \brief Get the renderer
	/// \return SDL_Renderer pointer to the screen renderer
	SDL_Renderer* GetRenderer();

	/// \brief Clears the screen with the selected color
	/// \param Color to paint the full screen
	void ClearScreen(unsigned int _colorKey);

	/// \brief Update the screen
	void UpdateScreen();

	/// \brief Wait a specified time
	/// \param Milliseconds to wait
	void WaitTime(int _ms);

	/// \brief Close all the services
	void Close();

	///	\brief Singleton instance getter
	///	\return Singleton instance
	static VideoManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new VideoManager();
		return _pInstance;
	}

protected:
	VideoManager();
};