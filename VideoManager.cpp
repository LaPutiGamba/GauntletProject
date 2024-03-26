#include "VideoManager.h"
#include "ResourceManager.h"
#include <iostream>

VideoManager* VideoManager::_pInstance = NULL;

VideoManager::VideoManager()
{
	_window = NULL;
	_renderer = NULL;
	_screenTexture = NULL;
    _camera = NULL;
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

bool VideoManager::RenderGraphic(int _img, int _posX, int _posY, int _width, int _height, int _cutX, int _cutY)
{
    if (_camera != NULL) {
        _posX -= _camera->GetX();
        _posY -= _camera->GetY();
    }

    SDL_Rect r, rectAux;
    r.x = _posX;
    r.y = _posY;
    r.w = _width;
    r.h = _height;
    rectAux.w = _width;
    rectAux.h = _height;
    rectAux.x = _cutX;
    rectAux.y = _cutY;
    SDL_Texture* origin = ResourceManager::GetInstance()->GetGraphicByID(_img);
    
    if (origin != NULL) 
        if (SDL_RenderCopy(_renderer, origin, &rectAux, &r) == 0)
            return true;

    return false;
}

void VideoManager::RenderTextures(SDL_Texture* _texture, SDL_Rect* _src, SDL_Rect* _dest)
{
    if (_camera != NULL) {
		_dest->x -= _camera->GetX();
		_dest->y -= _camera->GetY();
	}

	SDL_RenderCopy(_renderer, _texture, _src, _dest);
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