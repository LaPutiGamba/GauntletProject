#pragma once
#include <SDL.h>

/// \class Animation
/// \brief Handles the animation of the game
class Animation
{
private:
	int _frameCount; ///< Number of frames of the animation
	int _currentFrame; ///< Current frame of the animation
	SDL_Rect _startFrame; ///< Start frame of the animation

public:
	Animation();
	~Animation();

	/// \brief Get the frame of the animation
	/// \return SDL_Rect with the frame
	SDL_Rect GetFrame();

	/// \brief Initialize the animation
	/// \param X and Y of the start frame
	/// \param W and H of the start frame
	/// \param Number of frames of the animation
	void Init(int x, int y, int w, int h, int frameCount);

	/// \brief Update the animation
	void Update();

	/// \brief Update the reverse animation
	void UpdateReverse();
};

