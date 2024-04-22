#include "Animation.h"

Animation::ImageCut Animation::GetFrame()
{
	return { _startFrame.x + (_startFrame.w * _currentFrame), _startFrame.y, _startFrame.w, _startFrame.h };
}

void Animation::Init(int x, int y, int w, int h, int frameCount, int frameJump)
{
	_startFrame.x = x;
	_startFrame.y = y;
	_startFrame.w = w;
	_startFrame.h = h;
	_frameCount = frameCount;
	_currentFrame = 0;
	_frameJump = frameJump;
}

void Animation::Update()
{
	static int frameDelayCounter = 0;
	frameDelayCounter++;

	if(frameDelayCounter >= 5) {
		_currentFrame += _frameJump;

		if (_currentFrame >= _frameCount * _frameJump)
			_currentFrame = 0;

		frameDelayCounter = 0;
	}
}

void Animation::ChangeIdlePos(int x)
{
	_startFrame.x = x;
	_currentFrame = 0;
}


void Animation::UpdateReverse()
{
	_currentFrame--;

	if (_currentFrame < 0)
		_currentFrame = _frameCount - 1;

}

bool Animation::IsFinished()
{
	if (_currentFrame == _frameCount - 1)
		return true;
	else
		return false;
}

Animation::Animation()
{
	_startFrame.x = 0;
	_startFrame.y = 0;
	_startFrame.w = 0;
	_startFrame.h = 0;
	_frameCount = 0;
	_currentFrame = 0;
	_frameJump = 0;
}

Animation::~Animation()
{
}
