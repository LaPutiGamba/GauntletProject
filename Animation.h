#pragma once
#include <SDL.h>

/// \class Animation
/// \brief Handles the animation of the game
class Animation
{
	public:
	struct ImageCut
	{
		int x;
		int y;
		int w;
		int h;
	};

private:
	int _frameCount; ///< Number of frames of the animation
	int _currentFrame; ///< Current frame of the animation
	ImageCut _startFrame; ///< Start frame of the animation
	int _frameJump; ///< Number of frames to jump

public:
	Animation();
	~Animation();

	/// \brief Get the frame of the animation
	/// \return SDL_Rect with the frame
	Animation::ImageCut GetFrame();

	/// \brief Initialize the animation
	/// \param X and Y of the start frame
	/// \param W and H of the start frame
	/// \param Number of frames of the animation
	void Init(int x, int y, int w, int h, int frameCount, int frameJump);

	/// \brief Update the animation
	void Update();

	/// \brief Change the position of the idle animation to the last movement
	void changeIdlePos(int x);

	/// \brief Update the reverse animation
	void UpdateReverse();
};

