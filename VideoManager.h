#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1020

/*
	VideoManager class: Handles the creation of the window and controles the surface
*/
class VideoManager
{
public:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _screenTexture;

	/*
		Desctructor
	*/
	~VideoManager() {}

	/*
		Initialize the window, the screen surface and the image
		\return True if all went well, false if something fails
	*/	
	bool Init();

	/*
		Renders the selected grapich based on the params
		\param Image id 
		\param X and Y of the destination source 
		\param W and H of the source
	*/
	void RenderGraphic(int _img, int _posX, int _posY, int _width, int _height);

	/*
		Get the renderer
		\return SDL_Renderer pointer to the screen renderer
	*/
	SDL_Renderer* GetRenderer();

	/*
		Clears the screen with the selected color
		\param Color to paint the full screen
	*/
	void ClearScreen(unsigned int _colorKey);

	/*
		Update the screen
	*/
	void UpdateScreen();

	/*
		Wait a specified time
		\param Milliseconds to wait
	*/
	void WaitTime(int _ms);

	/*
		Close all the service
	*/
	void Close();

	/*
		Gets Singleton instance
		\return Instance of Video (Singleton)
	*/
	static VideoManager* GetInstance() {
		if (_pInstance == NULL)
			_pInstance = new VideoManager();
		return _pInstance;
	}
protected:
	// Constructor of an empty Video. Singleton mode
	VideoManager();

private:
	static VideoManager* _pInstance; /* Singleton instance */
};