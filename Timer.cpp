#include "Timer.h"


Timer::Timer()
{
	_tickStart = 0;
	_tickPause = 0;
	_ticks = 0;
	_state = TIM_INITIALIZED;
}

void Timer::Init()
{
	_tickStart = SDL_GetTicks();
	_ticks = 0;
	_state = TIM_STARTED;
}

void Timer::SetTimeCounter(int timer)
{
	_tickStart = SDL_GetTicks();
	_ticks = timer;
	_tickPause = _ticks;
	_state = TIM_INITIALIZED;
}



void Timer::ResetTimer()
{
	_tickPause = 0;
	_tickStart = 0;
	_ticks = 0;
	_state = TIM_INITIALIZED;
}

void Timer::StopTimer()
{
	if (_state != TIM_STOPPED)
	{
		_state = TIM_STOPPED;
		_ticks = SDL_GetTicks() - _tickStart;
	}
}

void Timer::StartTimer()
{
	_tickStart = SDL_GetTicks();
	_ticks = 0;
	_state = TIM_STARTED;
}

void Timer::PauseTimer()
{
	if (_state == TIM_STARTED)
	{
		_state = TIM_PAUSED;
		_tickPause = SDL_GetTicks();
		_ticks = _tickPause - _tickStart;
	}
}

void Timer::ResumeTimer()
{
	if (_state == TIM_PAUSED)
	{
		_state = TIM_STARTED;
		_tickStart = SDL_GetTicks();
		_tickPause = 0;
	}
}

int Timer::GetTicks()
{
	switch (_state)
	{
	case Timer::TIM_STARTED:
		_ticks += SDL_GetTicks() - _tickStart;
		_tickStart = SDL_GetTicks();
		return _ticks;

		break;
	case Timer::TIM_PAUSED:
		return _tickPause;
		break;
	case Timer::TIM_STOPPED:
		return _ticks;
		break;
	default:
		break;
	}
	return -1;
}

void Timer::AddTime(int time)
{
		_ticks += time;
}


