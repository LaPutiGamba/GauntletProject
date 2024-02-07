#include "Animation.h"

SDL_Rect Animation::GetFrame()
{
	return { mStartFrame.x + (mStartFrame.w * mCurrentFrame), mStartFrame.y, mStartFrame.w, mStartFrame.h };
}

void Animation::init(int x, int y, int w, int h, int frameCount)
{
	mStartFrame.x = x;
	mStartFrame.y = y;
	mStartFrame.w = w;
	mStartFrame.h = h;
	mFrameCount = frameCount;
	mCurrentFrame = 0;
}

void Animation::update()
{
	mCurrentFrame++;
	if (mCurrentFrame >= mFrameCount)
	{
		mCurrentFrame = 0;
	}
}

void Animation::updateReverse()
{
	mCurrentFrame--;
	if (mCurrentFrame < 0)
	{
		mCurrentFrame = mFrameCount - 1;
	}
}

Animation::Animation()
{
	mStartFrame.x = 0;
	mStartFrame.y = 0;
	mStartFrame.w = 0;
	mStartFrame.h = 0;
	mFrameCount = 0;
	mCurrentFrame = 0;
}

Animation::~Animation()
{
}
