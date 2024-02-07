#pragma once
#include <SDL.h>
class Animation
{
private:
	int mFrameCount;
	int mCurrentFrame;
	SDL_Rect mStartFrame;
	public:
		SDL_Rect GetFrame();
		void init(int x, int y, int w, int h, int frameCount);
		void update();
		void updateReverse();
		Animation();
		~Animation();
};

