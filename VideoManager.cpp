#include "VideoManager.h"
#include "ResourceManager.h"
#include <iostream>

VideoManager* VideoManager::_pInstance = NULL;

VideoManager::VideoManager()
{
	_window = NULL;
	_renderer = NULL;
	_screenTexture = NULL;
}

bool VideoManager::Init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: \n" << SDL_GetError();
        success = false;
    } else {
        // Create window
        _window = SDL_CreateWindow("Gauntlet Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (_window == NULL) {
            std::cout << "Window could not be created! SDL Error: \n" << SDL_GetError();
            success = false;
        } else {
            // Create renderer
            int rendFlags = SDL_RENDERER_PRESENTVSYNC;
            _renderer = SDL_CreateRenderer(_window, -1, rendFlags);
            if (_renderer == NULL) {
                std::cout << "Renderer could not be created! SDL Error: \n" << SDL_GetError();
                success = false;
            } else {
                // Initialize PNG and JPG loading
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: \n" << IMG_GetError();
                    success = false;
                }
            }
        }
    }

    return success;
}

void VideoManager::RenderGraphic(int _img, int _posX, int _posY, int _width, int _height)
{
    SDL_Rect r, rectAux;
    r.x = _posX;
    r.y = _posY;
    rectAux.w = _width;
    rectAux.h = _height;
    rectAux.x = 0;
    rectAux.y = 0;
    SDL_Texture* origin = ResourceManager::GetInstance()->GetGraphicByID(_img);
    
    if (origin != NULL)
        SDL_RenderCopy(_renderer, origin, &rectAux, &r);
}

SDL_Renderer* VideoManager::GetRenderer()
{
    return _renderer;
}

void VideoManager::ClearScreen(unsigned int _colorKey) 
{
    SDL_SetRenderDrawColor(_renderer, (_colorKey >> 24) & 0xFF, (_colorKey >> 16) & 0xFF, (_colorKey >> 8) & 0xFF, _colorKey & 0xFF);
    SDL_RenderClear(_renderer);
}

void VideoManager::UpdateScreen() 
{
    SDL_RenderPresent(_renderer);
}

void VideoManager::WaitTime(int _ms) 
{
    SDL_Delay(_ms);
}

void VideoManager::Close() 
{
    IMG_Quit();
    SDL_DestroyWindow(_window);
    SDL_Quit();
}